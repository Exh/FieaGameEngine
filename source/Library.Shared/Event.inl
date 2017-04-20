
#include "EventSubscriber.h"
#include "Vector.h"
#include <mutex>

namespace FieaGameEngine
{
	template<typename T>
	RTTI_DEFINITIONS(Event<T>)

	template<typename T>
	Vector<EventSubscriber*> Event<T>::sSubscribers;

	template<typename T>
	std::recursive_mutex Event<T>::sMutex;

	template<typename T>
	Event<T>::Event(const T& message, bool destroy) :
		EventPublisher(sSubscribers, sMutex, destroy),
		mMessage(message)
	{
	
	}

	template<typename T>
	void Event<T>::Subscribe(EventSubscriber& subscriber)
	{
		std::lock_guard<std::recursive_mutex> guard(sMutex);
		sSubscribers.PushBack(&subscriber);
	} 

	template<typename T>
	void Event<T>::Unsubscribe(EventSubscriber& subscriber)
	{
		std::lock_guard<std::recursive_mutex> guard(sMutex);
		sSubscribers.Remove(sSubscribers.Find(&subscriber));
	}

	template<typename T>
	void Event<T>::UnsubscribeAll()
	{
		std::lock_guard<std::recursive_mutex> guard(sMutex);
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
