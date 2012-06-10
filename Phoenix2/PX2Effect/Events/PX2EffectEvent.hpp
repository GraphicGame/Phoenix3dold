/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2EffectEvent.hpp
*
* �汾		:	1.0 (2011/12/17)
*
* ����		��	more
*
*/

#ifndef PX2EFFECTEVENT_HPP
#define PX2EFFECTEVENT_HPP

#include "PX2EffectPrerequisites.hpp"
#include "PX2TRange.hpp"
#include "PX2Particle.hpp"

namespace PX2
{

	class ParticleEmitterController;

	class EffectEvent : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EffectEvent);

	public:
		virtual ~EffectEvent ();

		// ʱ��
		TRange<float> GetTimeRange () const;
		void SetTimeRange (const TRange<float> range);

		// ����ʱ��
		/*
		* ���ӷ���������ʱ���TimeRangeץȡһ�����ʱ�䣬��Ϊ����ϵͳ������ȷ
		* ��ʱ�䡣
		*/
		float GetActivateTime () const;
		void SetActivateTime (float actTime);

		// �ı�
		bool IsFadeTo () const;
		void SetBeFadeTo (bool fade);

		// ��������
		virtual void UpdateParticleEmitter (ParticleEmitterController &ctrl);
		virtual void UpdateParticle (Particle &particle);

		// ��һ���¼�
		EffectEvent *NextEvent;

	protected:
		EffectEvent ();
		TRange<float> mTimeRange;

		float mActivateTime;
		bool mIsFadeTo;
	};

	PX2_REGISTER_STREAM(EffectEvent);
	typedef Pointer0<EffectEvent> EffectEventPtr;
#include "PX2EffectEvent.inl"

	//----------------------------------------------------------------------------
	// �����¼��ȽϺ���
	class EffectEvent_CompareFun :
		public std::binary_function <EffectEvent*, EffectEvent*, bool >
	{
	public:
		bool operator()( const EffectEvent *lhs, const EffectEvent *rhs ) const
		{
			return lhs->GetActivateTime() < rhs->GetActivateTime();
		}
	};
	//----------------------------------------------------------------------------

}

#endif