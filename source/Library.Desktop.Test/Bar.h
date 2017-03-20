#pragma once
#include <cstdint>
#include "Vector.h"

struct Bar
{
	Bar();
	~Bar();

	void PrintString(std::int32_t index);

	Bar* mParent;
	Vector<Bar*> mChildren;
	std::int32_t mIntValue;
	float mFloatValue;
	std::string mString;
};