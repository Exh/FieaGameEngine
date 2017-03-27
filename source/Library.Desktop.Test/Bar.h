#pragma once
#include <cstdint>
#include "Vector.h"
#include "Factory.h"

struct Bar
{
	Bar();
	virtual ~Bar();
	Bar(const Bar& rhs);

	bool operator==(const Bar& rhs) const;

	bool operator!=(const Bar& rhs) const;

	void PrintStringToFile(FILE* file, std::int32_t index) const;

	Bar* mParent;
	FieaGameEngine::Vector<Bar> mChildren;
	std::int32_t mIntValue;
	float mFloatValue;
	std::string mString;
};

struct HappyBar : public Bar
{
	HappyBar() = default;
	int mData;
};

ConcreteFactory(Bar, HappyBar)
