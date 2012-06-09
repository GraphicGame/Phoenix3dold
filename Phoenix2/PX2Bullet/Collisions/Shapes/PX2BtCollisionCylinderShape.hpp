/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BtCollisionCylinderShape.hpp
*
* �汾		:	1.0 (2011/03/15)
*
* ����		��	more
*
*/

#ifndef PX2BTCOLLISIONCYLINDERSHAPE_HPP
#define PX2BTCOLLISIONCYLINDERSHAPE_HPP

#include "PX2BtCollisionShape.hpp"

namespace TdBt
{

	class CylinderCollisionShape : public CollisionShape
	{
	public:
		CylinderCollisionShape (const PX2::Vector3f &halfExtents,
			const PX2::Vector3f &axe);
		virtual ~CylinderCollisionShape ();
	};

	typedef PX2::Pointer0<CylinderCollisionShape> CylinderCollisionShapePtr;

}

#endif