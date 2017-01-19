#include "pch.h"

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
