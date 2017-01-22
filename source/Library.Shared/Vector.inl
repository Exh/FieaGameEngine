#pragma once

#include <exception>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

namespace FieaGameEngine
{
    template<typename T>
    Vector<T>::Vector() :
        mBuffer(nullptr),
        mSize(0),
        mCapacity(0)
    {

    }

    template<typename T>
    T& Vector<T>::operator[](int index)
    {
        return const_cast<T&>(const_cast<const Vector<T>*>(this)->operator[](index));
    }

    template<typename T>
    const T& Vector<T>::operator[](unsigned int index) const
    {
        if(index < 0 ||
           index >= mSize)
        {
            throw std::exception("Index out of bounds.");
        }

        assert(mBuffer != nullptr);
        assert(mSize > 0);

        return *(mBuffer + index);
    }

    template<typename T>
    void Vector<T>::PopBack()
    {
        if (mSize > 0)
        {
            assert(mBuffer != nullptr);
            (mBuffer + mSize - 1)->~T();

            mSize--;
        }
    }

    template<typename T>
    bool Vector<T>::IsEmpty() const
    {
        return (mSize == 0);
    }

    template<typename T>
    T& Vector<T>::Front()
    {
        const_cast<T&>(const_cast<Vector<T>*>(this)->Front());
    }

    template<typename T>
    const T& Vector<T>::Front() const
    {
        if (mSize == 0)
        {
            return std::exception("Cannot get front of an empty vector.");
        }

        assert(mBuffer != nullptr);
        return *(mBuffer);
    }

    template<typename T>
    T& Vector<T>::Back()
    {
        const_cast<T&>(const_cast<Vector<T>*>(this)->Back());
    }

    template<typename T>
    const T& Vector<T>::Back() const
    {
        if (mSize == 0)
        {
            return std::exception("Cannot get back of an empty vector.");
        }

        assert(mBuffer != nullptr);
        return *(mBuffer + mSize - 1);
    }

    template<typename T>
    std::uint32_t Vector<T>::Size() const
    {
        return mSize;
    }

    template<typename T>
    std::uint32_t Vector<T>::Capacity() const
    {
        return mCapacity;
    }

    template<typename T>
    Vector<T>::Iterator Vector<T>::begin()
    {
        const_cast<Iterator>(const_cast<const Vector<T>*>(this)->begin());
    }

    template<typename T>
    const Vector<T>::Iterator Vector<T>::begin() const
    {
        return Iterator(this, 0);
    }

    template<typename T>
    Vector<T>::Iterator Vector<T>::end()
    {
        const_cast<Iterator>(const_cast<const Vector<T>*>(this)->begin());
    }

    template<typename T>
    const Vector<T>::Iterator Vector<T>::end() const
    {
        return Iterator(this, mSize);
    }

    template<typename T>
    void Vector<T>::PushBack(const T& item)
    {
        if (mSize == mCapacity)
        {
            Expand();
        }

        new (mBuffer + mSize) T(item);
        mSize++;
    }

    template<typename T>
    Vector<T>::Vector(const Vector& rhs) :
        mBuffer(nullptr),
        mSize(rhs.mSize),
        mCapacity(rhs.mCapacity)
    {
        DeepCopy(rhs);
    }

    template<typename T>
    Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
    {
        if (this != &rhs)
        {
            DeepCopy(rhs);
        }

        return *this;
    }

    template<typename T>
    T& Vector<T>::At(std::uint32_t index)
    {
        return operator[](index);
    }

    template<typename T>
    const T& Vector<T>::At(std::uint32_t index) const
    {
        return operator[](index);
    }

    template<typename T>
    Vector<T>::~Vector()
    {
        //@@ TODO: Change this to use iterator + ranged based for loop
        if (mBuffer != nullptr)
        {
            for (std::uint32_t i = 0; i < mSize; i++)
            {
                (mBuffer + i)->~T();
            }

            free(mBuffer);
            mBuffer = nullptr;
            mSize = 0;
            mCapacity = 0;
        }
        else
        {
            assert(mSize == 0);
            assert(mCapacity == 0);
        }
    }

    template<typename T>
    void Vector<T>::Clear()
    {
        for (int i = 0; i < mSize; i++)
        {
            mBuffer[i].~T();
        }

        mSize = 0;
    }

    template<typename T>
    void Vector<T>::Expand()
    {
        // Expands the capacity of the vector by twice its size.
        // If the vector has 0 capacity, then make it 1.
        if (mCapacity == 0)
        {
            mCapacity = 1;
        }
        else
        {
            mCapacity = mCapacity << 1;
        }

        T* previousBuffer = mBuffer;
        mBuffer = reinterpret_cast<T*>(malloc(sizeof(T) * mCapacity));
        
        if (previousBuffer != nullptr)
        {
            memcpy(mBuffer, previousBuffer, sizeof(T) * mSize);
            free(previousBuffer);
            previousBuffer = nullptr;
        }
        else
        {
            assert(mSize == 0);
            // Capacity was 0, but after expanding, will be 1
            assert(mCapacity == 1);
        }
    }

    template<typename T>
    void Vector<T>::DeepCopy(const Vector& rhs)
    {
        if (mBuffer != nullptr)
        {
            Clear();
            free(mBuffer);
        }

        mSize = rhs.mSize;
        mCapacity = rhs.mCapacity;

        if (mCapacity > 0)
        {
            mBuffer = reinterpret_cast<T*>(malloc(mCapacity * sizeof(T)));
        }

        if (mSize > 0)
        {
            assert(mCapacity != 0);
            assert(mBuffer != nullptr);

            for (std::uint32_t i = 0; i < mSize; i++)
            {
                new (mBuffer + i) T(rhs.mBuffer[i]);
            }
        }
    }











    template<typename T>
    Vector<T>::Iterator::Iterator() :
        mOwner(nullptr),
        mIndex(0)
    {

    }

    template<typename T>
    Vector<T>::Iterator::~Iterator()
    {

    }

    template<typename T>
    Vector<T>::Iterator::Iterator(const Iterator& rhs) :
        mOwner(rhs.mOwner),
        mIndex(rhs.mIndex)
    {

    }

    template<typename T>
    bool Vector<T>::Iterator::operator==(const Iterator& rhs) const
    {
        return mOwner == rhs.mOwner &&
            mIndex == rhs.mIndex;
    }

    template<typename T>
    bool Vector<T>::Iterator::operator!=(const Iterator& rhs) const
    {
        return !operator==(rhs);
    }

    template<typename T>
    typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
    {
        mIndex++;
        
        if (mIndex > mSize)
        {
            mIndex = mSize;
        }
    }

    template<typename T>
    typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int post)
    {
        UNREFERENCED_PARAMETER(post);

        Iterator previous = *this;
        operator++();
        return previous;
    }

    template<typename T>
    T& Vector<T>::Iterator::operator*()
    {
        return const_cast<T&>(const_cast<const Iterator*>(this)->operator*());
    }

    template<typename T>
    const T& Vector<T>::Iterator::operator*() const
    {
        if (mOwner == nullptr ||
            mIndex < 0 ||
            mIndex >= mOwner->mSize)
        {
            throw std::exception("Dereferencing an ownerless or out-of-bounds iterator.");
        }

        return mOwner->mBuffer[mIndex];
    }

    template<typename T>
    typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& rhs)
    {
        if (this != &rhs)
        {
            mOwner = rhs.mOwner;
            mIndex = rhs.mIndex;
        }

        return *this;
    }

    template<typename T>
    Vector<T>::Iterator::Iterator(const Vector* owner,
                                  std::uint32_t index) :
        mOwner(owner),
        mIndex(index)
    {

    }
}
