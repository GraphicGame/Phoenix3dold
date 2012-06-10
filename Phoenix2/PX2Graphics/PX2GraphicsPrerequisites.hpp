/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2GraphicsPrerequisites.hpp
*
* �汾		:	1.0 (2011/01/31)
*
* ����		��	more
*
*/

#ifndef PX2GRAPHICSPREREQUISITES_HPP
#define PX2GRAPHICSPREREQUISITES_HPP

#include "PX2MathematicsPrerequisites.hpp"

// Begin Microsoft Windows DLL
#if defined(PX2_GRAPHICS_DLL_EXPORT)
    #define PX2_GRAPHICS_ENTRY __declspec(dllexport)
#elif defined(PX2_GRAPHICS_DLL_IMPORT)
    #define PX2_GRAPHICS_ENTRY __declspec(dllimport)
#else
    #define PX2_GRAPHICS_ENTRY
#endif
// End Microsoft Windows DLL

// ���ϴ˺������������Ƿ����������м�飬ֻ����һ����������飬ֻ
// ��Ҫ����һ����������
#ifdef _DEBUG
    #define PX2_VALIDATE_CAMERA_FRAME_ONCE
#endif

// ���ı���Shader::MAX_PROFILES����shader�־û���ȡʱʹ�ô˺�������ԡ�
#ifdef _DEBUG
    #define PX2_ASSERT_ON_CHANGED_MAX_PROFILES
#endif

// ��������꣬Renderer::Draw (const Renderable*, const MaterialInstance*)��Ⱦ
// ��ϣ��ڲ����ûص�ȱʡ��Ⱦ״̬��
#ifdef _DEBUG
	//#define PX2_RESET_STATE_AFTER_DRAW
#endif

// ���ϴ˺������Ⱦ�������ļ���
// Renderer::DrawPrimitive.
//#define PX2_QUERY_PIXEL_COUNT

#ifdef PX2_USE_OPENGL
    #ifndef __LINUX__
        #define PX2_USE_TEXT_DISPLAY_LIST
    #endif

    // Some OpenGL 2.x drivers are not handling normal attributes correctly.
    // This is a problem should you want to use the normal vector to pass a
    // 4-tuple of information to the shader.  The OpenGL 1.x glNormalPointer
    // assumes the normals are 3-tuples.  If you know that your target
    // machines correctly support OpenGL 2.x normal attributes, expose the
    // following #define.  Otherwise, the renderer will use the OpenGL 1.x
    // glNormalPointer.
    //
    // TODO.  I must be misunderstanding how generic attributes work.  On the
    // Macintosh, whether PowerPC or Intel, with NVIDIA graphics cards, the
    // generic attributes for normals does not work.
    #ifndef __APPLE__
        #define PX2_USE_OPENGL2_NORMAL_ATTRIBUTES
    #endif
#endif

// Dx9��Ⱦ���е�һЩ���
#ifdef PX2_USE_DX9
    #ifdef _DEBUG
        #define PX2_PDR_DEBUG
    #endif
#endif

#endif