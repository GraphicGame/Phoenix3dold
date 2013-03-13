/*
*
* �ļ�����	��	PX2Actor.hpp
*
*/

#ifndef PX2ACTOR_HPP
#define PX2ACTOR_HPP

#include "PX2GamePre.hpp"
#include "PX2Netable.hpp"
#include "PX2APoint.hpp"
#include "PX2Movable.hpp"

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
		virtual ~Actor ();

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
		virtual void SetMovable (Movable *movable);
		Movable *GetMovable ();

		// ����
		/*
		* ���ڱ༭����
		*/
		void SetHelpMovable (Movable *movable);
		Movable *GetHelpMovable ();
		void ShowHelpMovable (bool show);
		bool IsHelpMovableShow ();

public_internal:
		void SetScene (Scene *scene);

	protected:
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
	};

	PX2_REGISTER_STREAM(Actor);
	typedef Pointer0<Actor> ActorPtr;
#include "PX2Actor.inl"
	
}

#endif