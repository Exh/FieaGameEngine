
#include "EventSubscriber.h"
#include "Vector.h"

namespace FieaGameEngine
{
	template<typename T>
	RTTI_DEFINITIONS(Event<T>)

	template<typename T>
	Vector<EventSubscriber*> Event<T>::sSubscribers;

	template<typename T>
	Event<T>::Event(const T&, bool destroy) :
		EventPublisher(sSubscribers, destroy),
		mMessage(T)
	{
	
	}

	template<typename T>
	void Event<T>::Subscribe(const EventSubscriber& subscriber)
	{
		sSubscribers.PushBack(&subscriber);
	}

	template<typename T>
	void Event<T>::Unsubscribe(const EventSubscriber& subscriber)
	{
		sSubscribers.Remove(sSubscribers.Find(&subscriber));
	}

	template<typename T>
	void Event<T>::UnsubscribeAll()
	{
		sSubscribers.Clear();
	}

	template<typename T>
	const T& Event<T>::Message() const
	{
		return mMessage;
	}

	template<typename T>
	Event<T>::Event(Event&& rhs) :
		EventPublisher(rhs),
		mMessage(rhs.mMessage)
	{

	}

	template<typename T>
	Event<T>& Event<T>::operator=(Event&& rhs)
	{
		if (this != &rhs)
		{
			EventPublisher::operator=(rhs);
		}
	}
}
