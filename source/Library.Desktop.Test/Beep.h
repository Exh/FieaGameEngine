#pragma once

#include "RTTI.h"
#include "Factory.h"

class Boop : public FieaGameEngine::RTTI
{
	RTTI_DECLARATIONS(Boop, FieaGameEngine::RTTI)

public:

	Boop();

	int mBoop;
};

ConcreteFactory(FieaGameEngine::RTTI, Boop)