#include "pch.h"
#include "BasicSubscriber.h"
#include "EventPublisher.h"

BasicSubscriber::BasicSubscriber() :
	mFlag(false)
{

}

void BasicSubscriber::Notify(const EventPublisher& publisher)
{
	publisher;
	mFlag = true;
}

bool BasicSubscriber::GetFlag() const
{
	return mFlag;
}

void BasicSubscriber::ResetFlag()
{
	mFlag = false;
}