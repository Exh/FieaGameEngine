#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace Microsoft
{
    namespace VisualStudio
    {
        namespace CppUnitTestFramework
        {
            template<>
            inline std::wstring ToString<Vector<int>::Iterator>(const Vector<int>::Iterator& it)
            {
                (it);
                return L"SList<int>::Iterator string!";
            }

            template<>
            inline std::wstring ToString<Vector<int*>::Iterator>(const Vector<int*>::Iterator& it)
            {
                (it);
                return L"SList<int>::Iterator string!";
            }

            template<>
            inline std::wstring ToString<Vector<Foo>::Iterator>(const Vector<Foo>::Iterator& it)
            {
                (it);
                return L"SList<Foo>::Iterator string!";
            }
        }
    }
}

namespace LibraryDesktopTest
{
    TEST_CLASS(VectorTest)
    {
    public:

        TEST_METHOD_INITIALIZE(Initialize)
        {
#if !defined(NDEBUG)
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
            _CrtMemCheckpoint(&sStartMemState);
#endif
        }

        TEST_METHOD_CLEANUP(Cleanup)
        {
#if !defined(NDEBUG)

            _CrtMemState endMemState, diffMemState;
            _CrtMemCheckpoint(&endMemState);
            if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
            {
                _CrtMemDumpStatistics(&diffMemState);
                Assert::Fail(L"Memory Leaks!");
            }
#endif
        }

        TEST_METHOD(Constructor)
        {
            Vector<int> intVector;
            Assert::IsTrue(intVector.IsEmpty());

            Vector<int*> pointerVector;
            Assert::IsTrue(pointerVector.IsEmpty());

            Vector<Foo> fooVector;
            Assert::IsTrue(fooVector.IsEmpty());
        }

        TEST_METHOD(SubscriptOperator)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            Vector<int> intVector;

            auto intCase1 = [&intVector]() { intVector[0]; };
            Assert::ExpectException<std::exception>(intCase1, L"Out of bounds access threw no exception");

            intVector.PushBack(int1);
            intVector.PushBack(int2);
            intVector.PushBack(int3);

            Assert::AreEqual<int>(intVector[0], int1);
            Assert::AreEqual<int>(intVector[1], int2);
            Assert::AreEqual<int>(intVector[2], int3);
            auto intCase2 = [&intVector]() { intVector[3]; };
            Assert::ExpectException<std::exception>(intCase2, L"Out of bounds access threw no exception");

            const Vector<int>* intConstVector = &intVector;
            Assert::AreEqual<int>((*intConstVector)[1], int2);

            // pointer test
            Vector<int*> pointerVector;

            auto pointerCase1 = [&pointerVector]() { pointerVector[0]; };
            Assert::ExpectException<std::exception>(pointerCase1, L"Out of bounds access threw no exception");

            pointerVector.PushBack(&int1);
            pointerVector.PushBack(&int2);
            pointerVector.PushBack(&int3);

            Assert::AreEqual<int*>(pointerVector[0], &int1);
            Assert::AreEqual<int*>(pointerVector[1], &int2);
            Assert::AreEqual<int*>(pointerVector[2], &int3);
            auto pointerCase2 = [&pointerVector]() { pointerVector[3]; };
            Assert::ExpectException<std::exception>(pointerCase2, L"Out of bounds access threw no exception");

            const Vector<int*>* pointerConstVector = &pointerVector;
            Assert::AreEqual<int*>((*pointerConstVector)[1], &int2);

            // Vector test
            Vector<Foo> fooVector;

            auto fooCase1 = [&fooVector]() { fooVector[0]; };
            Assert::ExpectException<std::exception>(fooCase1, L"Out of bounds access threw no exception");

            fooVector.PushBack(foo1);
            fooVector.PushBack(foo2);
            fooVector.PushBack(foo3);

            Assert::AreEqual<Foo>(fooVector[0], foo1);
            Assert::AreEqual<Foo>(fooVector[1], foo2);
            Assert::AreEqual<Foo>(fooVector[2], foo3);
            auto fooCase2 = [&fooVector](){ fooVector[3]; };
            Assert::ExpectException<std::exception>(fooCase2, L"Out of bounds access threw no exception");

            const Vector<Foo>* fooConstVector = &fooVector;
            Assert::AreEqual<Foo>((*fooConstVector)[1], foo2);
        }

        TEST_METHOD(CopySemantics)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // Copy constructor tests

            // int test
            Vector<int> intVector1;
            intVector1.PushBack(int1);
            intVector1.PushBack(int2);
            intVector1.PushBack(int3);

            Vector<int> intVector2(intVector1);

            Assert::AreEqual<int>(intVector1[0], intVector2[0]);
            Assert::AreEqual<int>(intVector1[1], intVector2[1]);
            Assert::AreEqual<int>(intVector1[2], intVector2[2]);

            // pointer test
            Vector<int*> pointerVector1;
            pointerVector1.PushBack(&int1);
            pointerVector1.PushBack(&int2);
            pointerVector1.PushBack(&int3);

            Vector<int*> pointerVector2(pointerVector1);

            Assert::AreEqual<int*>(pointerVector1[0], pointerVector2[0]);
            Assert::AreEqual<int*>(pointerVector1[1], pointerVector2[1]);
            Assert::AreEqual<int*>(pointerVector1[2], pointerVector2[2]);

            // foo test
            Vector<Foo> fooVector1;
            fooVector1.PushBack(foo1);
            fooVector1.PushBack(foo2);
            fooVector1.PushBack(foo3);

            Vector<Foo> fooVector2(fooVector1);

            Assert::AreEqual<Foo>(fooVector1[0], fooVector2[0]);
            Assert::AreEqual<Foo>(fooVector1[1], fooVector2[1]);
            Assert::AreEqual<Foo>(fooVector1[2], fooVector2[2]);

            // Assignment operator

            // int test
            intVector1.PopBack();
            intVector2 = intVector1;
            Assert::AreEqual<int>(intVector1[0], intVector2[0]);
            Assert::AreEqual<int>(intVector1[1], intVector2[1]);
            Assert::AreEqual<int>(intVector1.Size(), intVector2.Size());

            // pointer test
            pointerVector1.PopBack();
            pointerVector2 = pointerVector1;
            Assert::AreEqual<int*>(pointerVector1[0], pointerVector2[0]);
            Assert::AreEqual<int*>(pointerVector1[1], pointerVector2[1]);
            Assert::AreEqual<int>(pointerVector1.Size(), pointerVector2.Size());

            // foo test
            fooVector1.PopBack();
            fooVector2 = fooVector1;
            Assert::AreEqual<Foo>(fooVector1[0], fooVector2[0]);
            Assert::AreEqual<Foo>(fooVector1[1], fooVector2[1]);
            Assert::AreEqual<int>(fooVector1.Size(), fooVector2.Size());
        }

        TEST_METHOD(PopBack)
        {
            int int1 = 1;
            int int2 = 2;

            Foo foo1(1, 2);
            Foo foo2(2, 3);

            // int test
            Vector<int> intVector;
            intVector.PopBack();
            Assert::AreEqual<unsigned int>(intVector.Size(), 0);
            intVector.PushBack(int1);
            intVector.PushBack(int2);
            intVector.PopBack();
            Assert::AreEqual<int>(intVector[0], int1);
            Assert::AreEqual<unsigned int>(intVector.Size(), 1);
            intVector.PopBack();

            // pointer test
            Vector<int*> pointerVector;
            pointerVector.PopBack();
            Assert::AreEqual<unsigned int>(pointerVector.Size(), 0);
            pointerVector.PushBack(&int1);
            pointerVector.PushBack(&int2);
            pointerVector.PopBack();
            Assert::AreEqual<int*>(pointerVector[0], &int1);
            Assert::AreEqual<unsigned int>(pointerVector.Size(), 1);
            pointerVector.PopBack();

            // Foo test
            Vector<Foo> fooVector;
            fooVector.PopBack();
            Assert::AreEqual<unsigned int>(fooVector.Size(), 0);
            fooVector.PushBack(foo1);
            fooVector.PushBack(foo2);
            fooVector.PopBack();
            Assert::AreEqual<Foo>(fooVector[0], foo1);
            Assert::AreEqual<unsigned int>(fooVector.Size(), 1);
            fooVector.PopBack();
        }

        TEST_METHOD(IsEmpty)
        {
            int int1 = 1;
            Foo foo1(1, 2);

            // int test
            Vector<int> intVector;
            Assert::IsTrue(intVector.IsEmpty());
            intVector.PushBack(int1);
            Assert::IsFalse(intVector.IsEmpty());
            intVector.PopBack();
            Assert::IsTrue(intVector.IsEmpty());

            // pointer test
            Vector<int*> pointerVector;
            Assert::IsTrue(pointerVector.IsEmpty());
            pointerVector.PushBack(&int1);
            Assert::IsFalse(pointerVector.IsEmpty());
            pointerVector.PopBack();
            Assert::IsTrue(pointerVector.IsEmpty());

            // Foo test
            Vector<Foo> fooVector;
            Assert::IsTrue(fooVector.IsEmpty());
            fooVector.PushBack(foo1);
            Assert::IsFalse(fooVector.IsEmpty());
            fooVector.PopBack();
            Assert::IsTrue(fooVector.IsEmpty());
        }

        TEST_METHOD(Front)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            Vector<int> intVector;
            auto intCase1 = [intVector]() { intVector.Front(); };
            Assert::ExpectException<std::exception>(intCase1);
            intVector.PushBack(int1);
            intVector.PushBack(int2);
            intVector.PushBack(int3);
            Assert::AreEqual<int>(intVector.Front(), int1);
            intVector.Remove(0);
            Assert::AreEqual<int>(intVector.Front(), int2);
            intVector.PopBack();
            const Vector<int>* intConstVector = &intVector;
            const int& intConst = intConstVector->Front();
            Assert::AreEqual<int>(intConst, int2);

            // pointer test
            Vector<int*> pointerVector;
            auto pointerCase1 = [pointerVector]() { pointerVector.Front(); };
            Assert::ExpectException<std::exception>(pointerCase1);
            pointerVector.PushBack(&int1);
            pointerVector.PushBack(&int2);
            pointerVector.PushBack(&int3);
            Assert::AreEqual<int*>(pointerVector.Front(), &int1);
            pointerVector.Remove(0);
            Assert::AreEqual<int*>(pointerVector.Front(), &int2);
            pointerVector.PopBack();
            const Vector<int*>* pointerConstVector = &pointerVector;
            int* const & pointerConst = pointerConstVector->Front();
            Assert::AreEqual<int*>(pointerConst, &int2);

            // Foo test
            Vector<Foo> fooVector;
            auto exceptionalFront = [fooVector](){ fooVector.Front(); };
            Assert::ExpectException<std::exception>(exceptionalFront);
            fooVector.PushBack(foo1);
            fooVector.PushBack(foo2);
            fooVector.PushBack(foo3);
            Assert::AreEqual<Foo>(fooVector.Front(), foo1);
            fooVector.Remove(0);
            Assert::AreEqual<Foo>(fooVector.Front(), foo2);
            fooVector.PopBack();
            const Vector<Foo>* constVector = &fooVector;
            const Foo& constFoo = constVector->Front();
            Assert::AreEqual<Foo>(constFoo, foo2);
        }

        TEST_METHOD(Back)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            Vector<int> intVector;
            auto intCase1 = [intVector]() { intVector.Back(); };
            Assert::ExpectException<std::exception>(intCase1);
            intVector.PushBack(int1);
            intVector.PushBack(int2);
            intVector.PushBack(int3);
            Assert::AreEqual<int>(intVector.Back(), int3);
            intVector.Remove(2);
            Assert::AreEqual<int>(intVector.Back(), int2);
            intVector.PopBack();
            const Vector<int>* intConstVector = &intVector;
            const int& intConst = intConstVector->Back();
            Assert::AreEqual<int>(intConst, int1);

            // pointer test
            Vector<int*> pointerVector;
            auto pointerCase1 = [pointerVector]() { pointerVector.Back(); };
            Assert::ExpectException<std::exception>(pointerCase1);
            pointerVector.PushBack(&int1);
            pointerVector.PushBack(&int2);
            pointerVector.PushBack(&int3);
            Assert::AreEqual<int*>(pointerVector.Back(), &int3);
            pointerVector.Remove(2);
            Assert::AreEqual<int*>(pointerVector.Back(), &int2);
            pointerVector.PopBack();
            const Vector<int*>* pointerConstVector = &pointerVector;
            int* const & pointerConst = pointerConstVector->Back();
            Assert::AreEqual<int*>(pointerConst, &int1);

            // Foo test
            Vector<Foo> fooVector;
            auto exceptionalFront = [fooVector]() { fooVector.Back(); };
            Assert::ExpectException<std::exception>(exceptionalFront);
            fooVector.PushBack(foo1);
            fooVector.PushBack(foo2);
            fooVector.PushBack(foo3);
            Assert::AreEqual<Foo>(fooVector.Back(), foo3);
            fooVector.Remove(2);
            Assert::AreEqual<Foo>(fooVector.Back(), foo2);
            fooVector.PopBack();
            const Vector<Foo>* constVector = &fooVector;
            const Foo& constFoo = constVector->Back();
            Assert::AreEqual<Foo>(constFoo, foo1);
        }

        TEST_METHOD(Size)
        {
            int int1 = 1;
            int int2 = 2;

            Foo foo1(1, 2);
            Foo foo2(2, 3);

            // int test
            Vector<int> intVector;
            Assert::AreEqual<int>(intVector.Size(), 0);
            intVector.PushBack(int1);
            Assert::AreEqual<int>(intVector.Size(), 1);
            intVector.PushBack(int2);
            intVector.PushBack(int1);
            Assert::AreEqual<int>(intVector.Size(), 3);
            intVector.PopBack();
            Assert::AreEqual<int>(intVector.Size(), 2);

            // pointer test
            Vector<int*> pointerVector;
            Assert::AreEqual<int>(pointerVector.Size(), 0);
            pointerVector.PushBack(&int1);
            Assert::AreEqual<int>(pointerVector.Size(), 1);
            pointerVector.PushBack(&int2);
            pointerVector.PushBack(&int1);
            Assert::AreEqual<int>(pointerVector.Size(), 3);
            pointerVector.PopBack();
            Assert::AreEqual<int>(pointerVector.Size(), 2);

            // Foo test
            Vector<Foo> fooVector;
            Assert::AreEqual<int>(fooVector.Size(), 0);
            fooVector.PushBack(foo1);
            Assert::AreEqual<int>(fooVector.Size(), 1);
            fooVector.PushBack(foo2);
            fooVector.PushBack(foo1);
            Assert::AreEqual<int>(fooVector.Size(), 3);
            fooVector.PopBack();
            Assert::AreEqual<int>(fooVector.Size(), 2);
        }

        TEST_METHOD(Capacity)
        {
            int int1 = 1;
            int int2 = 2;

            Foo foo1(1, 2);
            Foo foo2(2, 3);

            // int test
            Vector<int> intVector;
            Assert::AreEqual<int>(intVector.Capacity(), 0);
            intVector.PushBack(int1);
            Assert::AreEqual<int>(intVector.Capacity(), 1);
            intVector.PushBack(int2);
            intVector.PushBack(int1);
            Assert::AreEqual<int>(intVector.Capacity(), 4);
            intVector.PopBack();
            Assert::AreEqual<int>(intVector.Capacity(), 4);
            intVector.Reserve(16);
            Assert::AreEqual<int>(intVector.Capacity(), 16);
            intVector.PushBack(int1);
            intVector.PushBack(int2);
            Assert::AreEqual<int>(intVector.Capacity(), 16);
            intVector.Clear();
            Assert::AreEqual<int>(intVector.Capacity(), 16);
            intVector.Destroy();
            Assert::AreEqual<int>(intVector.Capacity(), 0);

            // pointer test
            Vector<int*> pointerVector;
            Assert::AreEqual<int>(pointerVector.Capacity(), 0);
            pointerVector.PushBack(&int1);
            Assert::AreEqual<int>(pointerVector.Capacity(), 1);
            pointerVector.PushBack(&int2);
            pointerVector.PushBack(&int1);
            Assert::AreEqual<int>(pointerVector.Capacity(), 4);
            pointerVector.PopBack();
            Assert::AreEqual<int>(pointerVector.Capacity(), 4);
            pointerVector.Reserve(16);
            Assert::AreEqual<int>(pointerVector.Capacity(), 16);
            pointerVector.PushBack(&int1);
            pointerVector.PushBack(&int2);
            Assert::AreEqual<int>(pointerVector.Capacity(), 16);
            pointerVector.Clear();
            Assert::AreEqual<int>(pointerVector.Capacity(), 16);
            pointerVector.Destroy();
            Assert::AreEqual<int>(pointerVector.Capacity(), 0);

            // Foo test
            Vector<Foo> fooVector;
            Assert::AreEqual<int>(fooVector.Capacity(), 0);
            fooVector.PushBack(foo1);
            Assert::AreEqual<int>(fooVector.Capacity(), 1);
            fooVector.PushBack(foo2);
            fooVector.PushBack(foo1);
            Assert::AreEqual<int>(fooVector.Capacity(), 4);
            fooVector.PopBack();
            Assert::AreEqual<int>(fooVector.Capacity(), 4);
            fooVector.Reserve(16);
            Assert::AreEqual<int>(fooVector.Capacity(), 16);
            fooVector.PushBack(foo1);
            fooVector.PushBack(foo2);
            Assert::AreEqual<int>(fooVector.Capacity(), 16);
            fooVector.Clear();
            Assert::AreEqual<int>(fooVector.Capacity(), 16);
            fooVector.Destroy();
            Assert::AreEqual<int>(fooVector.Capacity(), 0);
        }

        TEST_METHOD(begin)
        {
            int int1 = 1;
            int int2 = 2;

            Foo foo1(1, 2);
            Foo foo2(2, 3);

            // int test
            Vector<int> intVector;
            Assert::AreEqual<Vector<int>::Iterator>(intVector.begin(), intVector.end());
            intVector.PushBack(int1);
            Assert::AreEqual<int>(*(intVector.begin()), int1);
            intVector.PushBack(int2);
            Assert::AreEqual<int>(*(intVector.begin()), int1);
            intVector.Remove(0);
            Assert::AreEqual<int>(*(intVector.begin()), int2);

            // pointer test
            Vector<int*> pointerVector;
            Assert::AreEqual<Vector<int*>::Iterator>(pointerVector.begin(), pointerVector.end());
            pointerVector.PushBack(&int1);
            Assert::AreEqual<int*>(*(pointerVector.begin()), &int1);
            pointerVector.PushBack(&int2);
            Assert::AreEqual<int*>(*(pointerVector.begin()), &int1);
            pointerVector.Remove(0);
            Assert::AreEqual<int*>(*(pointerVector.begin()), &int2);

            // Foo test
            Vector<Foo> fooVector;
            Assert::AreEqual<Vector<Foo>::Iterator>(fooVector.begin(), fooVector.end());
            fooVector.PushBack(foo1);
            Assert::AreEqual<Foo>(*(fooVector.begin()), foo1);
            fooVector.PushBack(foo2);
            Assert::AreEqual<Foo>(*(fooVector.begin()), foo1);
            fooVector.Remove(0);
            Assert::AreEqual<Foo>(*(fooVector.begin()), foo2);
        }

        TEST_METHOD(end)
        {
            int int1 = 1;
            int int2 = 2;

            Foo foo1(1, 2);
            Foo foo2(2, 3);

            // int test
            Vector<int> intVector;
            Assert::AreEqual<Vector<int>::Iterator>(intVector.begin(), intVector.end());

            intVector.PushBack(int1);
            intVector.PushBack(int2);
            int intCount = 0;
            for (auto intIt = intVector.begin(); intIt != intVector.end(); ++intIt)
            {
                intCount++;
            }
            Assert::AreEqual<int>(intCount, 2);

            // pointer test
            Vector<int*> pointerVector;
            Assert::AreEqual<Vector<int*>::Iterator>(pointerVector.begin(), pointerVector.end());

            pointerVector.PushBack(&int1);
            pointerVector.PushBack(&int2);
            int pointerCount = 0;
            for (auto intIt = pointerVector.begin(); intIt != pointerVector.end(); ++intIt)
            {
                pointerCount++;
            }
            Assert::AreEqual<int>(pointerCount, 2);

            // Foo test
            Vector<Foo> fooVector;
            Assert::AreEqual<Vector<Foo>::Iterator>(fooVector.begin(), fooVector.end());

            fooVector.PushBack(foo1);
            fooVector.PushBack(foo2);
            int fooCount = 0;
            for (auto intIt = fooVector.begin(); intIt != fooVector.end(); ++intIt)
            {
                fooCount++;
            }
            Assert::AreEqual<int>(fooCount, 2);
        }

        TEST_METHOD(PushBack)
        {
            int int1 = 1;
            int int2 = 2;

            Foo foo1(1, 2);
            Foo foo2(2, 3);

            // int test
            {
                Vector<int> vector;
                vector.PushBack(int1);
                Assert::AreEqual<int>(vector.Back(), int1);
                vector.PushBack(int2);
                Assert::AreEqual<int>(vector.Back(), int2);
            }

            // pointer test
            {
                Vector<int*> vector;
                vector.PushBack(&int1);
                Assert::AreEqual<int*>(vector.Back(), &int1);
                vector.PushBack(&int2);
                Assert::AreEqual<int*>(vector.Back(), &int2);
            }

            // Foo test
            {
                Vector<Foo> vector;
                vector.PushBack(foo1);
                Assert::AreEqual<Foo>(vector.Back(), foo1);
                vector.PushBack(foo2);
                Assert::AreEqual<Foo>(vector.Back(), foo2);
            }
        }

        TEST_METHOD(At)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            Vector<int> intVector;

            auto intCase1 = [&intVector]() { intVector.At(0)   ; };
            Assert::ExpectException<std::exception>(intCase1, L"Out of bounds access threw no exception");

            intVector.PushBack(int1);
            intVector.PushBack(int2);
            intVector.PushBack(int3);

            Assert::AreEqual<int>(intVector.At(0), int1);
            Assert::AreEqual<int>(intVector.At(1), int2);
            Assert::AreEqual<int>(intVector.At(2), int3);
            auto intCase2 = [&intVector]() { intVector.At(3); };
            Assert::ExpectException<std::exception>(intCase2, L"Out of bounds access threw no exception");

            const Vector<int>* intConstVector = &intVector;
            Assert::AreEqual<int>((*intConstVector).At(1), int2);

            // pointer test
            Vector<int*> pointerVector;

            auto pointerCase1 = [&pointerVector]() { pointerVector.At(0); };
            Assert::ExpectException<std::exception>(pointerCase1, L"Out of bounds access threw no exception");

            pointerVector.PushBack(&int1);
            pointerVector.PushBack(&int2);
            pointerVector.PushBack(&int3);

            Assert::AreEqual<int*>(pointerVector.At(0), &int1);
            Assert::AreEqual<int*>(pointerVector.At(1), &int2);
            Assert::AreEqual<int*>(pointerVector.At(2), &int3);
            auto pointerCase2 = [&pointerVector]() { pointerVector.At(3); };
            Assert::ExpectException<std::exception>(pointerCase2, L"Out of bounds access threw no exception");

            const Vector<int*>* pointerConstVector = &pointerVector;
            Assert::AreEqual<int*>((*pointerConstVector).At(1), &int2);

            // Vector test
            Vector<Foo> fooVector;

            auto fooCase1 = [&fooVector]() { fooVector.At(0); };
            Assert::ExpectException<std::exception>(fooCase1, L"Out of bounds access threw no exception");

            fooVector.PushBack(foo1);
            fooVector.PushBack(foo2);
            fooVector.PushBack(foo3);

            Assert::AreEqual<Foo>(fooVector.At(0), foo1);
            Assert::AreEqual<Foo>(fooVector.At(1), foo2);
            Assert::AreEqual<Foo>(fooVector.At(2), foo3);
            auto fooCase2 = [&fooVector]() { fooVector.At(3); };
            Assert::ExpectException<std::exception>(fooCase2, L"Out of bounds access threw no exception");

            const Vector<Foo>* fooConstVector = &fooVector;
            Assert::AreEqual<Foo>((*fooConstVector).At(1), foo2);
        }

        TEST_METHOD(Reserve)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            {
                Vector<int> vector;
                Assert::AreEqual<int>(vector.Capacity(), 0);
                vector.Reserve(4);
                Assert::AreEqual<int>(vector.Capacity(), 4);
                vector.PushBack(int1);
                Assert::AreEqual<int>(vector.Capacity(), 4);
                vector.PushBack(int1);
                vector.PushBack(int2);
                vector.PushBack(int3);
                vector.PushBack(int1);
                Assert::AreNotEqual<int>(vector.Capacity(), 4);
            }

            // pointer test
            {
                Vector<int*> vector;
                Assert::AreEqual<int>(vector.Capacity(), 0);
                vector.Reserve(4);
                Assert::AreEqual<int>(vector.Capacity(), 4);
                vector.PushBack(&int1);
                Assert::AreEqual<int>(vector.Capacity(), 4);
                vector.PushBack(&int1);
                vector.PushBack(&int2);
                vector.PushBack(&int3);
                vector.PushBack(&int1);
                Assert::AreNotEqual<int>(vector.Capacity(), 4);
            }

            // Foo test
            {
                {
                    Vector<Foo> vector;
                    Assert::AreEqual<int>(vector.Capacity(), 0);
                    vector.Reserve(4);
                    Assert::AreEqual<int>(vector.Capacity(), 4);
                    vector.PushBack(foo1);
                    Assert::AreEqual<int>(vector.Capacity(), 4);
                    vector.PushBack(foo1);
                    vector.PushBack(foo2);
                    vector.PushBack(foo3);
                    vector.PushBack(foo1);
                    Assert::AreNotEqual<int>(vector.Capacity(), 4);
                }
            }
        }

        TEST_METHOD(Find)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            {
                Vector<int> vector;
                Vector<int>::Iterator it = vector.Find(int1);
                Assert::AreEqual<Vector<int>::Iterator>(it, vector.end());
                vector.PushBack(int1);
                vector.PushBack(int2);
                vector.PushBack(int3);
                it = vector.Find(int2);
                Assert::AreEqual<int>(*it, int2);
                ++it;
                ++it;
                Assert::AreEqual<Vector<int>::Iterator>(it, vector.end());
            }

            // pointer test
            {
                Vector<int*> vector;
                Vector<int*>::Iterator it = vector.Find(&int1);
                Assert::AreEqual<Vector<int*>::Iterator>(it, vector.end());
                vector.PushBack(&int1);
                vector.PushBack(&int2);
                vector.PushBack(&int3);
                it = vector.Find(&int2);
                Assert::AreEqual<int*>(*it, &int2);
                ++it;
                ++it;
                Assert::AreEqual<Vector<int*>::Iterator>(it, vector.end());
            }

            // Foo test
            {
                Vector<Foo> vector;
                Vector<Foo>::Iterator it = vector.Find(foo1);
                Assert::AreEqual<Vector<Foo>::Iterator>(it, vector.end());
                vector.PushBack(foo1);
                vector.PushBack(foo2);
                vector.PushBack(foo3);
                it = vector.Find(foo2);
                Assert::AreEqual<Foo>(*it, foo2);
                ++it;
                ++it;
                Assert::AreEqual<Vector<Foo>::Iterator>(it, vector.end());
            }
        }

        TEST_METHOD(Clear)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            {
                Vector<int> vector;
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
                vector.Clear();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
                vector.PushBack(int1);
                vector.PushBack(int2);
                vector.PushBack(int3);
                Assert::AreEqual<int>(vector.Size(), 3);
                Assert::AreEqual<int>(vector.Capacity(), 4);
                vector.Clear();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 4);
            }

            // pointer test
            {
                Vector<int*> vector;
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
                vector.Clear();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
                vector.PushBack(&int1);
                vector.PushBack(&int2);
                vector.PushBack(&int3);
                Assert::AreEqual<int>(vector.Size(), 3);
                Assert::AreEqual<int>(vector.Capacity(), 4);
                vector.Clear();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 4);
            }

            // Foo test
            {
                Vector<Foo> vector;
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
                vector.Clear();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
                vector.PushBack(foo1);
                vector.PushBack(foo2);
                vector.PushBack(foo3);
                Assert::AreEqual<int>(vector.Size(), 3);
                Assert::AreEqual<int>(vector.Capacity(), 4);
                vector.Clear();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 4);
            }
        }

        TEST_METHOD(Remove)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            {
                Vector<int> vector;
                Assert::IsFalse(vector.Remove(vector.Find(int1)));
                vector.PushBack(int1);
                Assert::IsTrue(vector.Remove(vector.Find(int1)));
                Assert::AreEqual<int>(vector.Size(), 0);
                vector.PushBack(int1);
                vector.PushBack(int2);
                vector.PushBack(int3);
               Assert::IsTrue(vector.Remove(vector.Find(int2)));
               Assert::AreEqual<int>(vector.Size(), 2);
               Assert::IsTrue(vector.Remove(vector.Find(int3)));
               Assert::AreEqual<int>(vector.Size(), 1);
               Assert::IsFalse(vector.Remove(vector.Find(int3)));
               Assert::AreEqual<int>(vector.Size(), 1);
            }

            // pointer test
            {
                Vector<int*> vector;
                Assert::IsFalse(vector.Remove(vector.Find(&int1)));
                vector.PushBack(&int1);
                Assert::IsTrue(vector.Remove(vector.Find(&int1)));
                Assert::AreEqual<int>(vector.Size(), 0);
                vector.PushBack(&int1);
                vector.PushBack(&int2);
                vector.PushBack(&int3);
                Assert::IsTrue(vector.Remove(vector.Find(&int2)));
                Assert::AreEqual<int>(vector.Size(), 2);
                Assert::IsTrue(vector.Remove(vector.Find(&int3)));
                Assert::AreEqual<int>(vector.Size(), 1);
                Assert::IsFalse(vector.Remove(vector.Find(&int3)));
                Assert::AreEqual<int>(vector.Size(), 1);
            }

            // Foo test
            {
                Vector<Foo> vector;
                Assert::IsFalse(vector.Remove(vector.Find(foo1)));
                vector.PushBack(foo1);
                Assert::IsTrue(vector.Remove(vector.Find(foo1)));
                Assert::AreEqual<int>(vector.Size(), 0);
                vector.PushBack(foo1);
                vector.PushBack(foo2);
                vector.PushBack(foo3);
                Assert::IsTrue(vector.Remove(vector.Find(foo2)));
                Assert::AreEqual<int>(vector.Size(), 2);
                Assert::IsTrue(vector.Remove(vector.Find(foo3)));
                Assert::AreEqual<int>(vector.Size(), 1);
                Assert::IsFalse(vector.Remove(vector.Find(foo3)));
                Assert::AreEqual<int>(vector.Size(), 1);
            }
        }

        TEST_METHOD(IteratorEqualityOperator)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            {
                Vector<int> vector;
                Vector<int>::Iterator it;
                Assert::AreNotEqual<Vector<int>::Iterator>(it, vector.begin());
                Assert::AreNotEqual<Vector<int>::Iterator>(it, vector.end());
                vector.PushBack(int1);
                vector.PushBack(int2);
                vector.PushBack(int3);
                Assert::AreEqual<Vector<int>::Iterator>(vector.Find(int1), vector.begin());
                Assert::AreNotEqual<Vector<int>::Iterator>(vector.Find(int2), vector.begin());
                Vector<int> vector2;
                vector2.PushBack(int1);
                vector2.PushBack(int2);
                Assert::AreNotEqual<Vector<int>::Iterator>(vector.Find(int2), vector2.Find(int2));
                Assert::AreNotEqual<Vector<int>::Iterator>(vector.begin(), vector2.begin());
                Assert::AreNotEqual<Vector<int>::Iterator>(vector.end(), vector2.end());
            }

            // pointer test
            {
                Vector<int*> vector;
                Vector<int*>::Iterator it;
                Assert::AreNotEqual<Vector<int*>::Iterator>(it, vector.begin());
                Assert::AreNotEqual<Vector<int*>::Iterator>(it, vector.end());
                vector.PushBack(&int1);
                vector.PushBack(&int2);
                vector.PushBack(&int3);
                Assert::AreEqual<Vector<int*>::Iterator>(vector.Find(&int1), vector.begin());
                Assert::AreNotEqual<Vector<int*>::Iterator>(vector.Find(&int2), vector.begin());
                Vector<int*> vector2;
                vector2.PushBack(&int1);
                vector2.PushBack(&int2);
                Assert::AreNotEqual<Vector<int*>::Iterator>(vector.Find(&int2), vector2.Find(&int2));
                Assert::AreNotEqual<Vector<int*>::Iterator>(vector.begin(), vector2.begin());
                Assert::AreNotEqual<Vector<int*>::Iterator>(vector.end(), vector2.end());
            }

            // Foo test
            {
                Vector<Foo> vector;
                Vector<Foo>::Iterator it;
                Assert::AreNotEqual<Vector<Foo>::Iterator>(it, vector.begin());
                Assert::AreNotEqual<Vector<Foo>::Iterator>(it, vector.end());
                vector.PushBack(foo1);
                vector.PushBack(foo2);
                vector.PushBack(foo3);
                Assert::AreEqual<Vector<Foo>::Iterator>(vector.Find(foo1), vector.begin());
                Assert::AreNotEqual<Vector<Foo>::Iterator>(vector.Find(foo2), vector.begin());
                Vector<Foo> vector2;
                vector2.PushBack(foo1);
                vector2.PushBack(foo2);
                Assert::AreNotEqual<Vector<Foo>::Iterator>(vector.Find(foo2), vector2.Find(foo2));
                Assert::AreNotEqual<Vector<Foo>::Iterator>(vector.begin(), vector2.begin());
                Assert::AreNotEqual<Vector<Foo>::Iterator>(vector.end(), vector2.end());
            }
        }

        TEST_METHOD(IncrementOperator)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            {
                Vector<int> vector;
                Vector<int>::Iterator it;
                auto case1 = [&it]{++it;};
                auto case2 = [&it]{it++;};
                Assert::ExpectException<std::exception>(case1);
                Assert::ExpectException<std::exception>(case2);
                it = vector.begin();
                ++it;
                it++;
                vector.PushBack(int1);
                vector.PushBack(int2);
                vector.PushBack(int3);
                Assert::AreEqual(*(it++), int1);
                Assert::AreEqual(*(it), int2);
                Assert::AreEqual(*(++it), int3);
            }

            // pointer test
            {
                Vector<int*> vector;
                Vector<int*>::Iterator it;
                auto case1 = [&it] {++it;};
                auto case2 = [&it] {it++;};
                Assert::ExpectException<std::exception>(case1);
                Assert::ExpectException<std::exception>(case2);
                it = vector.begin();
                ++it;
                it++;
                vector.PushBack(&int1);
                vector.PushBack(&int2);
                vector.PushBack(&int3);
                Assert::AreEqual(*(it++), &int1);
                Assert::AreEqual(*(it), &int2);
                Assert::AreEqual(*(++it), &int3);
            }

            // Foo test
            {
                Vector<Foo> vector;
                Vector<Foo>::Iterator it;
                auto case1 = [&it] {++it;};
                auto case2 = [&it] {it++;};
                Assert::ExpectException<std::exception>(case1);
                Assert::ExpectException<std::exception>(case2);
                it = vector.begin();
                ++it;
                it++;
                vector.PushBack(foo1);
                vector.PushBack(foo2);
                vector.PushBack(foo3);
                Assert::AreEqual(*(it++), foo1);
                Assert::AreEqual(*(it), foo2);
                Assert::AreEqual(*(++it), foo3);
            }
        }

        TEST_METHOD(IteratoreDereferenceOperator)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            {
                Vector<int> vector;
                Vector<int>::Iterator it;
                auto case1 = [&it] { *it; };
                Assert::ExpectException<std::exception>(case1);
                vector.PushBack(int1);
                vector.PushBack(int2);
                vector.PushBack(int3);
                Assert::AreEqual<int>(*(vector.begin()), int1);
                Assert::AreEqual<int>(*(vector.Find(int2)), int2);
                auto case2 = [&vector] { *(vector.end()); };
                Assert::ExpectException<std::exception>(case2);
            }

            // pointer test
            {
                Vector<int*> vector;
                Vector<int*>::Iterator it;
                auto case1 = [&it] { *it; };
                Assert::ExpectException<std::exception>(case1);
                vector.PushBack(&int1);
                vector.PushBack(&int2);
                vector.PushBack(&int3);
                Assert::AreEqual<int*>(*(vector.begin()), &int1);
                Assert::AreEqual<int*>(*(vector.Find(&int2)), &int2);
                auto case2 = [&vector] { *(vector.end()); };
                Assert::ExpectException<std::exception>(case2);
            }

            // Foo test
            {
                Vector<Foo> vector;
                Vector<Foo>::Iterator it;
                auto case1 = [&it] { *it; };
                Assert::ExpectException<std::exception>(case1);
                vector.PushBack(foo1);
                vector.PushBack(foo2);
                vector.PushBack(foo3);
                Assert::AreEqual<Foo>(*(vector.begin()), foo1);
                Assert::AreEqual<Foo>(*(vector.Find(foo2)), foo2);
                auto case2 = [&vector] { *(vector.end()); };
                Assert::ExpectException<std::exception>(case2);
            }
        }

        TEST_METHOD(IteratorCopySemantics)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            {
                Vector<int> vector;
                Vector<int> vector2;
                Vector<int>::Iterator it;
                vector.PushBack(int1);
                vector.PushBack(int2);
                it = vector.begin();
                Vector<int>::Iterator it2(vector2.begin());
                Assert::AreEqual<Vector<int>::Iterator>(it2, vector2.begin());
                it2 = it;
                Assert::AreEqual<int>(*it2, int1);
                it2 = vector.Find(int2);
                Assert::AreEqual<int>(*it2, int2);
                vector2.PushBack(int3);
                it2 = vector2.Find(int3);
                Assert::AreEqual<int>(*it2, int3);
            }

            // pointer test
            {
                Vector<int*> vector;
                Vector<int*> vector2;
                Vector<int*>::Iterator it;
                vector.PushBack(&int1);
                vector.PushBack(&int2);
                it = vector.begin();
                Vector<int*>::Iterator it2(vector2.begin());
                Assert::AreEqual<Vector<int*>::Iterator>(it2, vector2.begin());
                it2 = it;
                Assert::AreEqual<int*>(*it2, &int1);
                it2 = vector.Find(&int2);
                Assert::AreEqual<int*>(*it2, &int2);
                vector2.PushBack(&int3);
                it2 = vector2.Find(&int3);
                Assert::AreEqual<int*>(*it2, &int3);
            }

            // Foo test
            {
                Vector<Foo> vector;
                Vector<Foo> vector2;
                Vector<Foo>::Iterator it;
                vector.PushBack(foo1);
                vector.PushBack(foo2);
                it = vector.begin();
                Vector<Foo>::Iterator it2(vector2.begin());
                Assert::AreEqual<Vector<Foo>::Iterator>(it2, vector2.begin());
                it2 = it;
                Assert::AreEqual<Foo>(*it2, foo1);
                it2 = vector.Find(foo2);
                Assert::AreEqual<Foo>(*it2, foo2);
                vector2.PushBack(foo3);
                it2 = vector2.Find(foo3);
                Assert::AreEqual<Foo>(*it2, foo3);
            }
        }

        TEST_METHOD(ShrinkToFit)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            {
                Vector<int> vector;
                vector.ShrinkToFit();
                vector.PushBack(int1);
                vector.PushBack(int2);
                vector.PushBack(int3);
                Assert::AreEqual<int>(vector.Size(), 3);
                Assert::AreEqual<int>(vector.Capacity(), 4);
                vector.ShrinkToFit();
                Assert::AreEqual<int>(vector.Size(), 3);
                Assert::AreEqual<int>(vector.Capacity(), 3);
                vector.Clear();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 3);
                vector.ShrinkToFit();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
            }

            // pointer test
            {
                Vector<int*> vector;
                vector.ShrinkToFit();
                vector.PushBack(&int1);
                vector.PushBack(&int2);
                vector.PushBack(&int3);
                Assert::AreEqual<int>(vector.Size(), 3);
                Assert::AreEqual<int>(vector.Capacity(), 4);
                vector.ShrinkToFit();
                Assert::AreEqual<int>(vector.Size(), 3);
                Assert::AreEqual<int>(vector.Capacity(), 3);
                vector.Clear();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 3);
                vector.ShrinkToFit();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
            }

            // Foo test
            {
                Vector<Foo> vector;
                vector.ShrinkToFit();
                vector.PushBack(foo1);
                vector.PushBack(foo2);
                vector.PushBack(foo3);
                Assert::AreEqual<int>(vector.Size(), 3);
                Assert::AreEqual<int>(vector.Capacity(), 4);
                vector.ShrinkToFit();
                Assert::AreEqual<int>(vector.Size(), 3);
                Assert::AreEqual<int>(vector.Capacity(), 3);
                vector.Clear();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 3);
                vector.ShrinkToFit();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
            }
        }

        TEST_METHOD(Destroy)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            {
                Vector<int> vector;
                vector.Destroy();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
                vector.PushBack(int1);
                vector.PushBack(int2);
                vector.PushBack(int3);
                Assert::AreEqual<int>(vector.Size(), 3);
                Assert::AreEqual<int>(vector.Capacity(), 4);
                vector.Destroy();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
                Assert::AreEqual<Vector<int>::Iterator>(vector.begin(), vector.end());

            }

            // pointer test
            {
                Vector<int*> vector;
                vector.Destroy();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
                vector.PushBack(&int1);
                vector.PushBack(&int2);
                vector.PushBack(&int3);
                Assert::AreEqual<int>(vector.Size(), 3);
                Assert::AreEqual<int>(vector.Capacity(), 4);
                vector.Destroy();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
                Assert::AreEqual<Vector<int*>::Iterator>(vector.begin(), vector.end());
            }

            // Foo test
            {
                Vector<Foo> vector;
                vector.Destroy();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
                vector.PushBack(foo1);
                vector.PushBack(foo2);
                vector.PushBack(foo3);
                Assert::AreEqual<int>(vector.Size(), 3);
                Assert::AreEqual<int>(vector.Capacity(), 4);
                vector.Destroy();
                Assert::AreEqual<int>(vector.Size(), 0);
                Assert::AreEqual<int>(vector.Capacity(), 0);
                Assert::AreEqual<Vector<Foo>::Iterator>(vector.begin(), vector.end());
            }
        }

    private:
        static _CrtMemState sStartMemState;
    };

    _CrtMemState VectorTest::sStartMemState;
}