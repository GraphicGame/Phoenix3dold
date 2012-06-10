/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2UIPrerequisites.hpp
*
* �汾		:	1.0 (2011/02/23)
*
* ����		��	more
*
*/

#ifndef PX2UIPREREQUISITES_HPP
#define PX2UIPREREQUISITES_HPP

#include "PX2GraphicsPrerequisites.hpp"

// Begin Microsoft Windows DLL
#if defined(PX2_UI_DLL_EXPORT)
    #define PX2_UI_ENTRY __declspec(dllexport)
#elif defined(PX2_UI_DLL_IMPORT)
    #define PX2_UI_ENTRY __declspec(dllimport)
#else
    #define PX2_UI_ENTRY
#endif
// End Microsoft Windows DLL

#endif