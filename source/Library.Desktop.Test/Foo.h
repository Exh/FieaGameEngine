#pragma once

#include "RTTI.h"
#include "Factory.h"

class Foo : public FieaGameEngine::RTTI
{
	RTTI_DECLARATIONS(Foo, FieaGameEngine::RTTI)

public:

    Foo();

    Foo(int data,
        int heapData);

    ~Foo();

    Foo(const Foo& rhs);

    Foo& operator=(const Foo& rhs);

    bool operator==(const Foo& rhs) const;

	bool operator!=(const Foo& rhs) const;

    int GetData() const;

    int GetHeapData() const;

    void SetData(int data);

    void SetHeapData(int data);

	bool Equals(const RTTI* rhs) const override;

	class FooHashFunctor
	{
	public:

		std::uint32_t operator()(const Foo& key) const;

		std::uint32_t operator()(Foo* key) const;

	private:

		std::uint32_t AdditiveHash(const std::uint8_t* data, std::uint32_t size) const;

	};


private:

    int mData;
    int* mHeapData;
};

ConcreteFactory(FieaGameEngine::RTTI, Foo)

//class FooFactory : public FieaGameEngine::Factory<FieaGameEngine::RTTI>
//{
//public:
//
//	FooFactory()
//	{
//		FieaGameEngine::Factory<FieaGameEngine::RTTI>::Add(*this);
//	}
//
//	~FooFactory()
//	{
//		FieaGameEngine::Factory<FieaGameEngine::RTTI>::Remove(*this);
//	}
//
//	virtual std::string ClassName()
//	{
//		return "Foo";
//	}
//
//	virtual FieaGameEngine::RTTI* Create()
//	{
//		FieaGameEngine::RTTI* product = new Foo();
//		assert(product != nullptr);
//		return product;
//	}
//};


namespace Microsoft
{
    namespace VisualStudio
    {
        namespace CppUnitTestFramework
        {
            template<>
            inline std::wstring ToString<Foo>(const Foo& foo)
            {
                (foo);
                    return L"Foo string!";
            }
        }
    }
}