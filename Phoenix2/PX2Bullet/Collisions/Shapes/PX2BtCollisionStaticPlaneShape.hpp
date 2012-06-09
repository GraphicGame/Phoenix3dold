/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BtCollisionStaticPlaneShape.hpp
*
* �汾		:	1.0 (2011/03/07)
*
* ����		��	more
*
*/

#ifndef PX2BTCOLLISIONSTATICPLANESHAPE_HPP
#define PX2BTCOLLISIONSTATICPLANESHAPE_HPP

#include "PX2BtCollisionShape.hpp"

namespace TdBt
{

	class StaticPlaneCollisionShape : public CollisionShape
	{
	public:
		StaticPlaneCollisionShape (const PX2::Vector3f normal, float distance);
		virtual ~StaticPlaneCollisionShape();

	protected:
		virtual bool DrawWireFrame (DebugLines *wire, 
			const PX2::APoint &pos = PX2::APoint::ORIGIN, 
			const PX2::HQuaternion &quat = PX2::HQuaternion::IDENTITY) const;
	};

	typedef PX2::Pointer0<StaticPlaneCollisionShape> 
		StaticPlaneCollisionShapePtr;

}

#endif