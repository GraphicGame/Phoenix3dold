/*
*
* �ļ�����	��	PX2EventWorld.cpp
*
*/

#include "PX2EventWorld.hpp"
#include "PX2Event.hpp"
#include "PX2EventFactory.hpp"
using namespace PX2;

EventWorld::EventWorld ()
{
	mNowEventList = new0 EventList();
	assertion(mNowEventList!=0, "mNowEventList was not created successfully.");

	mNextEventList = new0 EventList();
	assertion(mNextEventList!=0, "mNextEventList was not created successfully.");
}
//----------------------------------------------------------------------------
EventWorld::~EventWorld ()
{
	//Ternamate();

	if (mNowEventList)
	{
		delete0(mNowEventList);
		mNowEventList = 0;
	}

	if (mNextEventList)
	{
		delete0(mNextEventList);
		mNextEventList = 0;
	}
}
//----------------------------------------------------------------------------
bool EventWorld::Initlize ()
{
	return true;
}
//----------------------------------------------------------------------------
bool EventWorld::Ternamate ()
{
	while (!(mNowEventList->empty() && mNextEventList->empty() ) )
	{
		UpdateEvent();
	}

	return true;
}
//----------------------------------------------------------------------------
void EventWorld::ComeIn (EventHandler *handler)
{
	assertion(handler!=0, "handler must not be 0.");

	if (!handler)
		return;

	if (handler->IsInWorld(this))
		return;

	handler->Enter(this);

	Event* event = 0;
	event = EventFactory::GetInstance().CreateEvent();

	if (event)
	{
		event->SetEventType((Event::EventType)EVENT_ADD_HANDLER);
		event->SetBeSystemEvent();
		EventHandler* handlerPtr = handler;
		event->SetData<EventHandler*>(handlerPtr);
		_BroadcastingEvent(event);
	}
}
//----------------------------------------------------------------------------
void EventWorld::GoOut(EventHandler *handler)
{
	assertion(handler!=0, "handler must not be 0.");

	if (!handler)
		return;

	if (!handler->IsInWorld(this))
		return;

	handler->Leave();

	// ����ɾ��
	RemoveHandler(handler);

	Event* event = 0;
	event = EventFactory::GetInstance().CreateEvent();

	if (event)
	{
		event->SetEventType((Event::EventType)EVENT_REMOVE_HANDLER);
		event->SetBeSystemEvent();
		EventHandler* handlerPtr = handler;
		event->SetData<EventHandler*>(handlerPtr);
		_BroadcastingEvent(event);
	}
}
//----------------------------------------------------------------------------
void EventWorld::Update ()
{
	Event* event = 0;
	event = EventFactory::GetInstance().CreateEvent();

	if (event)
	{
		event->SetEventType((Event::EventType)EVENT_UPDATE_HANDLER);
		event->SetBeSystemEvent();
		_BroadcastingEvent(event);
	}

	UpdateEvent();
}
//----------------------------------------------------------------------------
void EventWorld::BroadcastingLocalEvent (Event* event)
{
	if (event->IsSystemEvent())
	{
		assertion(false, "event can't be system event.");
	}

	_BroadcastingEvent(event);
}
//----------------------------------------------------------------------------
void EventWorld::BroadcastingNetEvent (Event* event)
{
	PX2_UNUSED(event);
}
//----------------------------------------------------------------------------
bool EventWorld::AddHandler (EventHandler* handler)
{
	mHandlers.push_back(handler);

	return true;
}
//----------------------------------------------------------------------------
void EventWorld::RemoveHandler (EventHandler* handler)
{
	EventHandlerList::iterator it = mHandlers.begin();

	for (; it!=mHandlers.end(); it++)
	{
		if (*it == handler)
		{
			*it = 0;
			mHandlers.erase(it);
			return;
		}
	}
}
//----------------------------------------------------------------------------
void EventWorld::UpdateEvent ()
{
	EventList::iterator itEvent;
	for (itEvent=mNowEventList->begin();
		itEvent!=mNowEventList->end();
		++itEvent)
	{
		// ϵͳ��Ϣ
		if ((*itEvent)->IsSystemEvent())
		{
			// û��Ƶ������Ϣ
			switch ((*itEvent)->GetEventType())
			{
			case EVENT_ADD_HANDLER:
				AddHandler((*itEvent)->GetData<EventHandler*>());
				break;
			case EVENT_REMOVE_HANDLER:
			//	RemoveHandler((*itEvent)->GetData<EventHandler*>());
				break;
			case EVENT_UPDATE_HANDLER:
				{
					EventHandlerList::iterator itHandler;
					for (itHandler=mHandlers.begin();
						itHandler!=mHandlers.end();
						++itHandler)
					{
						(*itHandler)->Execute(*itEvent);
					}
				}
				break;
			default:
				break;
			}
		}
		// ��ϵͳ��Ϣ
		else
		{
			EventHandler* receiver = (*itEvent)->GetReceiver();
			if (receiver)
			{ // �н�����
				receiver->Execute(*itEvent);
			}
			else
			{ // û�н����ߣ���ѯ
				EventHandlerList::iterator itHandler;
				for (itHandler=mHandlers.begin();
					itHandler!=mHandlers.end();
					++itHandler)
				{
					if ((*itHandler)->GetChannel().IsListening((*itEvent)->GetChannel()))
						(*itHandler)->Execute(*itEvent);
				}
			}
		}

		// ��Ϣ�����꣬����ɾ��
		EventFactory::GetInstance().DestoryEvent(*itEvent);
	}

	mNowEventList->clear();

	SwapEventList();
}
//----------------------------------------------------------------------------
void EventWorld::_BroadcastingEvent (Event* event)
{
	mNextEventList->push_back(event);
}
//----------------------------------------------------------------------------
void EventWorld::SwapEventList()
{
	EventList* tempEventList = 0;

	tempEventList = mNowEventList;
	mNowEventList = mNextEventList;
	mNextEventList = tempEventList;
}
//----------------------------------------------------------------------------