#pragma once

class Foo
{
public:

    Foo();

    Foo(int data,
        int heapData);

    ~Foo();

    Foo(const Foo& rhs);

    Foo& operator=(const Foo& rhs);

    bool operator==(const Foo& rhs) const;

    int GetData() const;

    int GetHeapData() const;

    void SetData(int data);

    void SetHeapData(int data);

private:

    int mData;
    int* mHeapData;
};

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