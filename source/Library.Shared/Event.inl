
#include "EventSubscriber.h"
#include "Vector.h"

namespace FieaGameEngine
{
	template<typename T>
	RTTI_DEFINITIONS(Event<T>)

	template<typename T>
	Vector<EventSubscriber*> Event<T>::sSubscribers;

	template<typename T>
	Event<T>::Event(const T& message, bool destroy) :
		EventPublisher(sSubscribers, destroy),
		mMessage(message)
	{
	
	}

	template<typename T>
	void Event<T>::Subscribe(EventSubscriber& subscriber)
	{
		sSubscribers.PushBack(&subscriber);
	} 

	template<typename T>
	void Event<T>::Unsubscribe(EventSubscriber& subscriber)
	{
		sSubscribers.Remove(sSubscribers.Find(&subscriber));
	}

	template<typename T>
	void Event<T>::UnsubscribeAll()
	{
		sSubscribers.Destroy();
	}

	template<typename T>
	const T& Event<T>::Message() const
	{
		return mMessage;
	}

	template<typename T>
	Event<T>::Event(Event&& rhs) :
		EventPublisher(std::move(rhs)),
		mMessage(std::move(rhs.mMessage))
	{

	}

	template<typename T>
	Event<T>& Event<T>::operator=(Event&& rhs)
	{
		if (this != &rhs)
		{
			EventPublisher::operator=(std::move(rhs));
			mMessage = std::move(rhs.mMessage);
		}

		return *this;
	}
}
