/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BtCollisionMinkowskiSumShape.hpp
*
* �汾		:	1.0 (2011/03/16)
*
* ����		��	more
*
*/

#ifndef PX2BTCOLLISIONMINKOWSKISUMSHAPE_HPP
#define PX2BTCOLLISIONMINKOWSKISUMSHAPE_HPP

#include "PX2BtCollisionShape.hpp"

namespace TdBt
{

	class MinkowskiSumCollisionShape : public CollisionShape
	{
	public:
		MinkowskiSumCollisionShape (CollisionShape* shapeA, 
			CollisionShape* shapeB);
		virtual ~MinkowskiSumCollisionShape();
	};

	typedef PX2::Pointer0<MinkowskiSumCollisionShape>
		MinkowskiSumCollisionShapePtr;

}

#endif