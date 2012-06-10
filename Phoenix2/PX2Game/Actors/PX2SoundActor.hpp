/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2SoundActor.hpp
*
* �汾		:	1.0 (2011/04/10)
*
* ����		��	more
*
*/

#ifndef PX2SOUNDACTOR_HPP
#define PX2SOUNDACTOR_HPP

#include "PX2Actor.hpp"
#include "PX2Soundable.hpp"

namespace PX2
{

	class SoundActor : public Actor
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(SoundActor);

	public:
		SoundActor (const char *fileName);
		SoundActor (Soundable *soundable);
		~SoundActor ();

		PX2::Soundable *GetSoundable ();
		void Play ();

		// ��Ϣ����
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (Event *event);
		virtual void DoLeave ();

	protected:
		PX2::SoundablePtr mSoundable;
	};

	PX2_REGISTER_STREAM(SoundActor);
	typedef Pointer0<SoundActor> SoundActorPtr;
#include "PX2SoundActor.inl"

}

#endif