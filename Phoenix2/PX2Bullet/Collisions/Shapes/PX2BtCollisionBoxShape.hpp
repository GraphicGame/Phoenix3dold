/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BtCollisionBoxShape.hpp
*
* �汾		:	1.0 (2011/03/07)
*
* ����		��	more
*
*/

#ifndef PX2BTCOLLISIONBOXSHAPE_HPP
#define PX2BTCOLLISIONBOXSHAPE_HPP

#include "PX2BtCollisionShape.hpp"

namespace TdBt
{

	// ��װ��ײ��
	class BoxCollisionShape : public CollisionShape
	{
	public:
		BoxCollisionShape (const PX2::Vector3f &boxBounds);
		virtual ~BoxCollisionShape();
	};

	typedef PX2::Pointer0<BoxCollisionShape> BoxCollisionShapePtr;

}

#endif