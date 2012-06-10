/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2LodTerrainBlock.hpp
*
* �汾		:	1.0 (2011/03/03)
*
* ����		��	more
*
*/

#ifndef PX2LODTERRAINBLOCK_HPP
#define PX2LODTERRAINBLOCK_HPP

#include "PX2TerrainPrerequisites.hpp"

namespace PX2
{
	class Camera;
	class Frustum;
	class LODTerrainPage;
	class LODTerrainVertex;

	class PX2_TERRAIN_ENTRY LODTerrainBlock
	{
	public:
		int GetX () const;
		int GetY () const;
		int GetStride () const;
		float GetDelta (int i) const;
		float GetDeltaMax () const;
		float GetDeltaL () const;
		float GetDeltaH () const;
		const Vector3f& GetMin () const;
		const Vector3f& GetMax () const;

		void SetEven (bool set);
		bool IsEven () const;
		void SetProcessed (bool set);
		bool IsProcessed () const;
		void SetVisible (bool set);
		bool IsVisible () const;
		void SetVisibilityTested (bool set);
		bool IsVisibilityTested () const;

		bool BitsSet () const;
		void ClearBits ();

		// ����quadtree
		void Initialize (LODTerrainPage *page, LODTerrainBlock *blocks,
			int blockIndex, int x, int y, int stride, bool even);

		// ����block�İ�Χ��
		void UpdateBoundingBox (LODTerrainPage *page,
			LODTerrainBlock *blocks, int blockIndex, int stride);

		/// ����ҳ��Χ�к������ͷ���ཻ���
		void TestIntersectFrustum (const LODTerrainPage* page,
			const Camera* camera);

		// distant terrain assumption
		void ComputeInterval (const APoint &modelEye, float tolerance);

		// close terrain assumption
		void ComputeInterval (const AVector &modelDir,
			const APoint &modelEye, float tolerance, Vector2f &loc,
			float spacing);

		// �򻯶���
		void SimplifyVertices (LODTerrainPage* page,
			const APoint &modelEye, const AVector &modelDir,	float tolerance,
			bool closeAssumption);

		void Enable (LODTerrainPage* page);
		void Disable (LODTerrainPage* page);

		// quadtree ����
		static int GetParentIndex (int child);
		static int GetChildIndex (int parent, int index); //< 1<=index<=4
		static bool IsFirstChild (int index);
		static bool IsSibling (int index, int test);

	protected:
		// mFlags��bit��ʶ
		enum
		{
			EVEN_PARITY       = 0x01,
			PROCESSED         = 0x02,
			VISIBLE           = 0x04,
			VISIBILITY_TESTED = 0x08, // �ɼ����Ѽ���
			BITS_MASK         = 0x0E  // all but even parity bit
		};

		/// ���block��9������
		void GetVertex9 (unsigned short size, LODTerrainVertex* origin,
			LODTerrainVertex* vertex[9]);

		unsigned char mX, mY, mStride, mFlags;
		float mHeightDelta[5], mHeightDeltaMax;
		float mDeltaL, mDeltaH;
		APoint mMin, mMax;
	};

#include "PX2LODTerrainBlock.inl"

}

#endif