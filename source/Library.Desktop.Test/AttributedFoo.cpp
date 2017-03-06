#include "pch.h"

#pragma region AttributedFooMethods

RTTI_DEFINITIONS(AttributedFoo)

AttributedFoo::AttributedFoo() :
	mInteger(0),
	mFloat(0.0f),
	mVector(0.0f),
	mMatrix(0.0f)
{

}

AttributedFoo::~AttributedFoo()
{

}

bool AttributedFoo::operator==(const AttributedFoo& rhs) const
{

	return mInteger == rhs.mInteger &&
		mFloat == rhs.mFloat &&
		mVector == rhs.mVector &&
		mMatrix == rhs.mMatrix &&
		mString == rhs.mString &&
		mFoo == rhs.mFoo;
}

void AttributedFoo::Populate()
{
	
}

#pragma endregion 
