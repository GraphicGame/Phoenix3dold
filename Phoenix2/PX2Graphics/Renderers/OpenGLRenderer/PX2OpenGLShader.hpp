/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2OpenGLShader.hpp
*
* �汾		:	1.0 (2011/05/14)
*
* ����		��	TimeX
*
*/

#ifndef PX2OPENGLSHADER_HPP
#define PX2OPENGLSHADER_HPP

#include "PX2OpenGLPrerequisites.hpp"
#include "PX2OpenGLRendererData.hpp"
#include "PX2Shader.hpp"
#include "PX2ShaderParameters.hpp"

namespace PX2
{

	class Renderer;

	class PdrShader
	{
	public:
		// Construction and destruction.  The derived classes are
		// PdrVertexShader and PdrPixelShader.  Both classes hide the
		// base-class destructor.  This is not a problem because the
		// derived-class destructors are called explicitly when the shaders
		// are destroyed by Renderer.
		PdrShader ();
		~PdrShader ();

	protected:
		void SetSamplerState (Renderer* renderer, const Shader* shader,
			int profile, const ShaderParameters* parameters, int maxSamplers,
			RendererData::SamplerState* currentSS);

		void DisableTextures (Renderer* renderer, const Shader* shader,
			int profile, const ShaderParameters* parameters, int maxSamplers);
	};

}

#endif
