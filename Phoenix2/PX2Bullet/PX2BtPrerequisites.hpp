/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BtPreRequisites.hpp
*
* �汾		:	1.0 (2011/03/07)
*
* ����		��	more
*
*/

#ifndef PX2BTPREREQUISITES_HPP
#define PX2BTPREREQUISITES_HPP

#include "PX2Core.hpp"
#include "PX2Mathematics.hpp"
#include "PX2Graphics.hpp"

#pragma warning(push) 
#pragma warning(disable : 4127)
#pragma warning(disable : 4200)
#pragma warning(disable : 619)
#pragma warning(disable : 4100)
#include "btBulletCollisionCommon.h"
#include "BulletCollision/Gimpact/btGImpactShape.h"
#include "BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h"
#include "BulletCollision/CollisionShapes/btMinkowskiSumShape.h"
#include "btBulletDynamicsCommon.h"
#pragma warning(pop) 

// Begin Microsoft Windows DLL
#if defined(PX2_BULLET_DLL_EXPORT)
    #define PX2_BT_ENTRY __declspec(dllexport)
#elif defined(PX2_BULLET_DLL_IMPORT)
    #define PX2_BT_ENTRY __declspec(dllimport)
#else
    #define PX2_BT_ENTRY
#endif
// End Microsoft Windows DLL

#endif