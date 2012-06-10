/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2LODTerrain.hpp
*
* �汾		:	1.0 (2011/03/05)
*
* ����		��	more
*
*/

#ifndef PX2LODTERRAIN_HPP
#define PX2LODTERRAIN_HPP

#include "PX2TerrainPrerequisites.hpp"
#include "PX2LODTerrainPage.hpp"

namespace PX2
{

	/// Level Of Detail����
	class PX2_TERRAIN_ENTRY LODTerrain : public Node
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(LODTerrain);

	public:
		LODTerrain (const char* heightName, const char* imageName,
			VertexFormat *vertexFormat, Renderer *renderer, float uvBias,
			Float4 *borderColor);

		virtual ~LODTerrain ();

		void SetRenderer (Renderer* renderer);

		// ���γ�Ա
		int GetRowQuantity () const;
		int GetColQuantity () const;
		int GetSize () const;
		float GetMinElevation () const;
		float GetMaxElevation () const;
		float GetSpacing () const;
		void SetPixelTolerance (float fTolerance);
		float GetPixelTolerance () const;
		bool &CloseAssumption ();
		float &GetUVBias ();
		Float4 &GetBorderColor ();

		// ����ҳ����
		LODTerrainPage *GetPage (int row, int col);
		LODTerrainPage *GetCurrentPage (float x, float y) const;
		float GetHeight (float x, float y) const;

		/// ����λ��(fX,fY)�ķ���
		AVector GetNormal (float x, float y) const;

		/// ����ҳ�滻
		/**
		* �����Ͼ͵ĵ���ҳ�������µĵ���ҳ���ҷ�ϵ�һ�𡣷��ؾɵĵ���ҳ���Ա�
		* �ٴθ��á�
		*/
		LODRawTerrainPagePtr ReplacePage (int row, int col,
			const char *heightName, const char *heightSuffix,
			const char *imageName, const char *imageSuffix);

		LODRawTerrainPagePtr ReplacePage (int row, int col,
			LODTerrainPage *newPage);

		void UseLOD (bool use);
		bool UsingLOD ();

		/// �򻯵���
		void Simplify ();

	protected:
		LODTerrain ();

		void LoadHeader (const char *heightPrefix);
		void LoadPage (int row, int col, const char *heightName,
			const char *heightSuffix, const char *imageName,
			const char *imageSuffix);
		void StitchAll (); //< �����е���ҳ�����һ��

		// ����ҳ�����ʽ
		VertexFormatPtr mVFormat;

		// ����ҳ��Ϣ
		int mRowQuantity, mColQuantity;
		int mSize; //< һ������ҳ�Ĵ�С
		float mMinElevation, mMaxElevation, mSpacing;
		LODRawTerrainPagePtr **mPages;

		// simplification
		float mPixelTolerance;
		Renderer *mRenderer;
		bool mCloseAssumption;

		// �����ǰ���ڵ���ҳ
		int mCameraRow, mCameraCol;

		// �������
		float mUVBias;
		Float4 mBorderColor;

		bool mUseLOD;
	};

	PX2_REGISTER_STREAM(LODTerrain);
	typedef Pointer0<LODTerrain> LODTerrainPtr;
#include "PX2LODTerrain.inl"

}

#endif