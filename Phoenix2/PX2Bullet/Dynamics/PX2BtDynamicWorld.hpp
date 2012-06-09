/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BtDynamicWorld.hpp
*
* �汾		:	1.0 (2011/03/21)
*
* ����		��	more
*
*/

#ifndef PX2BTDYNAMICWORLD_HPP
#define PX2BTDYNAMICWORLD_HPP

#include "PX2BtPreRequisites.hpp"
#include "PX2BtCollisionWorld.hpp"
#include "PX2BtDynamicableRigidBody.hpp"
#include "PX2BtDynamicConstraint.hpp"
#include "PX2BtCollisionDebugDrawer.hpp"

namespace TdBt
{

	class DynamicWorld : public CollisionWorld
	{
	public:
		DynamicWorld (const PX2::AxisAlignedBox3f &bounds, 
			const PX2::Vector3f &gravity, bool init=true,
			bool set32BitAxisSweep=true, unsigned int maxHandles=1500000);
		virtual ~DynamicWorld ();

		// bullet����
		template <class BTDNYWORLDCLASS>
		void CreateBtDynamicWorld (BTDNYWORLDCLASS *&createWorld);
		btDynamicsWorld *GetBulletDynamicWorld () const;

		// ����
		void AddRigidBody (RigidBody *body, short collisionGroup, 
			short collisionMask);
		bool RemoveRigidRody (RigidBody *body);

		void AddConstraint (TypedConstraint *constraint);
		void RemoveConstraint (TypedConstraint *constraint);
		bool IsConstraintIn (TypedConstraint *constraint) const;

		// ��ͨ����
		void AddVehicle(RaycastVehicle *vehicle);

		void StepSimulation (const float elapsedTime, int maxSubSteps=1, 
			const float fixedTimeStep=(1.0f/60.0f));

	private:
		btConstraintSolver *mConstraintSolver;
		std::vector<TypedConstraintPtr> mConstraints;
		std::vector<ActionInterfacePtr> mActionInterfaces;
	};

	typedef PX2::Pointer0<DynamicWorld> DynamicWorldPtr;
#include "PX2BtDynamicWorld.inl"

}

#endif