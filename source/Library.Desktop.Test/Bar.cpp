#include "pch.h"

Bar::Bar() :
	mParent(nullptr),
	mIntValue(0),
	mFloatValue(0.0f)
{

}

Bar::~Bar()
{

}

void Bar::PrintString(std::int32_t index)
{
	for (std::int32_t i = 0; i < index; i++)
	{
		printf("    ");
	}

	printf("Bar %d: ", index);
	printf("mIntValue = %d, ", mIntValue);
	printf("mFloatValue = %f," mFloatValue);
	printf("mString = %s\n", mString.c_str());
	PrintString(index + 1);
}
