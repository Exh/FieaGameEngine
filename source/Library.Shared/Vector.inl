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

    /************************************************************************/
    /** ADD ITERATOR BEGIN() AND END() METHODS HERE                         */
    /************************************************************************/
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
        mBuffer = (T*) malloc(sizeof(T) * mCapacity);
        
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
}
