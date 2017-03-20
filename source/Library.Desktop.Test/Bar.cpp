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

void Bar::PrintStringToFile(FILE* file, std::int32_t index) const
{
	for (std::int32_t i = 0; i < index; i++)
	{
		fprintf(file, "    ");
	}

	fprintf(file,"Bar %d: ", index);
	fprintf(file, "mIntValue = %d, ", mIntValue);
	fprintf(file, "mFloatValue = %f,", mFloatValue);
	fprintf(file, "mString = %s\n", mString.c_str());

	for (Bar& bar : mChildren)
	{
		bar.PrintStringToFile(file, index + 1);
	}
}
