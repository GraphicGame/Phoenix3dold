/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Actor.hpp
*
* �汾		:	1.0 (2011/02/25)
*
* ����		��	more
*
*/

#ifndef PX2ACTOR_HPP
#define PX2ACTOR_HPP

#include "PX2GamePrerequisites.hpp"
#include "PX2Netable.hpp"

namespace PX2
{

	class Scene;

	class Actor : public Netable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Actor);

	public:
		Actor ();
		~Actor ();

		// ����
		PX2::Scene *GetScene ();

		// ��λ	
		virtual void SetScale (APoint &scale);
		virtual void SetRotation (APoint &rolate);
		virtual void SetPosition (APoint &position);
		APoint GetScale ();
		APoint GetRotation ();
		APoint GetPosition ();

		// Steering
		AVector GetVelocity () { return mVelocity; }
		double GetMass () { return mMass; }
		double GetMaxSpeed () { return mMaxSpeed; }
		double GetMaxForce () { return mMaxForce; }
		double GetMaxTurnRate () { return mMaxTurnRate; }

		void SetVisible (bool visible);
		bool IsVisible ();

		void SetTransparent (float alpha);
		float GetTransparent ();

		// ģ��
		void SetMovable (Movable *movable);
		Movable *GetMovable ();

		// ����
		/*
		* ���ڱ༭����
		*/
		void SetHelpMovable (Movable *movable);
		Movable *GetHelpMovable ();
		void ShowHelpMovable (bool show);
		bool IsHelpMovableShow ();

		// ����
		void SetDoPhysicsSimulateion (bool simulate);
		bool IsDoPhysicsSimulateion ();
		void SetPhysicsStatic (bool stat);
		bool IsPhysicsStatic ();
		virtual void EnablePhysics (bool enable);
		bool IsPhysicsEnabled ();
		TdBt::RigidBody *GetRigidBody ();

		//enum PhysicsEnabledMode
		//{
		//	PEM_MODELBUILDIN, // �ڽ���ģ�ͣ�ģ���ڲ����Ʊ��ΪPhysics�Ľڵ�
		//	PEM_MODEL, // ģ������
		//	PEM_ATTACH, // �����а����ȥ�Ľڵ�
		//	PEM_MAX_MODE
		//};
		//void SetPhysicsMode (PhysicsEnabledMode mode);
		//PhysicsEnabledMode GetPhysicsEnabledMode ();

public_internal:
		void SetScene (Scene *scene);

	protected:
		void _EnablePhysics ();
		void _DisablePhysics ();

		/// ʹ��һ������ָ��ָ�򱻿��ƵĶ��󡣱���ѭ������
		Scene *mScene;

		// trans
		APoint mScale;
		APoint mRotation;
		APoint mPosition;
		APoint mOriginScale; // ������������ԭ
		APoint mOriginRotation;
		APoint mOriginPosition;

		// steering
		AVector mVelocity;
		double mMass;
		double mMaxSpeed;
		double mMaxForce;
		double mMaxTurnRate;

		bool mVisible;
		float mTransAlpha;

		MovablePtr mMovable;

		// �����
		MovablePtr mHelpMovable;
		bool mShowHelpMovable;

		// Physics
		bool mDoPhysicsSimulateion;
		bool mPhysicsStatic;
		bool mPhysicsEnabled;
		TdBt::RigidBodyPtr mRigidBody;
	};

	PX2_REGISTER_STREAM(Actor);
	typedef Pointer0<Actor> ActorPtr;
#include "PX2Actor.inl"
	
}

#endif