/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2LODTerrainPage.hpp
*
* �汾		:	1.0 (2011/03/05)
*
* ����		��	more
*
*/

#ifndef PX2LODTERRAINPAGE_HPP
#define PX2LODTERRAINPAGE_HPP

#include "PX2TerrainPrerequisites.hpp"

namespace PX2
{

	class Renderer;
	class Camera;
	class LODTerrainBlock;
	class LODTerrainVertex;

	class PX2_TERRAIN_ENTRY LODTerrainPage : public TriMesh
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(LODTerrainPage);

	public:
		// size = 2^p + 1, p <= 7 (size = 3, 5, 9, 17, 33, 65, 129)
		LODTerrainPage (VertexFormat *vformat, int size,
			unsigned short *height, const Vector2f &origin,
			float minElevation, float maxElevation, float spacing, 
			float uvBias);

		virtual ~LODTerrainPage ();

		// �̷߳���
		int GetSize () const;
		const unsigned short *GetHeights () const;
		const Vector2f &GetOrigin () const;
		float GetMinElevation () const;
		float GetMaxElevation () const;
		float GetSpacing () const;

		// pixel tolerance on projected vertex height
		void SetPixelTolerance (const Renderer* renderer, float tolerance);
		float GetPixelTolerance () const;

		/// �̲߳���
		/**
		* �������λ���ڵ���ҳ��Χ�⣬����INFINITY��
		* @ param x	��������X����λ��
		* @ param y	��������Y����λ��
		*/
		float GetHeight (float x, float y) const;

		float &GetUVBias ();

	protected:
		friend class LODTerrainBlock;

		// �־û�֧��
		LODTerrainPage ();

		void InitializeDerivedData ();

		// queue handlers
		void AddToQueue (unsigned short blockIndex);
		unsigned short RemoveFromQueue ();
		unsigned short ReadFromQueue (unsigned short index);

		/// ����ҳ������ཻ���
		bool IntersectFrustum (const Camera *camera);

		// ���ο��
		void SimplifyBlocks (const Camera* camera, const APoint &modelEye,
			const AVector &modelDir, bool closeAssumption);

		// �����
		void SimplifyVertices (const APoint &modelEye,
			const AVector &modelDir, bool closeTerrainAssumption);

		// ���μ�
		friend class LODTerrain;
		void EnableBlocks ();
		void ResetBlocks ();
		void Simplify (const Renderer* renderer, const APoint &modelEye,
			const AVector &modelDir, bool closeAssumption);

		// ����
		float GetX (int x) const; //< x��X�����񶥵�����
		float GetY (int y) const; //< y��Y�����񶥵�����
		float GetHeight (int index) const; //< iIndex�����񶥵�����
		float GetTextureCoordinate (int index) const;
		void Render (LODTerrainBlock &block);
		void RenderTriangle (int t, int l, int r);
		void RenderBlocks ();

		// �ɼ����ü�
		virtual void GetVisibleSet (Culler &culler, bool noCull);

		// �߳�����
		int mSize, mSizeM1;
		unsigned short *mHeights;
		Vector2f mOrigin;
		float mMinElevation, mMaxElevation, mSpacing;
		float mInvSpacing, mTextureSpacing, mMultiplier;

		// �������
		float mUVBias;

		// ��
		float mPixelTolerance, mWorldTolerance;
		mutable bool mNeedsTessellation;
		int *mLookup;
		int mConnectLength;

		/// (2^p+1) * (2^p+1)�Ķ������飬��������
		LODTerrainVertex *mVertexs;
		VertexBufferAccessor mVBA;

		// maximum quantities
		int mTotalVQuantity, mTotalTQuantity, mTotalIQuantity;

		// quadtree of blocks
		int mBlockQuantity;
		LODTerrainBlock* mBlocks;

		// ��¼���Ӳ�Block��
		unsigned short *mQueue;
		unsigned short mQueueQuantity;
		unsigned short mFront, mRear;
		unsigned short mNumUnprocessed;
		unsigned short mItemsInQueue;

		// �ڲ�ʹ��
	public:
		// �̻߳�ȡ����Ϊ z = h(x,y)��xyƽ��ʹ����������ϵ������ͼ��ʾ
		//
		// y
		// ^
		// | col 0   col 1
		// +--------+-------+
		// |   10   |  11   | row 1
		// +--------+-------+
		// |   00   |  01   | row 0
		// +--------+-------+--> x

		// ����ҳ(r,c)��(r,c+1)֮��ķ��
		void StitchNextCol (LODTerrainPage *nextCol);
		void UnstitchNextCol (LODTerrainPage *nextCol);

		// ����ҳ(r,c)��(r+1,c)֮��ķ��
		void StitchNextRow (LODTerrainPage *nextRow);
		void UnstitchNextRow (LODTerrainPage *nextRow);
	};

	PX2_REGISTER_STREAM(LODTerrainPage);
	typedef Pointer0<LODTerrainPage> LODRawTerrainPagePtr;
#include "PX2LODTerrainPage.inl"

}

#endif