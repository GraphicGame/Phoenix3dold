/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BtCollisionShape.hpp
*
* �汾		:	1.0 (2011/03/07)
*
* ����		��	more
*
*/

#ifndef PX2BTCOLLISIONSHAPE_HPP
#define PX2BTCOLLISIONSHAPE_HPP

#include "PX2BtPreRequisites.hpp"

namespace TdBt
{
	
	class DebugLines;

	class PX2_BT_ENTRY CollisionShape 
	{
	public:
		CollisionShape();
		virtual ~CollisionShape();

		btCollisionShape* GetBulletShape ();

	protected:
		btCollisionShape *mShape;
	};

	typedef PX2::Pointer0<CollisionShape> CollisionShapePtr;

#include "PX2BtCollisionShape.inl"

}

#endif