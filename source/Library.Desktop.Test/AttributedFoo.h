#pragma once

#include "RTTI.h"
#include "Scope.h"
#include "Foo.h"

class AttributedFoo : public FieaGameEngine::Attributed
{
	RTTI_DECLARATIONS(AttributedFoo, FieaGameEngine::Scope)

public:

	AttributedFoo();

	~AttributedFoo();

	AttributedFoo(const AttributedFoo& rhs) = default;

	AttributedFoo& operator=(const AttributedFoo& rhs) = default;

	bool operator==(const AttributedFoo& rhs) const;

	virtual void Populate() override;

	class AttributedFooHashFunctor
	{
	public:

		std::uint32_t operator()(const AttributedFoo& key) const;

		std::uint32_t operator()(AttributedFoo* key) const;

	private:

		std::uint32_t AdditiveHash(const std::uint8_t* data, std::uint32_t size) const;

	};


public:

	std::uint32_t mInteger;
	float mFloat;
	glm::vec4 mVector;
	glm::mat4 mMatrix;
	std::string mString;
	Foo mFoo;
};



namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			inline std::wstring ToString<AttributedFoo>(const AttributedFoo& foo)
			{
				(foo);
				return L"AttributedFoo string!";
			}
		}
	}
}