/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2EventChannel.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2EVENT_HPP
#define PX2EVENT_HPP

#include "PX2EventSystemPrerequisites.hpp"
#include "PX2EventChannel.hpp"
#include "PX2EventHandler.hpp"
#include "PX2EventData.hpp"

namespace PX2
{

	/// ϵͳ�¼�
	enum SystemEvent
	{
		EVENT_NONE = -1,
	};

	/// �¼�����
	class Event
	{
	public:
		typedef int EventType;

	public:
		Event ();
		Event (const Event& event);
		~Event ();

		// ��ֵ
		Event& operator= (const Event& event);

		// �¼�
		void SetEventType (EventType eventType);
		EventType GetEventType ();

		// ͨ��
		void SetChannel (const EventChannel& eventChannel);
		const EventChannel &GetChannel ();

		// ����
		template <class DType>
		void SetData (DType data);

		template <class DType>
		DType GetData ();

		// ����/������
		void SetSender (EventHandler *handler);
		EventHandler* GetSender ();
		void SetReceiver (EventHandler *handler);
		EventHandler* GetReceiver ();

public_internal:
		bool IsSystemEvent () const;
		void SetBeSystemEvent (); //< mEventChannelΪ0��Ϣ
		void Initlize (const Event &event);

		EventChannel mEventChannel;
		EventType mEventType;
		EventData mEventData;
		
		EventHandler* mSender;
		EventHandler* mReceiver;
	};

#include "PX2Event.inl"

}

#endif