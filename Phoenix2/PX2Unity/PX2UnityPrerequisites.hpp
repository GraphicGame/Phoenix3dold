/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2UnityPrerequisites.hpp
*
* �汾		:	1.0 (2011/07/10)
*
* ����		��	more
*
*/

#ifndef PX2UNITYPREREQUISITES_HPP
#define PX2UNITYPREREQUISITES_HPP

#include "PX2Core.hpp"
#include "PX2Graphics.hpp"

// Begin Microsoft Windows DLL
#if defined(PX2_UNITY_DLL_EXPORT)
#define PX2_UNITY_ENTRY __declspec(dllexport)
#elif defined(PX2_UNITY_DLL_IMPORT)
#define PX2_UNITY_ENTRY __declspec(dllimport)
#else
#define PX2_UNITY_ENTRY
#endif
// End Microsoft Windows DLL

#endif