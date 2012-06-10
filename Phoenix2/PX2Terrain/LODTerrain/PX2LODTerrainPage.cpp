/*
*
* �ļ�����	��	PX2LODTerrainPage.cpp
*
*/

#include "PX2LODTerrainPage.hpp"
#include "PX2LODTerrainBlock.hpp"
#include "PX2LODTerrainVertex.hpp"
#include "PX2Camera.hpp"
#include "PX2Renderer.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, TriMesh, LODTerrainPage);
PX2_IMPLEMENT_STREAM(LODTerrainPage);
PX2_IMPLEMENT_FACTORY(LODTerrainPage);
PX2_IMPLEMENT_DEFAULT_NAMES(TriMesh, LODTerrainPage);

//----------------------------------------------------------------------------
LODTerrainPage::LODTerrainPage(VertexFormat *vformat, int size, 
								 unsigned short *height, const Vector2f &origin, 
								 float minElevation, float maxElevation,
								 float spacing, float uvBias)
								 :
mOrigin(origin)
{
	// size = 2^p + 1, p <= 7
	assertion(size ==  3 || size ==  5 || size ==   9 || size == 17
		|| size == 33 || size == 65 || size == 129, "size is not right.");

	mVFormat = vformat;

	// ����
	mTotalVQuantity = size*size; // ��ඥ������
	mVBuffer = new0 VertexBuffer(mTotalVQuantity, vformat->GetStride(),
		Buffer::BU_STATIC);
	
	// ��������
	mTotalTQuantity = 2*(size-1)*(size-1);
	mTotalIQuantity = 3*mTotalTQuantity;

	mIBuffer = new0 IndexBuffer(mTotalIQuantity, sizeof(int), Buffer::BU_DYNAMIC);

	// ����
	mVBA.ApplyTo((VertexFormat*)vformat, mVBuffer);

	// ԭʼ��������
	mSize = size;
	mHeights = height;
	mMinElevation = minElevation;
	mMaxElevation = maxElevation;
	mSpacing = spacing;
	mUVBias = uvBias;

	InitializeDerivedData();
}
//----------------------------------------------------------------------------
LODTerrainPage::LODTerrainPage ()
:
mOrigin(Vector2f::ZERO)
{
	mTotalVQuantity = 0;
	mTotalIQuantity = 0;
	mSize = 0;
	mHeights = 0;
	mMinElevation = 0.0f;
	mMaxElevation = 0.0f;
	mSpacing = 0.0f;
	mUVBias = 0.0f;
	mSizeM1 = 0;
	mPixelTolerance = 0.0f;
	mWorldTolerance = 0.0f;
	mInvSpacing = 0.0f;
	mTextureSpacing = 0.0f;
	mMultiplier = 0.0f;
	mNeedsTessellation = true;
	mLookup = 0;
	mConnectLength = 0;
	mVertexs = 0;
	mBlockQuantity = 0;
	mBlocks = 0;
	mQueueQuantity = 0;
	mQueue = 0;
	mFront = 0;
	mRear = 0;
	mItemsInQueue = 0;
}
//----------------------------------------------------------------------------
LODTerrainPage::~LODTerrainPage ()
{
	delete1(mHeights);
	delete1(mVertexs);
	delete1(mBlocks);
	delete1(mQueue);
	delete1(mLookup);
}
//----------------------------------------------------------------------------
void LODTerrainPage::InitializeDerivedData ()
{
	mSizeM1 = mSize - 1;
	mPixelTolerance = 1.0f;
	mWorldTolerance = -1.0f;
	mInvSpacing = 1.0f/mSpacing;
	mTextureSpacing = 1.0f/float(mSizeM1);
	mMultiplier = (mMaxElevation - mMinElevation)/65535.0f;
	mNeedsTessellation = true;

	mLookup = new1<int>(mTotalVQuantity);

	// ��ʼ��������Ϣ����
	mVertexs = new1<LODTerrainVertex>(mTotalVQuantity);
	memset(mVertexs, 0, mTotalVQuantity*sizeof(LODTerrainVertex));

	// ����block��quadtree
	mBlockQuantity = mSize*(mSize-2)/3;
	mBlocks = new1<LODTerrainBlock>(mBlockQuantity);

	// ��ʼ��quadtree
	int stride = (mSize-1)/2;
	mBlocks[0].Initialize(this, mBlocks, 0, 0, 0, stride, true);
	mBlocks[0].UpdateBoundingBox(this, mBlocks, 0, stride);

	// �������block�����������Χ���ϼ������ҳ��Χ��
	APoint center = 0.5f*(mBlocks[0].GetMax() + mBlocks[0].GetMin());
	AVector diag = 0.5f*(mBlocks[0].GetMax() - mBlocks[0].GetMin());
	mModelBound.SetCenter(center);
	mModelBound.SetRadius(diag.Length());

	// ����queue
	mQueueQuantity =
		(unsigned short)(mBlockQuantity - mBlockQuantity/4);
	mQueue = new1<unsigned short>(mQueueQuantity);

	// ��quadtree����ʼ������
	mQueue[0] = 0;
	mFront = 0;
	mRear = 1;
	mItemsInQueue = 1;
}
//----------------------------------------------------------------------------
void LODTerrainPage::SetPixelTolerance (const Renderer* renderer,
										float tolerance)
{
	float width = (float)renderer->GetWidth();
	const Camera *camera = renderer->GetCamera();
	float rMax = camera->GetRMax();
	float dMin = camera->GetDMin();

	mPixelTolerance = tolerance;
	mWorldTolerance = 2.0f*rMax*mPixelTolerance/(dMin*width);
	mWorldTolerance *= mWorldTolerance;
}
//----------------------------------------------------------------------------
float LODTerrainPage::GetHeight (float x, float y) const
{
	float xGrid = (x - mOrigin.X()) * mInvSpacing;
	if (xGrid<0.0f || xGrid>=(float)mSizeM1)
	{
		// λ�ò��ڵ���ҳ��
		return Mathf::MAX_REAL;
	}

	float yGrid = (y - mOrigin.Y())*mInvSpacing;
	if (yGrid < 0.0f || yGrid >= (float)mSizeM1)
	{
		// λ�ò��ڵ���ҳ��
		return Mathf::MAX_REAL;
	}

	float col = Mathf::Floor(xGrid);
	int iCol = (int)col;
	float row = Mathf::Floor(yGrid);
	int iRow = (int)row;

	int index = iCol + mSize*iRow;
	float deltaX = xGrid - col;
	float deltaY = yGrid - row;
	float h00, h10, h01, h11, height;

	if ((iCol&1) == (iRow&1))
	{
		float diff = deltaX - deltaY;
		h00 = mMinElevation + mMultiplier*mHeights[index];
		h11 = mMinElevation + mMultiplier*mHeights[index+1+mSize];
		if (diff > 0.0f)
		{
			h10 = mMinElevation + mMultiplier*mHeights[index+1];
			height = (1.0f-diff-deltaY)*h00 + diff*h10+deltaY*h11;
		}
		else
		{
			h01 = mMinElevation+mMultiplier*mHeights[index+mSize];
			height = (1.0f+diff-deltaX)*h00-diff*h01+deltaX*h11;
		}
	}
	else
	{
		float sum = deltaX + deltaY;
		h10 = mMinElevation + mMultiplier*mHeights[index+1];
		h01 = mMinElevation + mMultiplier*mHeights[index+mSize];
		if (sum <= 1.0f)
		{
			h00 = mMinElevation + mMultiplier*mHeights[index];
			height = (1.0f-sum)*h00 + deltaX*h10 + deltaY*h01;
		}
		else
		{
			h11 = mMinElevation + mMultiplier*mHeights[index+1+mSize];
			height = (sum-1.0f)*h11 + (1.0f-deltaY)*h10 + (1.0f-deltaX)*h01;
		}
	}

	return height;
}
//----------------------------------------------------------------------------
bool LODTerrainPage::IntersectFrustum (const Camera *camera)
{
	// ������ҳ�Ƿ��������ͷ����
	mBlocks[0].TestIntersectFrustum(this, camera);
	bool intersect = mBlocks[0].IsVisible();
	mBlocks[0].ClearBits();
	return intersect;
}
//----------------------------------------------------------------------------
void LODTerrainPage::AddToQueue (unsigned short blockIndex)
{
	mQueue[mRear] = blockIndex;
	if (++mRear == mQueueQuantity)
	{
		mRear = 0;
	}
	mItemsInQueue++;
}
//----------------------------------------------------------------------------
unsigned short LODTerrainPage::RemoveFromQueue ()
{
	unsigned short block = mQueue[mFront];
	if (++mFront == mQueueQuantity)
	{
		mFront = 0;
	}
	mItemsInQueue--;
	return block;
}
//----------------------------------------------------------------------------
unsigned short LODTerrainPage::ReadFromQueue (unsigned short index)
{
	index = index + mFront;
	if (index < mQueueQuantity)
	{
		return mQueue[index];
	}
	else
	{
		return mQueue[index - mQueueQuantity];
	}
}
//----------------------------------------------------------------------------
void LODTerrainPage::EnableBlocks ()
{
	for (int i=0; i<mBlockQuantity; i++)
	{
		mBlocks[i].Enable(this);
	}
}
//----------------------------------------------------------------------------
void LODTerrainPage::ResetBlocks ()
{
	unsigned short queue, block;
	if (mFront < mRear)
	{
		mNumUnprocessed = mRear - mFront;
		for (queue = mFront; queue < mRear; queue++)
		{
			block = mQueue[queue];
			if (mBlocks[block].BitsSet())
			{
				mBlocks[block].Disable(this);
				mBlocks[block].ClearBits();
			}
		}
	}
	else
	{
		mNumUnprocessed = mQueueQuantity - mFront + mRear;
		for (queue = mFront; queue < mQueueQuantity; queue++)
		{
			block = mQueue[queue];
			if (mBlocks[block].BitsSet())
			{
				mBlocks[block].Disable(this);
				mBlocks[block].ClearBits();
			}
		}
		for (queue = 0; queue < mRear; queue++)
		{
			block = mQueue[queue];
			if (mBlocks[block].BitsSet())
			{
				mBlocks[block].Disable(this);
				mBlocks[block].ClearBits();
			}
		}
	}
}
//----------------------------------------------------------------------------
void LODTerrainPage::SimplifyBlocks (const Camera* camera,
									  const APoint &modelEye, 
									  const AVector& modelDir,
									  bool closeAssumption)
{
	while (mNumUnprocessed > 0)
	{
		// �Ӷ��׶�ȡ��Ҫ�����block
		unsigned short blockIndex = RemoveFromQueue();
		LODTerrainBlock* block = &mBlocks[blockIndex];

		if (!block->IsProcessed())
		{
			// ������Ҫ�����block����
			mNumUnprocessed--;

			unsigned short childIndex;
			LODTerrainBlock *child;
			Vector2f location;
			int i;
			
			// --- ������������ ---

			if (block->IsFirstChild(blockIndex))
			{
				// ���block�������ֵ�block��Ҫ����block���
				if (block->IsSibling(blockIndex, ReadFromQueue(2)))
				{
					child = block;
					if (closeAssumption)
					{
						for (i = 0; i < 4; i++, child++)
						{
							location.X() = child->GetX()*mSpacing +
								mOrigin.X();
							location.Y() = child->GetY()*mSpacing +
								mOrigin.Y();
							child->ComputeInterval(modelDir, modelEye,
								mWorldTolerance,location,mSpacing);
							if (child->GetDeltaMax() > child->GetDeltaL())
							{
								break;
							}
						}
					}
					else // distant assumption
					{
						for (i = 0; i < 4; i++, child++)
						{
							child->ComputeInterval(modelEye,mWorldTolerance);
							if (child->GetDeltaMax() > child->GetDeltaL())
							{
								break;
							}
						}
					}

					if (i == 4) // ���еĺ��Ӷ�����Ҫϸ�֣��򱻸������
					{
						// �Ƴ�������block������һ����block�Ѿ����Ƴ���
						for (i = 0; i < 3; i++)
						{
							childIndex = RemoveFromQueue();
							if (!mBlocks[childIndex].IsProcessed())
							{
								mNumUnprocessed--;
							}
							mBlocks[childIndex].ClearBits();
						}

						// ����block����
						unsigned short parentIndex =
							(unsigned short)block->GetParentIndex(blockIndex);
						AddToQueue(parentIndex);
						assert(!mBlocks[parentIndex].IsProcessed());
						mNumUnprocessed++;

						continue; // continue!
					}
				}
			} // end if (block->IsFirstChild(blockIndex))

			// --- ϸ�ּ�� ---

			if (!block->IsVisibilityTested())
			{
				block->TestIntersectFrustum(this,camera);
			}

			// block���ڲ���block
			if (block->GetStride() > 1)
			{
				// ֻ�е��ڽ�ͷ�巶Χ�ڿɼ�����ϸ�ֵ��ο�
				if (block->IsVisible())
				{
					childIndex = (unsigned short)block->GetChildIndex(
						blockIndex,1);
					child = &mBlocks[childIndex];
					if (closeAssumption) 
					{
						for (i = 0; i < 4; i++, child++)
						{
							location.X() = child->GetX()*mSpacing +
								mOrigin.X();
							location.Y() = child->GetY()*mSpacing +
								mOrigin.Y();
							child->ComputeInterval(modelDir, modelEye,
								mWorldTolerance, location, mSpacing);
							if (child->GetDeltaMax() > child->GetDeltaL())
							{
								break;
							}
						}
					}
					else // distant assumption
					{
						for (i = 0; i < 4; i++, child++)
						{
							child->ComputeInterval(modelEye,
								mWorldTolerance);
							if (child->GetDeltaMax() > child->GetDeltaL())
							{
								break;
							}
						}
					}

					// ֻҪ��һ��������Ҫϸ�֣��ͽ�4�����Ӽ��봦�����
					if (i < 4)
					{
						// �����Ӽ��봦����У������Ѿ����Ƴ���
						for (i = 0; i < 4; i++, childIndex++)
						{
							// ���뺢��block
							AddToQueue(childIndex);
							assertion(!mBlocks[childIndex].IsProcessed(), 
								"child shoule not already be processed.");
							mNumUnprocessed++;
						}

						continue; // continue!

					} // end if (block->IsVisible())
				}
			} // end if (block->GetStride() > 1)


			// --- �Ȳ�����Ҳ��ϸ�� ---

			block->SetProcessed(true);
		} // end if (!block->IsProcessed())

		AddToQueue(blockIndex);
	}
}
//----------------------------------------------------------------------------
void LODTerrainPage::SimplifyVertices (const APoint& modelEye,
										const AVector& modelDir, bool closeAssumption)
{
	unsigned int queue, block;

	if (mFront < mRear)
	{
		for (queue = mFront; queue < mRear; queue++)
		{
			block = mQueue[queue];
			if (mBlocks[block].IsVisible())
			{
				mBlocks[block].SimplifyVertices(this,modelEye,
					modelDir,mWorldTolerance,closeAssumption);
			}
		}
	}
	else
	{
		for (queue = mFront; queue < mQueueQuantity; queue++)
		{
			block = mQueue[queue];
			if (mBlocks[block].IsVisible())
			{
				mBlocks[block].SimplifyVertices(this,modelEye,
					modelDir,mWorldTolerance,closeAssumption);
			}
		}
		for (queue = 0; queue < mRear; queue++)
		{
			block = mQueue[queue];
			if (mBlocks[block].IsVisible())
			{
				mBlocks[block].SimplifyVertices(this,modelEye,
					modelDir,mWorldTolerance,closeAssumption);
			}
		}
	}
}
//----------------------------------------------------------------------------
void LODTerrainPage::Simplify (const Renderer *renderer,
								const APoint &modelEye, 
								const AVector &modelDir,
								bool closeAssumption)
{
	if (mWorldTolerance == -1.0f)
	{
		SetPixelTolerance(renderer, mPixelTolerance);
	}

	SimplifyBlocks(renderer->GetCamera(), modelEye, modelDir,
		closeAssumption);
	SimplifyVertices(modelEye, modelDir, closeAssumption);

	mNeedsTessellation = true;
}
//----------------------------------------------------------------------------
void LODTerrainPage::Render (LODTerrainBlock &block)
{
	int origin = block.GetX() + mSize*block.GetY();
	int stride = block.GetStride();
	int twoStride = 2*stride;
	int twoStrideTimesSize = twoStride*mSize;
	int index[5] =
	{
		origin,
		origin + twoStride,
		origin + stride*(mSize + 1),
		origin + twoStrideTimesSize,
		origin + twoStrideTimesSize + twoStride
	};

	if (block.IsEven())
	{ // ż��
		RenderTriangle(index[0], index[3], index[1]);
		RenderTriangle(index[4], index[1], index[3]);
	}
	else
	{
		RenderTriangle(index[1], index[0], index[4]);
		RenderTriangle(index[3], index[4], index[0]);
	}
}
//----------------------------------------------------------------------------
void LODTerrainPage::RenderTriangle (int t, int l, int r)
{
	// ȷ�����������ڲ��Ļ���Ҷ���ϵ�
	bool interior;
	if (r > t)
	{
		if (l > t)
		{
			interior = (r - t > 1);
		}
		else
		{
			interior = (t - l > 1);
		}
	}
	else
	{
		if (l > t)
		{
			interior = (l - t > 1);
		}
		else
		{
			interior = (t - r > 1);
		}
	}

	if (interior)
	{
		// �����������ڲ�block���Ա�ϸ�֣�M�Ǳ�<L,R>���е㡣
		int m = ((l + r) >> 1);
		if (mVertexs[m].IsEnabled())
		{
			RenderTriangle(m, t, l);
			RenderTriangle(m, r, t);
			return;
		}
	}

	// ���������ݴ��
	int vertexNumElements = mVBuffer->GetNumElements();
	int x, y, unit;
	Float2 tCoord;
	if (mLookup[t] == -1)
	{
		x = t % mSize;
		y = t / mSize;

		mVBA.Position<Float3>(vertexNumElements) =
			Float3(GetX(x), GetY(y), GetHeight(t));

		tCoord = Float2(GetTextureCoordinate(x), GetTextureCoordinate(y));
		for (unit=0; unit<VertexFormat::AM_MAX_TCOORD_UNITS; unit++)
		{
			if (mVBA.HasTCoord(unit))
			{
				mVBA.TCoord<Float2>(unit, vertexNumElements) = tCoord;
			}
		}
		mLookup[t] = vertexNumElements++;
		mVBuffer->SetNumElements(vertexNumElements);
	}

	if (mLookup[r] == -1)
	{
		x = r % mSize;
		y = r / mSize;

		mVBA.Position<Float3>(vertexNumElements) =
			Float3(GetX(x), GetY(y), GetHeight(r));

		tCoord = Float2(GetTextureCoordinate(x), GetTextureCoordinate(y));
		for (unit=0; unit<VertexFormat::AM_MAX_TCOORD_UNITS; unit++)
		{
			if (mVBA.HasTCoord(unit))
			{
				mVBA.TCoord<Float2>(unit, vertexNumElements) = tCoord;
			}
		}
		mLookup[r] = vertexNumElements++;
		mVBuffer->SetNumElements(vertexNumElements);
	}

	if (mLookup[l] == -1)
	{
		x = l % mSize;
		y = l / mSize;

		mVBA.Position<Float3>(vertexNumElements) =
			Float3(GetX(x), GetY(y), GetHeight(l));

		tCoord = Float2(GetTextureCoordinate(x), GetTextureCoordinate(y));
		for (unit=0; unit<VertexFormat::AM_MAX_TCOORD_UNITS; unit++)
		{
			if (mVBA.HasTCoord(unit))
			{
				mVBA.TCoord<Float2>(unit, vertexNumElements) = tCoord;
			}
		}
		mLookup[l] = vertexNumElements++;
		mVBuffer->SetNumElements(vertexNumElements);
	}

	assertion(vertexNumElements<mTotalVQuantity,
		"vertexNumElements must be less than mTotalVQuantity.");

	// ���ö�������
	int indexNumElements = mIBuffer->GetNumElements();

	int *indices = (int*)mIBuffer->GetData();
	indices[indexNumElements++] = mLookup[t];
	indices[indexNumElements++] = mLookup[r];
	indices[indexNumElements++] = mLookup[l];
	mIBuffer->SetNumElements(indexNumElements);

	assertion(indexNumElements<mTotalIQuantity,
		"indexNumElements should be less than mTotalIQuantity");
}
//----------------------------------------------------------------------------
void LODTerrainPage::RenderBlocks ()
{
	// ���û�����
	memset(mLookup,0xFF,mSize*mSize*sizeof(int));
	mVBuffer->SetNumElements(0);
	mIBuffer->SetNumElements(0);

	unsigned short queue;
	if (mFront < mRear)
	{
		for (queue=mFront; queue<mRear; queue++)
		{
			LODTerrainBlock &block = mBlocks[mQueue[queue]];
			if (block.IsVisible())
			{
				Render(block);
			}
		}
	}
	else
	{
		for (queue=mFront; queue<mQueueQuantity; queue++)
		{
			LODTerrainBlock& block = mBlocks[mQueue[queue]];
			if (block.IsVisible())
			{
				Render(block);
			}
		}
		for (queue=0; queue<mRear; queue++)
		{
			LODTerrainBlock& block = mBlocks[mQueue[queue]];
			if (block.IsVisible())
			{
				Render(block);
			}
		}
	}
}
//----------------------------------------------------------------------------
void LODTerrainPage::GetVisibleSet (Culler &culler, bool noCull)
{
	if (mNeedsTessellation)
	{
		mNeedsTessellation = false;
		RenderBlocks();
	}

	if (mIBuffer->GetNumElements() > 0)
	{
		TriMesh::GetVisibleSet(culler, noCull);
	}
}
//----------------------------------------------------------------------------
void LODTerrainPage::StitchNextCol (LODTerrainPage *nextCol)
{
	// 'this'����ҳΪ(r,c)��'nextCol'����ҳΪ(r,c+1)
	assertion(nextCol->mSize == mSize, "size should be the same.");

	int max = mSize - 2;
	int xThis = mSize - 1;
	int xNext = 0;

	for (int y=1; y<=max; y++)
	{
		int indexThis = xThis + mSize*y;
		int indexNext = xNext + mSize*y;
		LODTerrainVertex *vThis = &mVertexs[indexThis];
		LODTerrainVertex *vNext = &nextCol->mVertexs[indexNext];
		vNext->SetDependent(0, vThis);
		vThis->SetDependent(1, vNext);
	}
}
//----------------------------------------------------------------------------
void LODTerrainPage::UnstitchNextCol (LODTerrainPage *nextCol)
{
	// 'this'����ҳΪ(r,c)��'nextCol'����ҳΪ(r,c+1)
	assertion(nextCol->mSize == mSize, "size should be the same.");

	int max = mSize - 2;
	int xThis = mSize - 1;
	int xNext = 0;

	for (int y=1; y<=max; y++)
	{
		int indexThis = xThis + mSize*y;
		int indexNext = xNext + mSize*y;
		LODTerrainVertex *vThis = &mVertexs[indexThis];
		LODTerrainVertex *vNext = &nextCol->mVertexs[indexNext];
		vNext->SetDependent(0, 0);
		vThis->SetDependent(1, 0);
	}
}
//----------------------------------------------------------------------------
void LODTerrainPage::StitchNextRow (LODTerrainPage *nextRow)
{
	// 'this'����ҳΪ(r,c)��'nextRow'����ҳΪ(r+1,c)
	assertion(nextRow->mSize == mSize, "size should be the same.");

	int max = mSize - 2;
	int yThis = mSize - 1;
	int yNext = 0;

	for (int x=1; x<max; x++)
	{
		int indexThis = x + mSize*yThis;
		int indexNext = x + mSize*yNext;
		LODTerrainVertex *vThis = &mVertexs[indexThis];
		LODTerrainVertex *vNext = &nextRow->mVertexs[indexNext];
		vNext->SetDependent(1, vThis);
		vThis->SetDependent(0, vNext);
	}
}
//----------------------------------------------------------------------------
void LODTerrainPage::UnstitchNextRow (LODTerrainPage *nextRow)
{
	// 'this'����ҳΪ(r,c)��'nextRow'����ҳΪ(r+1,c)
	assertion(nextRow->mSize == mSize, "size should be the same.");

	int max = mSize - 2;
	int yThis = mSize - 1;
	int yNext = 0;

	for (int x=1; x<max; x++)
	{
		int indexThis = x + mSize*yThis;
		int indexNext = x + mSize*yNext;
		LODTerrainVertex *vThis = &mVertexs[indexThis];
		LODTerrainVertex *vNext = &nextRow->mVertexs[indexNext];
		vNext->SetDependent(1, 0);
		vThis->SetDependent(0, 0);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�
//----------------------------------------------------------------------------
LODTerrainPage::LODTerrainPage (LoadConstructor value)
:
TriMesh(value),
mSize(0),
mSizeM1(0),
mHeights(0),
mOrigin(Float2(0.0f, 0.0f)),
mMinElevation(0.0f),
mMaxElevation(0.0f),
mSpacing(0.0f),
mInvSpacing(0.0f),
mMultiplier(0.0f)
{
}
//----------------------------------------------------------------------------
void LODTerrainPage::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	TriMesh::Load(source);

	source.Read(mSize);
	mTotalIQuantity = mSize*mSize;
	mHeights = new1<unsigned short>(mTotalIQuantity);
	source.ReadVR(mTotalIQuantity, mHeights);
	source.Read(mOrigin);
	source.Read(mMinElevation);
	source.Read(mMaxElevation);
	source.Read(mSpacing);

	mSizeM1 = mSize - 1;
	mInvSpacing = 1.0f/mSpacing;
	mMultiplier = (mMaxElevation- mMinElevation)/65535.0f;

	PX2_END_DEBUG_STREAM_LOAD(LODTerrainPage, source);
}
//----------------------------------------------------------------------------
void LODTerrainPage::Link (InStream& source)
{
	TriMesh::Link(source);
}
//----------------------------------------------------------------------------
void LODTerrainPage::PostLink ()
{
	TriMesh::PostLink();
}
//----------------------------------------------------------------------------
bool LODTerrainPage::Register (OutStream& target) const
{
	return TriMesh::Register(target);
}
//----------------------------------------------------------------------------
void LODTerrainPage::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	TriMesh::Save(target);

	target.Write(mSize);
	target.WriteN(mTotalIQuantity, mHeights);
	target.Write(mOrigin);
	target.Write(mMinElevation);
	target.Write(mMaxElevation);
	target.Write(mSpacing);

	PX2_END_DEBUG_STREAM_SAVE(LODTerrainPage, target);
}
//----------------------------------------------------------------------------
int LODTerrainPage::GetStreamingSize () const
{
	int size = TriMesh::GetStreamingSize();
	size += sizeof(mSize);
	size += mSize*mSize*sizeof(mHeights[0]);
	size += sizeof(mOrigin);
	size += sizeof(mMinElevation);
	size += sizeof(mMaxElevation);
	size += sizeof(mSpacing);
	return size;
}
//----------------------------------------------------------------------------