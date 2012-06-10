/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2ParticleEmitterControl.hpp
*
* �汾		:	1.0 (2011/12/19)
*
* ����		��	more
*
*/

#ifndef PX2PARTICLEEMITTERCONTROL_HPP
#define PX2PARTICLEEMITTERCONTROL_HPP

#include "PX2GraphicsPrerequisites.hpp"
#include "PX2Controller.hpp"
#include "PX2TRecyclingArray.hpp"
#include "PX2TRange.hpp"
#include "PX2Particle.hpp"
#include "PX2EffectEvent.hpp"

namespace PX2
{

	/// ���ӷ�����������
	/**
	* �û�����Ҫ����AttachController(...)���������������ӷ�������
	* ���ӷ���������ʱ�򣬻�Ĭ�ϴ����ÿ�������
	*/
	class ParticleEmitterController : public Controller
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(ParticleEmitterController);

	public:
		ParticleEmitterController ();
		virtual ~ParticleEmitterController ();

		enum EmitterType
		{
			ET_PLANE = 0,
			ET_SPHERE,
			ET_CIRCLE,
			ET_COLUMN,
			ET_MAX_TYPE
		};

		void SetEmitterType (EmitterType type);
		EmitterType GetEmitterType ();

		enum DrawType
		{
			DT_NORMAL,
			DT_OBJECT,
			DT_MAX_TYPE
		};
		void SetDrawType (DrawType type);
		DrawType GetDrawType ();

		enum PlacerType
		{
			PT_PLANE = 0,
			PT_SPHERE,
			PT_SPHEREFACE,
			PT_CIRCLE,
			PT_COLUMNSSPREAD,
			PT_COLUMNUP
		};
		void SetPlacerType (PlacerType type);
		PlacerType GetPlacerType ();

		enum AxisType
		{
			AT_LOCAL,
			AT_GLOBAL,
			AT_MAX_TYPE
		};
		void SetAxisType (AxisType type);
		AxisType GetAxisType ();

		void SetMaxQuantity (int quantity);
		int GetMaxQuantity () const;
		int GetActivateParticleQuantity ();
		TRecyclingArray<Particle>* &GetArray ();

		// Event
		int AttachEffectEvent (EffectEvent *event);
		int DetachEffectEvent (EffectEvent *event);
		EffectEvent *DetachEffectEventAt (int i);
		EffectEvent *SetEffectEvent (int i, EffectEvent *event);
		EffectEvent *GetEffectEvent (int i);
		int GetNumEvents ();

		void Reset ();

		void ConfigeAllEvents ();

		// ����
		virtual bool Update (double applicationTime);

public_internal:
		void SetEmitRate (float rate);
		float GetEmitRate ();
		void SetEmitRateStep (float step);
		float GetEmitRateStep ();

	protected:
		void SortEvents ();
		void CreateEventList ();
		void NailDowmRandTime (); //< �������¼���TimeRange��ΪActivateTime
		void NewAParticle ();
		void UpdateEmitterEvents ();
		void UpdateParticleEvents (Particle &particle);

		TRecyclingArray<Particle> *mParticleArray;
		int mMaxQuantity; // ��Ҫ�־û�

		int mCreatedParticlesQuantity; //< �ܹ���������������(����+����ȥ)
		float mNumNewParticlesExcess;
		double mLastApplicationTime;
		bool mbFirstFrame; //< ��һ֡����������
		float mEmitRate;
		float mEmitRateStep;

		typedef std::vector<EffectEventPtr> EventList;
		typedef std::vector<EffectEventPtr>::iterator EventIt;
		EventList mEvents;
	};

	PX2_REGISTER_STREAM(ParticleEmitterController);
	typedef Pointer0<ParticleEmitterController> ParticleEmitterControllerPtr;
#include "PX2ParticleEmitterControl.inl"

}

#endif