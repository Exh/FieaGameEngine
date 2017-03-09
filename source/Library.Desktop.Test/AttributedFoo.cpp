#include "pch.h"

#pragma region AttributedFooMethods

const std::int32_t AttributedFoo::INTERNAL_INTEGER_DEFAULT = 1;
const float AttributedFoo::INTERNAL_FLOAT_DEFAULT = 2.0f;
const glm::vec4 AttributedFoo::INTERNAL_VECTOR_DEFAULT(3.0f);
const glm::mat4 AttributedFoo::INTERNAL_MATRIX_DEFAULT(4.0f);
const std::string AttributedFoo::INTERNAL_STRING_DEFAULT("five");

const std::int32_t AttributedFoo::EXTERNAL_INTEGER_DEFAULT = 10;
const float AttributedFoo::EXTERNAL_FLOAT_DEFAULT = 20.0f;
const glm::vec4 AttributedFoo::EXTERNAL_VECTOR_DEFAULT(30.0f);
const glm::mat4 AttributedFoo::EXTERNAL_MATRIX_DEFAULT(40.0f);
const std::string AttributedFoo::EXTERNAL_STRING_DEFAULT("fifty");

const std::string AttributedFoo::EXTERNAL_INTEGER_KEY("ExternalInteger");
const std::string AttributedFoo::EXTERNAL_FLOAT_KEY("ExternalFloat");
const std::string AttributedFoo::EXTERNAL_VECTOR_KEY("ExternalVector");
const std::string AttributedFoo::EXTERNAL_MATRIX_KEY("ExternalMatrix");
const std::string AttributedFoo::EXTERNAL_STRING_KEY("ExternalString");
const std::string AttributedFoo::EXTERNAL_POINTER_KEY("ExternalPointer");

const std::string AttributedFoo::INTERNAL_INTEGER_KEY("InternalInteger");
const std::string AttributedFoo::INTERNAL_FLOAT_KEY("InternalFloat");
const std::string AttributedFoo::INTERNAL_VECTOR_KEY("InternalVector");
const std::string AttributedFoo::INTERNAL_MATRIX_KEY("InternalMatrix");
const std::string AttributedFoo::INTERNAL_STRING_KEY("InternalString");
const std::string AttributedFoo::INTERNAL_POINTER_KEY("InternalPointer");

const std::string AttributedFoo::NESTED_SCOPE_KEY("NestedScope");

RTTI_DEFINITIONS(AttributedFoo)

AttributedFoo::AttributedFoo() :
	mInteger(EXTERNAL_INTEGER_DEFAULT),
	mFloat(EXTERNAL_FLOAT_DEFAULT),
	mGlmVector(EXTERNAL_VECTOR_DEFAULT),
	mMatrix(EXTERNAL_MATRIX_DEFAULT),
	mPointer(&mFoo),
	mNestedScope(nullptr)
{
	Populate();
}

AttributedFoo::~AttributedFoo()
{

}

AttributedFoo::AttributedFoo(const AttributedFoo& rhs)
{
	operator=(rhs);
}

AttributedFoo& AttributedFoo::operator=(const AttributedFoo& rhs)
{
	if (this != &rhs)
	{
		Attributed::operator=(rhs);

		mInteger = rhs.mInteger;
		mFloat = rhs.mFloat;
		mGlmVector = rhs.mGlmVector;
		mMatrix = rhs.mMatrix;
		mString = rhs.mString;
		mFoo = rhs.mFoo;
		mPointer = &mFoo;

		// Scope pointed to by mNestedScope was deleted in Attributed's operator=
		mNestedScope = (*this)[AttributedFoo::NESTED_SCOPE_KEY].GetScope();
	}

	return *this;
}

AttributedFoo::AttributedFoo(AttributedFoo&& rhs) :
	Attributed(std::move(rhs)),
	mInteger(rhs.mInteger),
	mFloat(rhs.mFloat),
	mGlmVector(std::move(rhs.mGlmVector)),
	mMatrix(std::move(rhs.mMatrix)),
	mString(std::move(rhs.mString)),
	mFoo(rhs.mFoo),
	mPointer(&mFoo),
	mNestedScope(rhs.mNestedScope)

{
	rhs.mPointer = nullptr;
	rhs.mNestedScope = nullptr;

	FixNativePointers();
}

AttributedFoo& AttributedFoo::operator=(AttributedFoo&& rhs)
{
	if (this != &rhs)
	{
		Attributed::operator=(std::move(rhs));

		mInteger = rhs.mInteger;
		mFloat = rhs.mFloat;
		mGlmVector = rhs.mGlmVector;
		mMatrix = rhs.mMatrix;
		mString = rhs.mString;
		mFoo = rhs.mFoo;
		mPointer = &mFoo;
		mNestedScope = rhs.mNestedScope;

		rhs.mPointer = nullptr;
		rhs.mNestedScope = nullptr;
	}

	return *this;
}

bool AttributedFoo::operator==(const AttributedFoo& rhs) const
{

	return Attributed::operator==(rhs) &&
		mInteger == rhs.mInteger &&
		mFloat == rhs.mFloat &&
		mGlmVector == rhs.mGlmVector &&
		mMatrix == rhs.mMatrix &&
		mString == rhs.mString &&
		mFoo == rhs.mFoo;
}

bool AttributedFoo::operator!=(const AttributedFoo& rhs) const
{
	return !operator==(rhs);
}

void AttributedFoo::Populate()
{
	Attributed::Populate();

	AddExternalAttribute(EXTERNAL_INTEGER_KEY, &mInteger, 1U);
	AddExternalAttribute(EXTERNAL_FLOAT_KEY, &mFloat, 1U);
	AddExternalAttribute(EXTERNAL_VECTOR_KEY, &mGlmVector, 1U);
	AddExternalAttribute(EXTERNAL_MATRIX_KEY, &mMatrix, 1U);
	AddExternalAttribute(EXTERNAL_STRING_KEY, &mString, 1U);
	AddExternalAttribute(EXTERNAL_POINTER_KEY, &mPointer, 1U);

	AddInternalAttribute(INTERNAL_INTEGER_KEY, INTERNAL_INTEGER_DEFAULT);
	AddInternalAttribute(INTERNAL_FLOAT_KEY, INTERNAL_FLOAT_DEFAULT);
	AddInternalAttribute(INTERNAL_VECTOR_KEY, INTERNAL_VECTOR_DEFAULT);
	AddInternalAttribute(INTERNAL_MATRIX_KEY, INTERNAL_MATRIX_DEFAULT);
	AddInternalAttribute(INTERNAL_STRING_KEY, INTERNAL_STRING_DEFAULT);
	AddInternalAttribute(INTERNAL_POINTER_KEY, &mFoo);

	mNestedScope = new Scope();
	AddNestedScopeAttribute(NESTED_SCOPE_KEY, *mNestedScope);
}

#pragma endregion 
