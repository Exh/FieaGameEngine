#pragma once

#include "RTTI.h"
#include "Scope.h"
#include "Foo.h"

class AttributedFoo : public FieaGameEngine::Attributed
{
	RTTI_DECLARATIONS(AttributedFoo, FieaGameEngine::Attributed)

public:

	// Defaults
	static const std::int32_t INTERNAL_INTEGER_DEFAULT;
	static const float INTERNAL_FLOAT_DEFAULT;
	static const glm::vec4 INTERNAL_VECTOR_DEFAULT;
	static const glm::mat4 INTERNAL_MATRIX_DEFAULT;
	static const std::string INTERNAL_STRING_DEFAULT;

	static const std::int32_t EXTERNAL_INTEGER_DEFAULT;
	static const float EXTERNAL_FLOAT_DEFAULT;
	static const glm::vec4 EXTERNAL_VECTOR_DEFAULT;
	static const glm::mat4 EXTERNAL_MATRIX_DEFAULT;
	static const std::string EXTERNAL_STRING_DEFAULT;

	static const std::string EXTERNAL_INTEGER_KEY;
	static const std::string EXTERNAL_FLOAT_KEY;
	static const std::string EXTERNAL_VECTOR_KEY;
	static const std::string EXTERNAL_MATRIX_KEY;
	static const std::string EXTERNAL_STRING_KEY;
	static const std::string EXTERNAL_POINTER_KEY;

	static const std::string INTERNAL_INTEGER_KEY;
	static const std::string INTERNAL_FLOAT_KEY;
	static const std::string INTERNAL_VECTOR_KEY;
	static const std::string INTERNAL_MATRIX_KEY;
	static const std::string INTERNAL_STRING_KEY;
	static const std::string INTERNAL_POINTER_KEY;

	static const std::string NESTED_SCOPE_KEY;

	AttributedFoo();

	 virtual ~AttributedFoo();

	AttributedFoo(const AttributedFoo& rhs) = default;

	AttributedFoo& operator=(const AttributedFoo& rhs) = default;

	bool operator==(const AttributedFoo& rhs) const;

	virtual void Populate();

	class AttributedFooHashFunctor
	{
	public:

		std::uint32_t operator()(const AttributedFoo& key) const;

		std::uint32_t operator()(AttributedFoo* key) const;

	private:

		std::uint32_t AdditiveHash(const std::uint8_t* data, std::uint32_t size) const;

	};


public:

	std::int32_t mInteger;
	float mFloat;
	glm::vec4 mVector;
	glm::mat4 mMatrix;
	std::string mString;
	Foo mFoo;
	RTTI* mPointer;
	Scope* mNestedScope;
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