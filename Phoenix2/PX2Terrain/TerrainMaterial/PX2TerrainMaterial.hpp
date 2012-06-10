/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2TerrainMaterial.hpp
*
* �汾		:	1.0 (2011/11/12)
*
* ����		��	more
*
*/

#ifndef PX2TERRAINMATERIAL_HPP
#define PX2TERRAINMATERIAL_HPP

#include "PX2TerrainPrerequisites.hpp"

namespace PX2
{

	class PX2_TERRAIN_ENTRY TerrainMaterial : public Material
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(TerrainMaterial);

	public:
		TerrainMaterial (const std::string &filename);
		virtual ~TerrainMaterial ();
	};

	PX2_REGISTER_STREAM(TerrainMaterial);
	typedef Pointer0<TerrainMaterial> TerrainMaterialPtr;

}

#endif