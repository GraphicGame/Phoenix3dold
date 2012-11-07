/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2WglRendererInput.hpp
*
* �汾		:	1.0 (2011/05/17)
*
* ����		��	TimeX
*
*/

#ifndef PX2WGLRENDERERINPUT_HPP
#define PX2WGLRENDERERINPUT_HPP

#include "PX2Dx9RendererPrerequisites.hpp"
#include "PX2WglExtensions.hpp"

namespace PX2
{

	class RendererInput
	{
	public:
		HWND mWindowHandle;
		HDC mRendererDC;
		int mPixelFormat;
		bool mDisableVerticalSync;
	};

}

#endif