/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2LightModelPositionConstant.hpp
*
* 版本		:	1.0 (2011/02/01)
*
* 作者		：	more
*
*/

#ifndef PX2LIGHTMODELPOSITIONCONSTANT_HPP
#define PX2LIGHTMODELPOSITIONCONSTANT_HPP

#include "PX2GraphicsPrerequisites.hpp"
#include "PX2ShaderFloat.hpp"
#include "PX2Light.hpp"

namespace PX2
{

	class LightModelPositionConstant : public ShaderFloat
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(LightModelPositionConstant);

	public:
		LightModelPositionConstant (Light* light);
		virtual ~LightModelPositionConstant ();

		void SetLight (Light *light);
		Light* GetLight ();

		virtual void Update (const Renderable* renderable, const Camera* camera);

	protected:
		LightPtr mLight;
	};

	PX2_REGISTER_STREAM(LightModelPositionConstant);
	typedef Pointer0<LightModelPositionConstant> LightModelPositionConstantPtr;

}

#endif
