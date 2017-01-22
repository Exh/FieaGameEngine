#pragma once

#include <cstdint>

namespace FieaGameEngine
{

    template<typename T>
    class Vector
    {
    public:
        
        class Iterator;

        Vector();

        T& operator[](int index);

        const T& operator[](unsigned int index) const;

        void PopBack();

        bool IsEmpty() const;

        T& Front();

        const T& Front() const;

        T& Back();

        const T& Back() const;

        std::uint32_t Size() const;

        std::uint32_t Capacity() const;

        Iterator begin();

        const Iterator begin() const;

        Iterator end();

        const Iterator end() const;

        void PushBack(const T& item);

        Vector(const Vector& rhs);

        Vector& operator=(const Vector& rhs);

        T& At(std::uint32_t);

        const T& At(std::uint32_t) const;

        ~Vector();

        void Reserve(std::uint32_t capacity);

        Iterator Find(const T& item);

        const Iterator Find(const T& item) const;

        void Clear();

        void Remove(std::uint32_t index);

        void Remove(std::uint32_t begin,
                    std::uint32_t end);

        class Iterator
        {
        public:
            friend Vector;

            Iterator();
            ~Iterator();
            Iterator(const Iterator& rhs);

            bool operator==(const Iterator& rhs) const;
            bool operator!=(const Iterator& rhs) const;

            Iterator& operator++();
            Iterator operator++(int post);

            T& operator*();
            const T& operator*() const;

            Iterator& operator=(const Iterator& rhs);

        private:
            Iterator(const Vector* owner,
                     std::uint32_t index);
            const Vector* mOwner;
            std:int32_t mIndex;
        };

    private:

        void Expand();

        void DeepCopy(const Vector& rhs);

        T* mBuffer;
        std::uint32_t mSize;
        std::uint32_t mCapacity;
    };
}

#include "Vector.inl"