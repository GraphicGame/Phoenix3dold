/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2BtCollisionMinkowskiSumShape.hpp
*
* 版本		:	1.0 (2011/03/16)
*
* 作者		：	more
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