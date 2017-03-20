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

bool Bar::operator==(const Bar& rhs) const
{
	if (mIntValue != rhs.mIntValue ||
		mFloatValue != rhs.mFloatValue ||
		mString != rhs.mString ||
		mChildren.Size() != rhs.mChildren.Size())
	{
		return false;
	}

	// Assured that size are same
	for (std::uint32_t i = 0; i < mChildren.Size(); i++)
	{
		if (mChildren[i] != rhs.mChildren[i])
		{
			return false;
		}
	}

	return true;
}

bool Bar::operator!=(const Bar& rhs) const
{
	return !operator==(rhs);
}

void Bar::PrintStringToFile(FILE* file, std::int32_t index) const
{
	for (std::int32_t i = 0; i < index; i++)
	{
		fprintf(file, "    ");
	}

	fprintf(file,"[Bar Depth %d: ", index);
	fprintf(file, "mIntValue = %d, ", mIntValue);
	fprintf(file, "mFloatValue = %f, ", mFloatValue);
	fprintf(file, "mString = %s]\n", mString.c_str());

	for (Bar& bar : mChildren)
	{
		bar.PrintStringToFile(file, index + 1);
	}
}
