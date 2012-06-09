/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BtCollisionSphereShape.hpp
*
* �汾		:	1.0 (2011/03/07)
*
* ����		��	more
*
*/

#ifndef PX2BTCOLLISIONSPHERESHAPE_HPP
#define PX2BTCOLLISIONSPHERESHAPE_HPP

#include "PX2BtCollisionShape.hpp"

namespace TdBt
{

	class SphereCollisionShape : public CollisionShape
	{
	public:
		SphereCollisionShape (const float radius);
		virtual ~SphereCollisionShape ();
	};

	typedef PX2::Pointer0<SphereCollisionShape> SphereCollisionShapePtr;

}

#endif