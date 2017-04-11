#pragma once

#include "EventSubscriber.h"

class BasicSubscriber : public EventSubscriber
{
public:

	BasicSubscriber();

	virtual void Notify(const class EventPublisher& publisher) override;

	bool GetFlag() const;

	void ResetFlag();

private:

	bool mFlag;
};