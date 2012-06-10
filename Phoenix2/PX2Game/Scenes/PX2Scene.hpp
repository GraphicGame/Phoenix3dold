/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Scene.hpp
*
* �汾		:	1.0 (2011/04/02)
*
* ����		��	more
*
*/

#ifndef PX2SCENE_HPP
#define PX2SCENE_HPP

#include "PX2GamePrerequisites.hpp"
#include "PX2Node.hpp"
#include "PX2Actor.hpp"
#include "PX2LODTerrainActor.hpp"
#include "PX2RawTerrainActor.hpp"
#include "PX2AmbientRegionActor.hpp"
#include "PX2LightActor.hpp"

namespace PX2
{

	class Scene : public Netable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Scene);

	public:
		Scene ();
		virtual ~Scene ();

		// �����ʼ����Ĭ�Ϲ��캯������
		void InitPhysics (const PX2::AxisAlignedBox3f bounds, 
			const PX2::Vector3f gravity);
		void TermPhysics ();
		void EnablePhysicsSimulation (bool play);
		bool IsPhysicsSimulateion ();

		TdBt::DynamicWorld *GetDynamicWorld ();
		TdBt::DebugDrawer *GetDebugDrawer ();

		void SetSceneID (int id);
		int GetSceneID ();

		virtual void DoUpdate ();

		// �����ڵ��ȡ
		PX2::Node *GetSceneNode ();

		// ��ɫ
		void AddActor (Actor *actor);
		bool RemoveActor (Actor *actor);
		ActorPtr SetActor (int i, Actor* actor);
		bool IsActorIn (Actor *actor);
		int GetActorQuantity ();
		Actor *GetActor (int i);
		Actor *GetActor (PX2::Movable *object);

		// ȱʡ��Դ
		PX2::Light *GetDefaultLight ();

		// ������ɫ
		AmbientRegionActor *GetDefaultARActor ();
		int GetARActorNum ();
		AmbientRegionActor *GetARActor (int i);

		// ����Actor
		PX2::LODTerrainActor *GetLODTerrainActor () { return mLODTerrainActor; }
		PX2::RawTerrainActor *GetRawTerrainActor () { return mRawTerrainActor; }

	protected:
		void Update ();

		CameraPtr mCamera;

		int mSceneID;
		bool mIsFirstFrame;
		double mLastFrameTime;
		bool mPlayPhysicsSimulation;

		NodePtr mSceneNode;
		PX2::LODTerrainActorPtr mLODTerrainActor;
		PX2::RawTerrainActorPtr mRawTerrainActor;

		// Ambient
		PX2::AmbientRigionActorPtr mDefaultARActor;
		PX2::AmbientRigionActorPtr mTwoAmbientRigion[2];
		float mAmbientBlend;
		std::vector<AmbientRigionActorPtr> mARActors;

		// Light
		PX2::LightPtr mDefaultLight;

		// Actors
		std::vector<ActorPtr> mActors;

		// Physics
		TdBt::DynamicWorldPtr mBulletDynamicWorld;
		TdBt::DebugDrawerPtr mDebugDrawer;
	};

	PX2_REGISTER_STREAM(Scene);
	typedef Pointer0<Scene> ScenePtr;

#include "PX2Scene.inl"

}

#endif