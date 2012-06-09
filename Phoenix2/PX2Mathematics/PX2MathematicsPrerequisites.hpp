/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2MathematicsPrerequisites.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2MATHEMATICSPREREQUISITES_HPP
#define PX2MATHEMATICSPREREQUISITES_HPP

#include "PX2CorePrerequisites.hpp"

// Begin Microsoft Windows DLL
#if defined(PX2_MATHEMATICS_DLL_EXPORT)
    #define PX2_MATHEMATICS_ENTRY __declspec(dllexport)
#elif defined(PX2_MATHEMATICS_DLL_IMPORT)
    #define PX2_MATHEMATICS_ENTRY __declspec(dllimport)
#else
    #define PX2_MATHEMATICS_ENTRY
#endif
// End Microsoft Windows DLL

#endif