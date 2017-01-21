#pragma once

#include <cstdint>

namespace FieaGameEngine
{
    template<typename T>
    class Vector
    {
    public:
        Vector();

        T& operator[](const int index);

        const T& operator[](const int index) const;

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

        void PushBack(T& item);

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
        
        };

    private:


    };
}