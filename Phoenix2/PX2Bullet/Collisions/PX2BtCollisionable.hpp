/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BtCollisionObject.hpp
*
* �汾		:	1.0 (2011/03/07)
*
* ����		��	more
*
*/

#ifndef PX2BTCOLLISIONABLE_HPP
#define PX2BTCOLLISIONABLE_HPP

#include "PX2BtPreRequisites.hpp"
#include "PX2Movable.hpp"

namespace TdBt
{
	
	class CollisionWorld;
	class CollisionShape;
	class CollisionDebugShape;
	class CollisionableState;

	class Collisionable
	{
	public:
		Collisionable (CollisionWorld *world, bool init=true);
		~Collisionable ();	
		
		// bullet��ײ��
		btCollisionObject* GetBulletObject() const;

		// PX2������
		PX2::Movable *GetMovable();

		// PX2�����巽λ
		/*
		* ͨ����Щ�������ı�Movable�ķ�λ,ͬʱbullet�ķ�λҲ�ı䡣
		*/
		void SetPosition (const PX2::APoint &point);
		PX2::APoint GetPosition () const;
		void SetRotation (const PX2::HQuaternion &quat);
		PX2::HQuaternion GetRotation ();
		void SetPosition (const btVector3 &pos);
		void SetRotation (const btQuaternion &quat);
		void SetTransform (const btVector3 &pos, const btQuaternion &quat);
		void SetTransform (const btTransform& worldTrans);

		// ��ײ��״	
		void SetShape (CollisionShape *shape, const PX2::APoint &pos,
			const PX2::HQuaternion &quat);
		CollisionShape *GetShape () const;

		// ��ײ����
		btCollisionWorld* GetBulletCollisionWorld() const;
		CollisionWorld* GetCollisionWorld() const;

	protected:
		CollisionWorld *mWorld;
		PX2::MovablePtr mMovable; 
		PX2::Pointer0<btCollisionObject> mBtCollisionObject;
		PX2::Pointer0<CollisionShape> mShape;
		PX2::Pointer0<CollisionableState> mState;
		PX2::AxisAlignedBox3f mBound;
	};

	typedef PX2::Pointer0<Collisionable> CollisionablePtr;
#include "PX2BtCollisionable.inl"

}

#endif