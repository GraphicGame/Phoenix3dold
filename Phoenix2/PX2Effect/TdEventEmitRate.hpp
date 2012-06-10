/*
* Turandot 3D ��Ϸ���� Version 1.0
*
* Copyright (C) 2009-2011 http://www.Turandot3d.org/
*
* �ļ�����	��	TdEventEmitRate.hpp
*
* �汾		:	1.0 (2011/12/18)
*
* ����		��	���
*
*/

#ifndef TDEVENTEMITRATE_HPP
#define TDEVENTEMITRATE_HPP

#include "TdEffectPrerequisites.hpp"
#include "TdEffectEvent.hpp"

namespace Td
{

	// ���Ӵ�С�ı��¼�
	class ParticleEvent_EmitRate : public EffectEvent
	{
		TD_DECLARE_RTTI;
		TD_DECLARE_NAMES;
		TD_DECLARE_STREAM(ParticleEvent_EmitRate);

	public:
		ParticleEvent_EmitRate ();
		virtual ~ParticleEvent_EmitRate ();

		TRange<int> GetRateRange () const;
		bool FadeAllowed ();

		virtual void UpdateParticleEmitter (ParticleEmitterController &ctrl);

	protected:
		TRange<int> mEmitRateRange;
	};

	TD_REGISTER_STREAM(ParticleEvent_EmitRate);
	typedef Pointer0<ParticleEvent_EmitRate> ParticleEvent_EmitRatePtr;
#include "TdEventEmitRate.inl"

}

#endif