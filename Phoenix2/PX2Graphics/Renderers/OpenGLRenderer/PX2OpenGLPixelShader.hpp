/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2OpenGLPixelShader.hpp
*
* �汾		:	1.0 (2011/05/14)
*
* ����		��	TimeX
*
*/

#ifndef PX2OPENGLPIXELSHADER_HPP
#define PX2OPENGLPIXELSHADER_HPP

#include "PX2OpenGLPrerequisites.hpp"
#include "PX2OpenGLShader.hpp"
#include "PX2PixelShader.hpp"

namespace PX2
{

	class Renderer;

	class PdrPixelShader : public PdrShader
	{
	public:
		PdrPixelShader (Renderer* renderer, const PixelShader* pshader);
		~PdrPixelShader ();

		void Enable (Renderer* renderer, const PixelShader* pshader,
			const ShaderParameters* parameters);
		void Disable (Renderer* renderer, const PixelShader* pshader,
			const ShaderParameters* parameters);

	private:
		GLuint mShader;
	};

}

#endif
