/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BtCollisionConvexHullShape.hpp
*
* �汾		:	1.0 (2011/03/16)
*
* ����		��	more
*
*/

#ifndef PX2BTCOLLISIONCONVEXHULLSHAPE_HPP
#define PX2BTCOLLISIONCONVEXHULLSHAPE_HPP

#include "PX2BtCollisionShape.hpp"

namespace TdBt
{

	class ConvexHullCollisionShape : public CollisionShape
	{
	public:
		ConvexHullCollisionShape (const float *points, int numPoints, int stride);
		ConvexHullCollisionShape ();
		ConvexHullCollisionShape (btConvexHullShape *shape);
		virtual ~ConvexHullCollisionShape ();
	};

	typedef PX2::Pointer0<ConvexHullCollisionShape> ConvexHullCollisionShapePtr;

}

#endif