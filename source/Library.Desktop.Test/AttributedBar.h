#pragma once

#include "RTTI.h"
#include "Attributed.h"
#include "Scope.h"
#include "Foo.h"

class AttributedBar : public AttributedFoo
{
	RTTI_DECLARATIONS(AttributedBar, AttributedFoo)

public:

	static const std::int32_t INTEGER_DEFAULT;
	static const float FLOAT_DEFAULT;

	static const std::string INTEGER_KEY;
	static const std::string FLOAT_KEY;
	static const std::string SCOPE_KEY;

	AttributedBar();

	virtual ~AttributedBar();

	AttributedBar(const AttributedBar& rhs);
	AttributedBar& operator=(const AttributedBar& rhs);

	AttributedBar(AttributedBar&& rhs);
	AttributedBar& operator=(AttributedBar&& rhs);

	bool operator==(const AttributedBar& rhs) const;
	bool operator!=(const AttributedBar& rhs) const;

	virtual void Populate();

	std::int32_t mBarInteger;
	Scope* mBarScope;
};
