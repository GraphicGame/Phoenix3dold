/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2RawTerrain.h
*
* �汾		:	1.0 (2011/05/14)
*
* ����		��	more
*
*/

#ifndef PX2RAWTERRAIN_HPP
#define PX2RAWTERRAIN_HPP

#include "PX2TerrainPrerequisites.hpp"
#include "PX2Node.hpp"
#include "PX2Camera.hpp"
#include "PX2RawTerrainPage.hpp"
#include "PX2TerrainMaterial.hpp"

namespace PX2
{

	class PX2_TERRAIN_ENTRY RawTerrain : public Node
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(RawTerrain);

	public:
		RawTerrain (); //< ͨ���༭����������ʱʹ��
		RawTerrain (const std::string& heightName, VertexFormat* vformat,
			Camera* camera, int mode = FileIO::FM_DEFAULT_READ);

		virtual ~RawTerrain ();

		// ����
		TerrainMaterial *GetTerrainMaterial ();
		Shine *GetShine ();

		// ��������ʱ�����õ�������
		/*
		* ��Щ�ӿڣ��ڱ༭���д�������ʹ��
		*/
		void SetRowQuantity (int numRows);
		void SetColQuantity (int numCols);
		void SetSize (int size);
		void SetSpacing (float spacing);
		void AllocateRawTerrainPages ();
		void UpdateToHighField ();

		// ��Ա����
		inline int GetRowQuantity () const;
		inline int GetColQuantity () const;
		inline int GetSize () const;
		inline float GetSpacing () const;
		float GetHeight (float x, float y) const;
		AVector GetNormal (float x, float y) const;

		// ����ҳ����
		RawTerrainPage* GetPage (int row, int col);
		RawTerrainPage* GetCurrentPage (float x, float y) const;
		bool GetPageIndex (int &outRow, int &outCol, RawTerrainPage *page);
		RawTerrainPagePtr ReplacePage (int row, int col,
			const std::string& heightName, const std::string& heightSuffix);
		RawTerrainPagePtr ReplacePage (int row, int col, RawTerrainPage* newPage);

		// Update of active set of terrain pages.
		void OnCameraMotion ();

	protected:
		void LoadHeader (const std::string& heightName);

		void CreatePage (int row, int col);
		void LoadPage (int row, int col, const std::string& heightName,
			const std::string& heightSuffix);

		// Read mode for the height header file and the terrain page data.
		int mMode;

		// Shared by the pages.
		VertexFormatPtr mVFormat;

		// Page information.
		int mNumRows, mNumCols;
		int mSize;
		float mMinElevation, mMaxElevation, mSpacing;
		RawTerrainPagePtr** mPages;

		// Current page containing the camera.
		int mCameraRow, mCameraCol;
		CameraPtr mCamera;

		// Terrain Material
		TerrainMaterialPtr mTerrainMaterial;
		ShinePtr mShine;
	};

	PX2_REGISTER_STREAM(RawTerrain);
	typedef Pointer0<RawTerrain> RawTerrainPtr;
#include "PX2RawTerrain.inl"

}

#endif