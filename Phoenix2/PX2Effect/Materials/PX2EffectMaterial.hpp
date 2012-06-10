/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2EffectMaterial.hpp
*
* �汾		:	1.0 (2011/02/23)
*
* ����		��	more
*
*/

#ifndef PX2EFFECTMATERIAL_HPP
#define PX2EFFECTMATERIAL_HPP

#include "PX2EffectPrerequisites.hpp"

namespace PX2
{

	class EffectMaterial : public Material
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EffectMaterial);

	public:
		EffectMaterial (const std::string &filename);
		virtual ~EffectMaterial ();
	};

	PX2_REGISTER_STREAM(EffectMaterial);
	typedef Pointer0<EffectMaterial> EffectMaterialPtr;

}

#endif