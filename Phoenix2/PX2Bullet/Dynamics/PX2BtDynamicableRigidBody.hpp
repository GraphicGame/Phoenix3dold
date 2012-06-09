/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BtDynamicableRigidBody.hpp
*
* �汾		:	1.0 (2011/03/17)
*
* ����		��	more
*
*/

#ifndef PX2BTDYNAMICABLERIGIDBODY_HPP
#define PX2BTDYNAMICABLERIGIDBODY_HPP

#include "PX2BtPreRequisites.hpp"
#include "PX2BtCollisionable.hpp"
#include "PX2BtCollisionShape.hpp"
#include "PX2BtConverter.hpp"
#include "PX2BtDynamicConstraint.hpp"
#include "PX2BtDynamicRaycastVehicle.hpp"
#include "PX2BtCollisionWorld.hpp"

namespace TdBt
{

	class DynamicWorld;

	class RigidBody : public Collisionable
	{
	public:
		RigidBody (DynamicWorld *world, const short collisionGroup=0, 
			const short collisionMask=0);
		virtual ~RigidBody();

		// Shapes
		// ����Shapes��ͬʱ�����GetDynamicWorld()->AddRigidBody
		// ������������ʱ�����뿪DynamicWorld��ʱ��
		void SetShape (PX2::Movable *movable, CollisionShape *shape,
			float bodyRestitution, float bodyFriction, float bodyMass, 
			const PX2::Vector3f &pos, const PX2::HQuaternion &quat);

		void SetStaticShape (PX2::Movable *movable, CollisionShape *shape,
			const float bodyRestitution, const float bodyFriction, 
			const float bodyMass, const PX2::Vector3f &pos=PX2::Vector3f::ZERO,
			const PX2::HQuaternion &quat=PX2::HQuaternion::IDENTITY);

		void SetStaticShape (CollisionShape *shape, 
			const float bodyRestitution, const float bodyFriction,
			const PX2::Vector3f &pos=PX2::Vector3f::ZERO,
			const PX2::HQuaternion &quat=PX2::HQuaternion::IDENTITY);

		// linear velocity
		void SetLinearVelocity (const PX2::Vector3f &vel);
		void SetLinearVelocity (const float x, const float y, const float z);
		PX2::Vector3f GetLinearVelocity ();

		// ����
		void ApplayImpulse (const PX2::Vector3f &impulse, 
			const PX2::Vector3f &position);

		// ��
		void ApplayForce (const PX2::Vector3f &impulse, 
			const PX2::Vector3f &position);

		// ����
		void SetKinematicObject (bool kinematic);
		bool IsStaticObject () const;
		bool IsKinematicObject () const;

		// ����
		void DisableDeactivation();
		void EnableActiveState ();
		void ForceActivationState();
		void SetDeactivationTime(const float time);

		// �ʵ�
		const btTransform &GetCenterOfMassTransform () const;
		PX2::HQuaternion GetCenterOfMassOrientation () const;
		PX2::Vector3f GetCenterOfMassPosition () const;
		PX2::Vector3f GetCenterOfMassPivot (const PX2::Vector3f &pivotPosition) const;

		void SetDamping (const float linearDamping, const float angularDamping);

		// bullet����
		btRigidBody* GetBulletRigidBody() const;

		// ��������
		btDynamicsWorld* GetBulletDynamicWorld () const;
		DynamicWorld* GetDynamicWorld ();

	protected:
		// ��ײ����
		short mCollisionGroup;
		short mCollisionMask;

		CollisionShapePtr mCollisionShape;
	};

	typedef PX2::Pointer0<RigidBody> RigidBodyPtr;

	class WheeledRigidBody : public RigidBody
	{
	public:
		WheeledRigidBody (DynamicWorld *world);
		virtual ~WheeledRigidBody ();

		void SetVehicle (RaycastVehicle *vehicle);

	protected:
		RaycastVehicle *mVehicle;
	};

	typedef PX2::Pointer0<WheeledRigidBody> WheeledRigidBodyPtr;
#include "PX2BtDynamicableRigidBody.inl"

}

#endif