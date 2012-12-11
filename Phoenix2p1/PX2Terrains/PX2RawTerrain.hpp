/*
*
* �ļ�����	��	PX2RawTerrain.hpp
*
*/

#ifndef PX2RAWTERRAIN_HPP
#define PX2RAWTERRAIN_HPP

#include "PX2Terrain.hpp"
#include "PX2RawTerrainPage.hpp"
#include "PX2EditTerrainMaterial.hpp"

namespace PX2
{
	
	class RawTerrain : public Terrain
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(RawTerrain);

	public:
		RawTerrain ();
		virtual ~RawTerrain ();

		// ��������ʱ�����õ�������
		/*
		* ��Щ�ӿڣ��ڱ༭���д�������ʹ��
		*/
		void SetRowQuantity (int numRows);
		void SetColQuantity (int numCols);
		void SetSize (int size);
		void SetSpacing (float spacing);
		void AllocateRawTerrainPages ();

		RawTerrainPage* GetPage (int row, int col);
		RawTerrainPage* GetCurrentPage (float x, float y) const;
		bool GetPageIndex (int &outRow, int &outCol, RawTerrainPage *page);
		RawTerrainPagePtr ReplacePage (int row, int col, RawTerrainPage* newPage);

		virtual float GetHeight (float x, float y) const;
		virtual AVector GetNormal (float x, float y) const;

		// mtl
		EditTerrainMaterial *GetTerrainMaterial ();
		Shine *GetShine ();

	protected:
		void CreatePage (int row, int col);

		VertexFormatPtr mVFormat;
		RawTerrainPagePtr** mPages;

		EditTerrainMaterialPtr mMaterial;
		ShinePtr mShine;
	};

	PX2_REGISTER_STREAM(RawTerrain);
	typedef Pointer0<RawTerrain> RawTerrainPtr;
#include "PX2RawTerrain.inl"

}

#endif