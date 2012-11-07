/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2WglRendererData.hpp
*
* �汾		:	1.0 (2011/05/17)
*
* ����		��	TimeX
*
*/

#ifndef PX2WGLRENDERERDATA_HPP
#define PX2WGLRENDERERDATA_HPP

#include "PX2OpenGLPrerequisites.hpp"
#include "PX2OpenGLRendererData.hpp"
#include "PX2WGLExtensions.hpp"

namespace PX2
{

	class WglRendererData : public RendererData
	{
	public:
		HWND mWindowHandle;
		HDC mWindowDC;
		HGLRC mWindowRC;
	};

}

#endif
