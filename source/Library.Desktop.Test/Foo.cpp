#include "pch.h"

#pragma region FooMethods

RTTI_DEFINITIONS(Foo)

Foo::Foo() :
	mData(0),
	mHeapData(nullptr)
{
	mHeapData = new int();
}

Foo::Foo(int data,
	int heapData) :
	mData(data),
	mHeapData(nullptr)
{
	mHeapData = new int(heapData);
}

Foo::~Foo()
{
	if (mHeapData != nullptr)
	{
		delete mHeapData;
		mHeapData = nullptr;
	}
}

Foo::Foo(const Foo& rhs) :
	mData(0),
	mHeapData(nullptr)
{
	assert(rhs.mHeapData != nullptr);

	mData = rhs.mData;
	mHeapData = new int(*rhs.mHeapData);
}

Foo& Foo::operator=(const Foo& rhs)
{
	if (this != &rhs)
	{
		assert(rhs.mHeapData != nullptr);
		assert(mHeapData != nullptr);
		mData = rhs.mData;
		*mHeapData = *rhs.mHeapData;
	}

	return *this;
}

bool Foo::operator==(const Foo& rhs) const
{
	assert(mHeapData != nullptr);
	assert(rhs.mHeapData != nullptr);

	return mData == rhs.mData &&
		*mHeapData == *(rhs.mHeapData);
}

int Foo::GetData() const
{
	return mData;
}

int Foo::GetHeapData() const
{
	return *mHeapData;
}

void Foo::SetData(int data)
{
	mData = data;
}

void Foo::SetHeapData(int data)
{
	assert(mHeapData != nullptr);
	*mHeapData = data;
}

#pragma endregion 

#pragma region FooHashFunctorMethods

std::uint32_t Foo::FooHashFunctor::operator()(const Foo& key) const
{
	uint32_t data[2] = { 0, 0 };
	data[0] = key.GetData();
	data[1] = key.GetHeapData();

	return AdditiveHash(reinterpret_cast<uint8_t*>(data), sizeof(uint32_t) * 2);
}

std::uint32_t Foo::FooHashFunctor::operator()(Foo* key) const
{
	uint32_t data[2] = { 0, 0 };

	if (key != nullptr)
	{
		data[0] = key->GetData();
		data[1] = key->GetHeapData();
	}

	return AdditiveHash(reinterpret_cast<uint8_t*>(data), sizeof(uint32_t) * 2);
}

std::uint32_t Foo::FooHashFunctor::AdditiveHash(const std::uint8_t* data, std::uint32_t size) const
{
	static const std::uint8_t C = 13;
	std::uint32_t hash = 0;

	for (std::uint32_t i = 0; i < size; i++)
	{
		hash += C + data[i];
	}

	return hash;
}

#pragma endregion
