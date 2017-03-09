#include "pch.h"

const std::int32_t AttributedBar::INTEGER_DEFAULT = -1;
const float AttributedBar::FLOAT_DEFAULT = -2.0f;

const std::string AttributedBar::INTEGER_KEY("BarInteger");
const std::string AttributedBar::FLOAT_KEY("BarFloat");
const std::string AttributedBar::SCOPE_KEY("BarScope");

RTTI_DEFINITIONS(AttributedBar)

AttributedBar::AttributedBar() :
	mBarInteger(INTEGER_DEFAULT),
	mBarScope(nullptr)
{
	Populate();
}

AttributedBar::~AttributedBar()
{

}

AttributedBar::AttributedBar(const AttributedBar& rhs)
{
	operator=(rhs);
}

AttributedBar& AttributedBar::operator=(const AttributedBar& rhs)
{
	if (this != &rhs)
	{
		AttributedFoo::operator=(rhs);

		mBarInteger = rhs.mBarInteger;

		mBarScope = (*this)[AttributedBar::SCOPE_KEY].GetScope();
	}

	return *this;
}

AttributedBar::AttributedBar(AttributedBar&& rhs) :
	AttributedFoo(std::move(rhs)),
	mBarInteger(rhs.mBarInteger),
	mBarScope(rhs.mBarScope)
{
	rhs.mBarScope = nullptr;

	FixNativePointers();
}

AttributedBar& AttributedBar::operator=(AttributedBar&& rhs)
{
	if (this != &rhs)
	{
		AttributedFoo::operator=(std::move(rhs));

		mBarInteger = rhs.mBarInteger;
		mNestedScope = rhs.mNestedScope;

		rhs.mNestedScope = nullptr;
	}
	
	return *this;
}

bool AttributedBar::operator==(const AttributedBar& rhs) const
{
	return AttributedFoo::operator==(rhs) && 
		mBarInteger == rhs.mBarInteger;
}

bool AttributedBar::operator!=(const AttributedBar& rhs) const
{
	return !operator==(rhs);
}

void AttributedBar::Populate()
{
	AttributedFoo::Populate();

	AddExternalAttribute(INTEGER_KEY, &mBarInteger, 1U);
	AddInternalAttribute(FLOAT_KEY, FLOAT_DEFAULT);
	mBarScope = &AddNestedScopeAttribute(SCOPE_KEY);
}