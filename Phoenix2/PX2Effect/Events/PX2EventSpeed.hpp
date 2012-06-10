/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2EventSpeed.hpp
*
* �汾		:	1.0 (2011/12/17)
*
* ����		��	more
*
*/

#ifndef PX2EVENTSPEED_HPP
#define PX2EVENTSPEED_HPP

#include "PX2EffectPrerequisites.hpp"
#include "PX2EffectEvent.hpp"

namespace PX2
{

	// ���Ӵ�С�ı��¼�
	class ParticleEvent_Speed : public EffectEvent
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(ParticleEvent_Speed);

	public:
		ParticleEvent_Speed ();
		virtual ~ParticleEvent_Speed ();

		void SetSpeedRange (const TRange<float> range);
		TRange<float> GetSpeedRange () const;

		bool FadeAllowed ();
		virtual void UpdateParticle (Particle &particle);

	protected:
		TRange<float> mSpeed;
	};

	PX2_REGISTER_STREAM(ParticleEvent_Speed);
	typedef Pointer0<ParticleEvent_Speed> ParticleEvent_SpeedPtr;
#include "PX2EventSpeed.inl"

}

#endif