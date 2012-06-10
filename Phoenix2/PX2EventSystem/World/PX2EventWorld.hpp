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

#ifndef PX2EVENTWORLD_HPP
#define PX2EVENTWORLD_HPP

#include "PX2EventSystemPrerequisites.hpp"
#include "PX2EventHandler.hpp"
#include "PX2Singleton.hpp"

namespace PX2
{

	/// ��Ϣ����
	class EventWorld : public Singleton<EventWorld>
	{
	public:
		EventWorld ();
		~EventWorld ();

		// ��ʼ��/�ͷ�
		bool Initlize ();
		bool Ternamate (); //< ��Ϣ�����ͷţ���ʣ����Ϣ�㲥���

		// ��Ϣ���
		void ComeIn (EventHandler *handler);
		void GoOut (EventHandler *handler);

		/// ����
		/**
		* 1.Ϊÿ���¼�������һ���µĸ�����Ϣ
		* 2.�ַ������¼������¼�������Ӧ����
		*/
		void Update ();

		/// �㲥������Ϣ
		/**
		* ����Ϣֻ�ܹ㲥��ϵͳ��Ϣ�������һ��ϵͳ��Ϣ�������һ������ʧ�ܡ�
		*/
		void BroadcastingLocalEvent (Event* event);

		/// �㲥������Ϣ
		/**
		*
		*/
		void BroadcastingNetEvent (Event* event);

	private:
		bool AddHandler (EventHandler* handler);
		void RemoveHandler (EventHandler* handler);
		void UpdateEvent ();
		void _BroadcastingEvent (Event* event);
		void SwapEventList ();

		typedef std::vector<Event*> EventList;
		typedef std::vector<EventHandler*> EventHandlerList;

		EventList* mNowEventList;
		EventList* mNextEventList;
		EventHandlerList mHandlers;
	};

	typedef Pointer0<EventWorld> EventWorldPtr;

}

#endif