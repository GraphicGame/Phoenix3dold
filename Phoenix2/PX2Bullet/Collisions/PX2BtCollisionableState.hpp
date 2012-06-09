/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BtCollisionableState.hpp
*
* �汾		:	1.0 (2011/03/09)
*
* ����		��	more
*
*/

#ifndef PX2BTCOLLISIONABLESTATE_HPP
#define PX2BTCOLLISIONABLESTATE_HPP

#include "PX2BtPreRequisites.hpp"

namespace TdBt
{

	class Collisionable;

	/// ��ײ״̬
	/**
	* bulletʹ����ײ״̬�ı伸������ķ�λ��getWorldTransform������ʼ��������ײ
	* ��ķ�λ���������������ʱ��setWorldTransform������ײ����ķ�λ��
	*/
	class CollisionableState : public btMotionState
	{
	public:
		CollisionableState (Collisionable *object);
		virtual ~CollisionableState ();

		virtual void getWorldTransform (btTransform& worldTrans ) const;
		virtual void setWorldTransform (const btTransform& worldTrans);

	private:
		Collisionable *mCollisionable;
		btTransform mWorldTrans;
	};

	typedef PX2::Pointer0<CollisionableState> CollisionableStatePtr;

}

#endif