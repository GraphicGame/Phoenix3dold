/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2EventSpeedDir.hpp
*
* �汾		:	1.0 (2011/12/22)
*
* ����		��	more
*
*/

#ifndef PX2EVENTSPEEDDIR_HPP
#define PX2EVENTSPEEDDIR_HPP

#include "PX2EffectPrerequisites.hpp"
#include "PX2EffectEvent.hpp"

namespace PX2
{

	// ���Ӵ�С�ı��¼�
	class ParticleEvent_SpeedDir : public EffectEvent
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(ParticleEvent_SpeedDir);

	public:
		ParticleEvent_SpeedDir ();
		virtual ~ParticleEvent_SpeedDir ();

		void SetSpeedDirRange (const TRange<AVector> range);
		TRange<AVector> GetSpeedDirRange () const;

		bool FadeAllowed ();
		virtual void UpdateParticle (Particle &particle);

	protected:
		TRange<AVector> mSpeedDir;
	};

	PX2_REGISTER_STREAM(ParticleEvent_SpeedDir);
	typedef Pointer0<ParticleEvent_SpeedDir> ParticleEvent_SpeedDirPtr;
#include "PX2EventSpeedDir.inl"

}

#endif