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
    T& Vector<T>::operator[](std::uint32_t index)
    {
        return const_cast<T&>(const_cast<const Vector<T>*>(this)->operator[](index));
    }

    template<typename T>
    const T& Vector<T>::operator[](std::uint32_t index) const
    {
        if(index >= mSize)
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
        return const_cast<T&>(const_cast<const Vector<T>*>(this)->Front());
    }

    template<typename T>
    const T& Vector<T>::Front() const
    {
        if (mSize == 0)
        {
            throw std::exception("Cannot get front of an empty vector.");
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
    typename Vector<T>::Iterator Vector<T>::begin()
    {
        return const_cast<Iterator>(const_cast<const Vector<T>*>(this)->begin());
    }

    template<typename T>
    typename const Vector<T>::Iterator Vector<T>::begin() const
    {
        return Iterator(this, 0);
    }

    template<typename T>
    typename Vector<T>::Iterator Vector<T>::end()
    {
        return const_cast<Iterator>(const_cast<const Vector<T>*>(this)->end());
    }

    template<typename T>
    typename const Vector<T>::Iterator Vector<T>::end() const
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
        Destroy();
    }

    template<typename T>
    void Vector<T>::Reserve(std::uint32_t capacity)
    {
        // Do not shrink the array.
        if (capacity > mCapacity)
        {
            // Allocate new, larger buffer
            T* previousBuffer = mBuffer;
            mBuffer = reinterpret_cast<T*>(malloc(sizeof(T) * capacity));

            // Copy only the in-use data of the previous buffer; do not
            // call destructor as the data is simply being moved.
            memcpy(mBuffer, previousBuffer, sizeof(T) * mSize);

            free(previousBuffer);
            previousBuffer = nullptr;
        }
    }

    template<typename T>
    typename Vector<T>::Iterator Vector<T>::Find(const T& item)
    {
        return const_cast<Iterator>(const_cast<const Vector<T>*>(this)->Find(item));
    }

    template<typename T>
    typename const Vector<T>::Iterator Vector<T>::Find(const T& item) const
    {
        for (std::uint32_t i = 0; i < mSize; i++)
        {
            if (mBuffer[i] == item)
            {
                return Iterator(this, i);
            }
        }

        return end();
    }

    template<typename T>
    void Vector<T>::Remove(std::uint32_t index)
    {
        if (index < 0 ||
            index >= mSize)
        {
            throw std::exception("Index out of bounds.");
        }

        assert(mBuffer != nullptr);
        assert(mSize > 0);
        assert(mCapacity > 0);

        mBuffer[index].~T();

        memmove(mBuffer + index, mBuffer + index + 1, (mSize - index - 1) * sizeof(T));

        mSize--;
    }

    template<typename T>
    void Vector<T>::Remove(Iterator it)
    {
        if (it.mOwner != this)
        {
            throw std::exception("Iterator does not belong to this Vector.");
        }

        Remove(it.mIndex);
    }

    template<typename T>
    std::uint32_t Vector<T>::Remove(std::uint32_t begin,
                                    std::uint32_t end)
    {
        if (begin < 0      ||
            begin >= mSize ||
            end   < 0      ||
            end   >= mSize)
        {
            throw std::exception("Index out of bounds.");
        }

        if (begin > end)
        {
            return 0;
        }

        // Destroy objects being removed form list.
        for (uint32_t i = begin; i < end; i++)
        {
            mBuffer[i].~T();
        }

        // Shift data of higher elements downward so that elements in 
        // the vector's buffer are contiguous for random access.
        memmove(mBuffer + begin, mBuffer + (mSize - end - 1), sizeof(T) * (end - begin + 1));

        return end - begin + 1;
    }

    std::uint32_t Vector<T>::Remove(Iterator begin,
                                    Iterator end)
    {
        if (begin.mOwner != this ||
            end.mOwner != this)
        {
            throw std::exception("Iterator does not belong to this Vector.");
        }

        // If the user passed in an iterator equivalent to this->end(),
        // then change the iterator's index to point at the last element 
        // in the list, as the remove is inclusive, and it is assumed that
        // the user wants to remove up to the end of the vector.
        if (end.mIndex == mSize)
        {
            end.mIndex--;
        }

        return Remove(begin.mIndex, end.mIndex);
    }

    void Vector<T>::ShrinkToFit()
    {
        T* previousBuffer = mBuffer;

        mBuffer = reinterpret_cast<T*>(malloc(sizeof(T) * mSize));

        memcpy(m_Buffer, previousBuffer, sizeof(T) * mSize);

        free(previousBuffer);
        previousBuffer = nullptr;
    }

    void Vector<T>::Destroy()
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
        for (std::uint32_t i = 0; i < mSize; i++)
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
