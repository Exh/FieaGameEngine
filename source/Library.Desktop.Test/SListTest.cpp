#include "pch.h"

#include <exception>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace Microsoft
{
    namespace VisualStudio
    {
        namespace CppUnitTestFramework
        {
            template<>
            inline std::wstring ToString<SList<Foo>::Iterator>(const SList<Foo>::Iterator& it)
            {
                (it);
                    return L"SList<Foo>::Iterator string!";
            }

            template<>
            inline std::wstring ToString<SList<int>::Iterator>(const SList<int>::Iterator& it)
            {
                (it);
                return L"SList<int>::Iterator string!";
            }

            template<>
            inline std::wstring ToString<SList<int*>::Iterator>(const SList<int*>::Iterator& it)
            {
                (it);
                return L"SList<int*>::Iterator string!";
            }
        }
    }
}

namespace LibraryDesktopTest
{
    TEST_CLASS(SListTest)
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
            // int tests 
            SList<int> intList;
            Assert::AreEqual<int>(intList.Size(), 0);

            // int* tests
            SList<int*> pointerList;
            Assert::AreEqual<int>(pointerList.Size(), 0);

            // Foo tests
            SList<Foo> fooList;
            Assert::AreEqual<int>(fooList.Size(), 0);
        }

        TEST_METHOD(PushFront)
        {
            int int1 = 10;
            int int2 = 20;

            Foo foo1(1, 2);
            Foo foo2(3, 4);

            // int tests 
            SList<int> intList;
            intList.PushFront(int1);
            Assert::AreEqual<int>(intList.Size(), 1);

            int intFront = intList.Front();
            Assert::AreEqual<int>(intFront, int1);

            intList.PushFront(int2);
            Assert::AreEqual<int>(intList.Size(), 2);

            intFront = intList.Front();
            Assert::AreEqual<int>(intFront, int2);

            // int* tests
            SList<int*> pointerList;
            pointerList.PushFront(&int1);
            Assert::AreEqual<int>(pointerList.Size(), 1);

            int* pointerFront = pointerList.Front();
            Assert::AreEqual<int*>(pointerFront, &int1);

            pointerList.PushFront(&int2);
            Assert::AreEqual<int>(pointerList.Size(), 2);

            pointerFront = pointerList.Front();
            Assert::AreEqual<int*>(pointerFront, &int2);

            // Foo tests
            SList<Foo> fooList;
            fooList.PushFront(foo1);
            Assert::AreEqual<int>(fooList.Size(), 1);

            Foo fooFront = fooList.Front();
            Assert::AreEqual<Foo>(fooFront, foo1);

            fooList.PushFront(foo2);
            Assert::AreEqual<int>(fooList.Size(), 2);

            fooFront = fooList.Front();
            Assert::AreEqual<Foo>(fooFront, foo2);
        }

        TEST_METHOD(PopFront)
        {
            int int1 = 10;
            int int2 = 20;

            Foo foo1(1, 2);
            Foo foo2(3, 4);

            // int tests 
            SList<int> intList;
            intList.PushFront(int1);
            intList.PushFront(int2);

            Assert::AreEqual<int>(intList.Size(), 2);
            Assert::AreEqual<int>(intList.Front(), int2);
            intList.PopFront();
            Assert::AreEqual<int>(intList.Size(), 1);
            Assert::AreEqual<int>(intList.Front(), int1);
            intList.PopFront();
            Assert::AreEqual<int>(intList.Size(), 0);

            // pointer tests
            SList<int*> pointerList;
            pointerList.PushFront(&int1);
            pointerList.PushFront(&int2);

            Assert::AreEqual<int>(pointerList.Size(), 2);
            Assert::AreEqual<int*>(pointerList.Front(), &int2);
            pointerList.PopFront();
            Assert::AreEqual<int>(pointerList.Size(), 1);
            Assert::AreEqual<int*>(pointerList.Front(), &int1);
            pointerList.PopFront();
            Assert::AreEqual<int>(pointerList.Size(), 0);

            // Foo tests
            SList<Foo> fooList;
            fooList.PushFront(foo1);
            fooList.PushFront(foo2);

            Assert::AreEqual<int>(fooList.Size(), 2);
            Assert::AreEqual<Foo>(fooList.Front(), foo2);
            fooList.PopFront();
            Assert::AreEqual<int>(fooList.Size(), 1);
            Assert::AreEqual<Foo>(fooList.Front(), foo1);
            fooList.PopFront();
            Assert::AreEqual<int>(fooList.Size(), 0);
        }

        TEST_METHOD(PushBack)
        {
            int int1 = 10;
            int int2 = 20;

            Foo foo1(1, 2);
            Foo foo2(3, 4);

            // int tests
            SList<int> intList;
            intList.PushBack(int1);
            Assert::AreEqual<int>(intList.Size(), 1);
            Assert::AreEqual<int>(intList.Front(), int1);
            intList.PushBack(int2);
            Assert::AreEqual<int>(intList.Size(), 2);
            Assert::AreEqual<int>(intList.Front(), int1);

            // pointer tests
            SList<int*> pointerList;
            pointerList.PushBack(&int1);
            Assert::AreEqual<int>(pointerList.Size(), 1);
            Assert::AreEqual<int*>(pointerList.Front(), &int1);
            pointerList.PushBack(&int2);
            Assert::AreEqual<int>(pointerList.Size(), 2);
            Assert::AreEqual<int*>(pointerList.Front(), &int1);

            // Foo tests
            SList<Foo> fooList;
            fooList.PushBack(foo1);
            Assert::AreEqual<int>(fooList.Size(), 1);
            Assert::AreEqual<Foo>(fooList.Front(), foo1);
            fooList.PushBack(foo2);
            Assert::AreEqual<int>(fooList.Size(), 2);
            Assert::AreEqual<Foo>(fooList.Front(), foo1);
        }

        TEST_METHOD(IsEmpty)
        {
            int int1 = 10;

            Foo foo1(1, 2);

            // int tests
            SList<int> intList;
            Assert::IsTrue(intList.IsEmpty());
            intList.PushFront(int1);
            Assert::IsFalse(intList.IsEmpty());
            intList.PopFront();
            Assert::IsTrue(intList.IsEmpty());

            // pointer tests
            SList<int*> pointerList;
            Assert::IsTrue(pointerList.IsEmpty());
            pointerList.PushFront(&int1);
            Assert::IsFalse(pointerList.IsEmpty());
            pointerList.PopFront();
            Assert::IsTrue(pointerList.IsEmpty());

            // Foo tests
            SList<Foo> fooList;
            Assert::IsTrue(fooList.IsEmpty());
            fooList.PushFront(foo1);
            Assert::IsFalse(fooList.IsEmpty());
            fooList.PopFront();
            Assert::IsTrue(fooList.IsEmpty());
        }

        TEST_METHOD(Front)
        {
            int int1 = 10;
            int int2 = 20;
            int int3 = 30;

            Foo foo1(1, 2);
            Foo foo2(1, 3);
            Foo foo3(3, 2);

            // int test
            SList<int> intList;
            const SList<int>* constIntList = &intList;
            intList.PushFront(int1);
            Assert::AreEqual<int>(intList.Front(), int1);
            Assert::AreEqual<int>(constIntList->Front(), int1);
            intList.Front() = int3;
            Assert::AreEqual<int>(intList.Front(), int3);
            intList.PushFront(int2);
            Assert::AreEqual<int>(intList.Front(), int2);
            intList.PushBack(int3);
            Assert::AreEqual<int>(intList.Front(), int2);
            intList.PopFront();
            intList.PopFront();
            intList.PopFront();
            auto exceptionInt = [&intList]{ intList.Front(); };
            Assert::ExpectException<std::exception>(exceptionInt);

            // pointer test
            SList<int*> pointerList;
            const SList<int*>* constPointerList = &pointerList;
            pointerList.PushFront(&int1);
            Assert::AreEqual<int*>(pointerList.Front(), &int1);
            Assert::AreEqual<int*>(constPointerList->Front(), &int1);
            pointerList.Front() = &int2;
            Assert::AreEqual<int*>(pointerList.Front(), &int2);
            pointerList.PushFront(&int2);
            Assert::AreEqual<int*>(pointerList.Front(), &int2);
            pointerList.PushBack(&int3);
            Assert::AreEqual<int*>(pointerList.Front(), &int2);
            pointerList.PopFront();
            pointerList.PopFront();
            pointerList.PopFront();
            auto exceptionPointer = [&pointerList] { pointerList.Front(); };
            Assert::ExpectException<std::exception>(exceptionPointer);

            // Foo test
            SList<Foo> fooList;
            const SList<Foo>* constFooList = &fooList;
            fooList.PushFront(foo1);
            Assert::AreEqual<Foo>(fooList.Front(), foo1);
            Assert::AreEqual<Foo>(constFooList->Front(), foo1);
            fooList.Front() = foo3;
            Assert::AreEqual<Foo>(fooList.Front(), foo3);
            fooList.PushFront(foo2);
            Assert::AreEqual<Foo>(fooList.Front(), foo2);
            fooList.PushBack(foo3);
            Assert::AreEqual<Foo>(fooList.Front(), foo2);
            fooList.PopFront();
            fooList.PopFront();
            fooList.PopFront();
            auto exceptionFoo = [&fooList] { fooList.Front(); };
            Assert::ExpectException<std::exception>(exceptionFoo);
        }

        TEST_METHOD(Back)
        {
            int int1 = 10;
            int int2 = 20;
            int int3 = 30;

            Foo foo1(1, 2);
            Foo foo2(1, 3);
            Foo foo3(3, 2);

            // int test
            SList<int> intList;
            const SList<int>* constIntList = &intList;
            intList.PushBack(int1);
            Assert::AreEqual<int>(intList.Back(), int1);
            Assert::AreEqual<int>(constIntList->Back(), int1);
            intList.Back() = int3;
            Assert::AreEqual<int>(intList.Back(), int3);
            intList.PushBack(int2);
            Assert::AreEqual<int>(intList.Back(), int2);
            intList.PushFront(int3);
            Assert::AreEqual<int>(intList.Back(), int2);
            intList.PopFront();
            intList.PopFront();
            intList.PopFront();
            auto exceptionInt = [&intList] { intList.Back(); };
            Assert::ExpectException<std::exception>(exceptionInt);

            // pointer test
            SList<int*> pointerList;
            const SList<int*>* constPointerList = &pointerList;
            pointerList.PushBack(&int1);
            Assert::AreEqual<int*>(pointerList.Back(), &int1);
            Assert::AreEqual<int*>(constPointerList->Back(), &int1);
            pointerList.Back() = &int2;
            Assert::AreEqual<int*>(pointerList.Back(), &int2);
            pointerList.PushBack(&int2);
            Assert::AreEqual<int*>(pointerList.Back(), &int2);
            pointerList.PushFront(&int3);
            Assert::AreEqual<int*>(pointerList.Back(), &int2);
            pointerList.PopFront();
            pointerList.PopFront();
            pointerList.PopFront();
            auto exceptionPointer = [&pointerList] { pointerList.Back(); };
            Assert::ExpectException<std::exception>(exceptionPointer);

            // Foo test
            SList<Foo> fooList;
            const SList<Foo>* constFooList = &fooList;
            fooList.PushBack(foo1);
            Assert::AreEqual<Foo>(fooList.Back(), foo1);
            Assert::AreEqual<Foo>(constFooList->Back(), foo1);
            fooList.Back() = foo3;
            Assert::AreEqual<Foo>(fooList.Back(), foo3);
            fooList.PushBack(foo2);
            Assert::AreEqual<Foo>(fooList.Back(), foo2);
            fooList.PushFront(foo3);
            Assert::AreEqual<Foo>(fooList.Back(), foo2);
            fooList.PopFront();
            fooList.PopFront();
            fooList.PopFront();
            auto exceptionFoo = [&fooList] { fooList.Back(); };
            Assert::ExpectException<std::exception>(exceptionFoo);
        }

        TEST_METHOD(Size)
        {
            int int1 = 10;
            int int2 = 20;

            Foo foo1(1, 2);
            Foo foo2(3, 4);

            // int tests
            SList<int> intList;
            Assert::AreEqual<int>(intList.Size(), 0);
            intList.PushFront(int1);
            Assert::AreEqual<int>(intList.Size(), 1);
            intList.PushBack(int2);
            Assert::AreEqual<int>(intList.Size(), 2);
            intList.PopFront();
            Assert::AreEqual<int>(intList.Size(), 1);
            intList.PopFront();
            Assert::AreEqual<int>(intList.Size(), 0);

            // pointer tests
            SList<int*> pointerList;
            Assert::AreEqual<int>(pointerList.Size(), 0);
            pointerList.PushFront(&int1);
            Assert::AreEqual<int>(pointerList.Size(), 1);
            pointerList.PushBack(&int2);
            Assert::AreEqual<int>(pointerList.Size(), 2);
            pointerList.PopFront();
            Assert::AreEqual<int>(pointerList.Size(), 1);
            pointerList.PopFront();
            Assert::AreEqual<int>(pointerList.Size(), 0);

            // Foo tests
            SList<Foo> fooList;
            Assert::AreEqual<int>(fooList.Size(), 0);
            fooList.PushFront(foo1);
            Assert::AreEqual<int>(fooList.Size(), 1);
            fooList.PushBack(foo2);
            Assert::AreEqual<int>(fooList.Size(), 2);
            fooList.PopFront();
            Assert::AreEqual<int>(fooList.Size(), 1);
            fooList.PopFront();
            Assert::AreEqual<int>(fooList.Size(), 0);
        }

        TEST_METHOD(CopySemantics)
        {
            const int ASSIGNMENT_OPERATOR_TEST_LIST_SIZE = 3;

            int int1 = 10;
            int int2 = 20;
            int int3 = 30;

            Foo foo1(1, 2);
            Foo foo2(3, 4);
            Foo foo3(3, 2);

            // Copy Constructor test
            // int SList setup
            SList<int> intList;
            intList.PushBack(int1);
            intList.PushBack(int2);
            SList<int> intListCopy(intList);

            // pointer SList setup
            SList<int*> pointerList;
            pointerList.PushBack(&int1);
            pointerList.PushBack(&int2);
            SList<int*> pointerListCopy(pointerList);

            // foo SList setup
            SList<Foo> fooList;
            fooList.PushBack(foo1);
            fooList.PushBack(foo2);
            SList<Foo> fooListCopy(fooList);

            Assert::AreEqual<int>(intList.Front(), intListCopy.Front());
            Assert::AreEqual<int>(intList.Back(), intListCopy.Back());
            Assert::AreEqual<int>(intList.Size(), intListCopy.Size());

            Assert::AreEqual<int*>(pointerList.Front(), pointerListCopy.Front());
            Assert::AreEqual<int*>(pointerList.Back(), pointerListCopy.Back());
            Assert::AreEqual<int>(pointerList.Size(), pointerListCopy.Size());

            Assert::AreEqual<Foo>(fooList.Front(), fooListCopy.Front());
            Assert::AreEqual<Foo>(fooList.Back(), fooListCopy.Back());
            Assert::AreEqual<int>(fooList.Size(), fooListCopy.Size());

            // Assignment operator test
            intList.PushFront(int3);
            pointerList.PushFront(&int3);
            fooList.PushFront(foo3);

            intListCopy = intList;
            pointerListCopy = pointerList;
            fooListCopy = fooList;

            // Check copies are same
            for (int i = 0; i < ASSIGNMENT_OPERATOR_TEST_LIST_SIZE; i++)
            {
                Assert::AreEqual<int>(intList.Front(), intListCopy.Front());
                Assert::AreEqual<int*>(pointerList.Front(), pointerListCopy.Front());
                Assert::AreEqual<Foo>(fooList.Front(), fooListCopy.Front());

                intList.PopFront();
                intListCopy.PopFront();
                pointerList.PopFront();
                pointerListCopy.PopFront();
                fooList.PopFront();
                fooListCopy.PopFront();
            }
        }

        TEST_METHOD(begin)
        {
            int int1 = 1;
            int int2 = 2;

            Foo foo1(1, 2);
            Foo foo2(2, 3);

            // int test
            SList<int> intList;
            SList<int>::Iterator itInt = intList.begin();

            if (itInt != intList.end())
            {
                Assert::Fail();
            }

            intList.PushFront(int1);
            intList.PushFront(int2);

            itInt = intList.begin();
            Assert::AreEqual<int>(*itInt, int2);

            const SList<int>* constIntList = &intList;
            const SList<int>::Iterator constItInt = constIntList->begin();
            Assert::AreEqual<int>(*constItInt, int2);

            // pointer test
            SList<int*> pointerList;
            SList<int*>::Iterator itPointer = pointerList.begin();

            if (itPointer != pointerList.end())
            {
                Assert::Fail();
            }

            pointerList.PushFront(&int1);
            pointerList.PushFront(&int2);

            itPointer = pointerList.begin();
            Assert::AreEqual<int*>(*itPointer, &int2);

            const SList<int*>* constPointerList = &pointerList;
            const SList<int*>::Iterator constItPointer = constPointerList->begin();
            Assert::AreEqual<int*>(*constItPointer, &int2);

            // Foo test
            SList<Foo> fooList;
            SList<Foo>::Iterator itFoo = fooList.begin();
            
            if (itFoo != fooList.end())
            {
                Assert::Fail();
            }

            fooList.PushFront(foo1);
            fooList.PushFront(foo2);

            itFoo = fooList.begin();
            Assert::AreEqual<Foo>(*itFoo, foo2);

            const SList<Foo>* constFooList = &fooList;
            const SList<Foo>::Iterator constItFoo = constFooList->begin();
            Assert::AreEqual<Foo>(*constItFoo, foo2);
        }

        TEST_METHOD(end)
        {
            int int1 = 1;
            int int2 = 2;

            Foo foo1(1, 2);
            Foo foo2(2, 3);

            // int test
            SList<int> listInt;
            SList<int>::Iterator itInt = listInt.end();

            if (itInt != listInt.begin())
            {
                Assert::Fail();
            }

            listInt.PushFront(int1);
            listInt.PushFront(int2);
            int iInt = 0;
            for (itInt = listInt.begin(); itInt != listInt.end(); ++itInt)
            {
                iInt++;
            }
            Assert::AreEqual<int>(iInt, 2);

            const SList<int>* constListInt = &listInt;
            const SList<int>::Iterator constItInt = constListInt->end();
            Assert::AreEqual<SList<int>::Iterator>(constItInt, listInt.end());

            // pointer test
            SList<int*> listPointer;
            SList<int*>::Iterator itPointer = listPointer.end();

            if (itPointer != listPointer.begin())
            {
                Assert::Fail();
            }

            listPointer.PushFront(&int1);
            listPointer.PushFront(&int2);
            int iPointer = 0;
            for (itPointer = listPointer.begin(); itPointer != listPointer.end(); ++itPointer)
            {
                iPointer++;
            }
            Assert::AreEqual<int>(iPointer, 2);

            const SList<int*>* constListPointer = &listPointer;
            const SList<int*>::Iterator constItPointer = constListPointer->end();
            Assert::AreEqual<SList<int*>::Iterator>(constItPointer, listPointer.end());

            // Foo test
            SList<Foo> listFoo;
            SList<Foo>::Iterator itFoo = listFoo.end();

            if (itFoo != listFoo.begin())
            {
                Assert::Fail();
            }

            listFoo.PushFront(foo1);
            listFoo.PushFront(foo2);
            int iFoo = 0;
            for (itFoo = listFoo.begin(); itFoo != listFoo.end(); ++itFoo)
            {
                iFoo++;
            }
            Assert::AreEqual<int>(iFoo, 2);

            const SList<Foo>* constListFoo = &listFoo;
            const SList<Foo>::Iterator constItFoo = constListFoo->end();
            Assert::AreEqual<SList<Foo>::Iterator>(constItFoo, listFoo.end());
        }

        TEST_METHOD(InsertAfter)
        {
            int int0 = 0;
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo0(0, 0);
            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            SList<int> listInt;
            SList<int>::Iterator itInt = listInt.begin();
            listInt.InsertAfter(int0, itInt);
            Assert::IsFalse(listInt.IsEmpty());
            listInt.PopFront();

            listInt.PushFront(int1);
            listInt.PushBack(int2);
            listInt.InsertAfter(int3, listInt.begin());
            itInt = listInt.begin();
            ++itInt;
            Assert::AreEqual<int>(*itInt, int3);

            // pointer test
            SList<int*> listPointer;
            SList<int*>::Iterator itPointer = listPointer.begin();
            listPointer.InsertAfter(&int0, itPointer);
            Assert::IsFalse(listPointer.IsEmpty());
            listPointer.PopFront();

            listPointer.PushFront(&int1);
            listPointer.PushBack(&int2);
            listPointer.InsertAfter(&int3, listPointer.begin());
            itPointer = listPointer.begin();
            ++itPointer;
            Assert::AreEqual<int*>(*itPointer, &int3);

            // Foo test
            SList<Foo> listFoo;
            SList<Foo>::Iterator itFoo = listFoo.begin();
            listFoo.InsertAfter(foo0, itFoo);
            Assert::IsFalse(listFoo.IsEmpty());
            listFoo.PopFront();

            listFoo.PushFront(foo1);
            listFoo.PushBack(foo2);
            listFoo.InsertAfter(foo3, listFoo.begin());
            itFoo = listFoo.begin();
            ++itFoo;
            Assert::AreEqual<Foo>(*itFoo, foo3);
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
            SList<int> listInt;
            SList<int>::Iterator itInt = listInt.Find(int1);
            if (itInt != listInt.end())
            {
                Assert::Fail();
            }

            listInt.PushFront(int1);
            listInt.PushFront(int2);
            listInt.PushFront(int3);

            Assert::AreEqual<int>(*(listInt.Find(int2)), int2);
            Assert::AreEqual<int>(*(listInt.Find(int3)), int3);
            Assert::AreEqual<int>(*(listInt.Find(int1)), int1);

            const SList<int>* constListInt = &listInt;
            const SList<int>::Iterator constItInt = constListInt->Find(int2);
            itInt = listInt.Find(int2);
            Assert::AreEqual<int>(*itInt, *constItInt);

            // pointer test
            SList<int*> listPointer;
            SList<int*>::Iterator itPointer = listPointer.Find(&int1);
            if (itPointer != listPointer.end())
            {
                Assert::Fail();
            }

            listPointer.PushFront(&int1);
            listPointer.PushFront(&int2);
            listPointer.PushFront(&int3);

            Assert::AreEqual<int*>(*(listPointer.Find(&int2)), &int2);
            Assert::AreEqual<int*>(*(listPointer.Find(&int3)), &int3);
            Assert::AreEqual<int*>(*(listPointer.Find(&int1)), &int1);

            const SList<int*>* constListPointer = &listPointer;
            const SList<int*>::Iterator constItPointer = constListPointer->Find(&int2);
            itPointer = listPointer.Find(&int2);
            Assert::AreEqual<int*>(*itPointer, *constItPointer);

            // Foo test
            SList<Foo> listFoo;
            SList<Foo>::Iterator itFoo = listFoo.Find(foo1);
            if (itFoo != listFoo.end()) 
            {
                Assert::Fail();
            }
            
            listFoo.PushFront(foo1);
            listFoo.PushFront(foo2);
            listFoo.PushFront(foo3);

            Assert::AreEqual<Foo>(*(listFoo.Find(foo2)), foo2);
            Assert::AreEqual<Foo>(*(listFoo.Find(foo3)), foo3);
            Assert::AreEqual<Foo>(*(listFoo.Find(foo1)), foo1);

            const SList<Foo>* constListFoo = &listFoo;
            const SList<Foo>::Iterator constItFoo = constListFoo->Find(foo2);
            itFoo = listFoo.Find(foo2);
            Assert::AreEqual<Foo>(*itFoo, *constItFoo);
        }

        TEST_METHOD(Remove)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;
            int int4 = 4;
            int int5 = 5;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);
            Foo foo4(4, 5);
            Foo foo5(5, 6);

            // int test
            SList<int> listInt;
            Assert::IsFalse(listInt.Remove(int1));

            listInt.PushFront(int1);
            listInt.PushFront(int2);
            listInt.PushFront(int3);
            listInt.PushFront(int4);

            Assert::IsFalse(listInt.Remove(int5));
            Assert::AreEqual<int>(listInt.Size(), 4);
            Assert::IsTrue(listInt.Remove(int2));
            Assert::AreEqual<int>(listInt.Size(), 3);
            Assert::IsFalse(listInt.Remove(int2));
            Assert::AreEqual<int>(listInt.Size(), 3);
            Assert::IsTrue(listInt.Remove(int1));
            Assert::AreEqual<int>(listInt.Size(), 2);
            Assert::IsTrue(listInt.Remove(int4));
            Assert::AreEqual<int>(listInt.Size(), 1);
            Assert::IsTrue(listInt.Remove(int3));
            Assert::IsTrue(listInt.IsEmpty());

            Assert::IsFalse(listInt.RemoveAll(int1));
            listInt.PushFront(int1);
            listInt.PushFront(int1);
            listInt.PushFront(int3);
            listInt.PushFront(int4);
            listInt.PushFront(int1);

            Assert::AreEqual<int>(listInt.Size(), 5);
            Assert::IsTrue(listInt.RemoveAll(int1));
            Assert::AreEqual<int>(listInt.Size(), 2);
            Assert::IsTrue(listInt.RemoveAll(int3));
            Assert::IsFalse(listInt.RemoveAll(int3));

            // pointer test
            SList<int*> listPointer;
            Assert::IsFalse(listPointer.Remove(&int1));

            listPointer.PushFront(&int1);
            listPointer.PushFront(&int2);
            listPointer.PushFront(&int3);
            listPointer.PushFront(&int4);

            Assert::IsFalse(listPointer.Remove(&int5));
            Assert::AreEqual<int>(listPointer.Size(), 4);
            Assert::IsTrue(listPointer.Remove(&int2));
            Assert::AreEqual<int>(listPointer.Size(), 3);
            Assert::IsFalse(listPointer.Remove(&int2));
            Assert::AreEqual<int>(listPointer.Size(), 3);
            Assert::IsTrue(listPointer.Remove(&int1));
            Assert::AreEqual<int>(listPointer.Size(), 2);
            Assert::IsTrue(listPointer.Remove(&int4));
            Assert::AreEqual<int>(listPointer.Size(), 1);
            Assert::IsTrue(listPointer.Remove(&int3));
            Assert::IsTrue(listPointer.IsEmpty());

            Assert::IsFalse(listPointer.RemoveAll(&int1));
            listPointer.PushFront(&int1);
            listPointer.PushFront(&int1);
            listPointer.PushFront(&int3);
            listPointer.PushFront(&int4);
            listPointer.PushFront(&int1);

            Assert::AreEqual<int>(listPointer.Size(), 5);
            Assert::IsTrue(listPointer.RemoveAll(&int1));
            Assert::AreEqual<int>(listPointer.Size(), 2);
            Assert::IsTrue(listPointer.RemoveAll(&int3));
            Assert::IsFalse(listPointer.RemoveAll(&int3));

            // Foo test
            SList<Foo> listFoo;
            Assert::IsFalse(listFoo.Remove(foo1));

            listFoo.PushFront(foo1);
            listFoo.PushFront(foo2);
            listFoo.PushFront(foo3);
            listFoo.PushFront(foo4);

            Assert::IsFalse(listFoo.Remove(foo5));
            Assert::AreEqual<int>(listFoo.Size(), 4);
            Assert::IsTrue(listFoo.Remove(foo2));
            Assert::AreEqual<int>(listFoo.Size(), 3);
            Assert::IsFalse(listFoo.Remove(foo2));
            Assert::AreEqual<int>(listFoo.Size(), 3);
            Assert::IsTrue(listFoo.Remove(foo1));
            Assert::AreEqual<int>(listFoo.Size(), 2);
            Assert::IsTrue(listFoo.Remove(foo4));
            Assert::AreEqual<int>(listFoo.Size(), 1);
            Assert::IsTrue(listFoo.Remove(foo3));
            Assert::IsTrue(listFoo.IsEmpty());

            Assert::IsFalse(listFoo.RemoveAll(foo1));
            listFoo.PushFront(foo1);
            listFoo.PushFront(foo1);
            listFoo.PushFront(foo3);
            listFoo.PushFront(foo4);
            listFoo.PushFront(foo1);

            Assert::AreEqual<int>(listFoo.Size(), 5);
            Assert::IsTrue(listFoo.RemoveAll(foo1));
            Assert::AreEqual<int>(listFoo.Size(), 2);
            Assert::IsTrue(listFoo.RemoveAll(foo3));
            Assert::IsFalse(listFoo.RemoveAll(foo3));
        }

        TEST_METHOD(IteratorConstructors)
        {
            // int test
            SList<int> listInt;
            SList<int>::Iterator itInt;
            Assert::AreNotEqual<SList<int>::Iterator>(itInt, listInt.end());

            SList<int>::Iterator it2Int = listInt.begin();
            Assert::AreEqual<SList<int>::Iterator>(it2Int, listInt.begin());

            // pointer test
            SList<int*> listPointer;
            SList<int*>::Iterator itPointer;
            Assert::AreNotEqual<SList<int*>::Iterator>(itPointer, listPointer.end());

            SList<int*>::Iterator it2Pointer = listPointer.begin();
            Assert::AreEqual<SList<int*>::Iterator>(it2Pointer, listPointer.begin());

            // Foo test
            SList<Foo> listFoo;
            SList<Foo>::Iterator itFoo;
            Assert::AreNotEqual<SList<Foo>::Iterator>(itFoo, listFoo.end());

            SList<Foo>::Iterator it2Foo = listFoo.begin();
            Assert::AreEqual<SList<Foo>::Iterator>(it2Foo, listFoo.begin());
        }

        TEST_METHOD(IteratorEquality)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;
            int count = 0;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            SList<int> listInt;
            listInt.PushBack(int1);
            listInt.PushBack(int2);
            listInt.PushBack(int3);

            // Equality
            SList<int>::Iterator it1Int = listInt.begin();
            SList<int>::Iterator it2Int = listInt.begin();
            Assert::AreEqual<SList<int>::Iterator>(it1Int, it2Int);

            // Inequality
            count = 0;
            for (SList<int>::Iterator itInt = listInt.begin(); itInt != listInt.end(); ++itInt)
            {
                count++;
            }
            Assert::AreEqual<int>(count, 3);

            // pointer test
            SList<int*> listPointer;
            listPointer.PushBack(&int1);
            listPointer.PushBack(&int2);
            listPointer.PushBack(&int3);

            // Equality
            SList<int*>::Iterator it1Pointer = listPointer.begin();
            SList<int*>::Iterator it2Pointer = listPointer.begin();
            Assert::AreEqual<SList<int*>::Iterator>(it1Pointer, it2Pointer);

            // Inequality
            count = 0;
            for (SList<int*>::Iterator itPointer = listPointer.begin(); itPointer != listPointer.end(); ++itPointer)
            {
                count++;
            }
            Assert::AreEqual<int>(count, 3);

            // Foo test
            SList<Foo> listFoo;
            listFoo.PushBack(foo1);
            listFoo.PushBack(foo2);
            listFoo.PushBack(foo3);

            // Equality
            SList<Foo>::Iterator it1Foo = listFoo.begin();
            SList<Foo>::Iterator it2Foo = listFoo.begin();
            Assert::AreEqual<SList<Foo>::Iterator>(it1Foo, it2Foo);

            // Inequality
            count = 0;
            for (SList<Foo>::Iterator itFoo = listFoo.begin(); itFoo != listFoo.end(); ++itFoo)
            {
                count++;
            }
            Assert::AreEqual<int>(count, 3);
        }

        TEST_METHOD(IteratorAssignment)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            //  int test
            SList<int> listInt;
            listInt.PushBack(int1);
            listInt.PushBack(int2);
            listInt.PushBack(int3);

            SList<int>::Iterator it1Int = listInt.begin();
            SList<int>::Iterator it2Int = listInt.begin();
            Assert::AreEqual<SList<int>::Iterator>(it1Int, it2Int);
            ++it1Int;
            Assert::AreNotEqual<SList<int>::Iterator>(it1Int, it2Int);
            it2Int = it1Int;
            Assert::AreEqual<SList<int>::Iterator>(it1Int, it2Int);

            // pointer test
            SList<int*> listPointer;
            listPointer.PushBack(&int1);
            listPointer.PushBack(&int2);
            listPointer.PushBack(&int3);

            SList<int*>::Iterator it1Pointer = listPointer.begin();
            SList<int*>::Iterator it2Pointer = listPointer.begin();
            Assert::AreEqual<SList<int*>::Iterator>(it1Pointer, it2Pointer);
            ++it1Pointer;
            Assert::AreNotEqual<SList<int*>::Iterator>(it1Pointer, it2Pointer);
            it2Pointer = it1Pointer;
            Assert::AreEqual<SList<int*>::Iterator>(it1Pointer, it2Pointer);

            // Foo test
            SList<Foo> listFoo;
            listFoo.PushBack(foo1);
            listFoo.PushBack(foo2);
            listFoo.PushBack(foo3);

            SList<Foo>::Iterator it1Foo = listFoo.begin();
            SList<Foo>::Iterator it2Foo = listFoo.begin();
            Assert::AreEqual<SList<Foo>::Iterator>(it1Foo, it2Foo);
            ++it1Foo;
            Assert::AreNotEqual<SList<Foo>::Iterator>(it1Foo, it2Foo);
            it2Foo = it1Foo;
            Assert::AreEqual<SList<Foo>::Iterator>(it1Foo, it2Foo);
        }

        TEST_METHOD(IteratorIncrements)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            SList<int> listInt;
            listInt.PushBack(int1);
            listInt.PushBack(int2);
            listInt.PushBack(int3);

            SList<int>::Iterator itInt = listInt.begin();

            // Postincrement
            Assert::AreEqual<int>(*itInt, int1);
            Assert::AreEqual<int>(*(itInt++), int1);
            Assert::AreEqual<int>(*itInt, int2);

            // Preincrement
            Assert::AreEqual(*(++itInt), int3);
            Assert::AreEqual<int>(*itInt, int3);

            // pointer test
            SList<int*> listPointer;
            listPointer.PushBack(&int1);
            listPointer.PushBack(&int2);
            listPointer.PushBack(&int3);

            SList<int*>::Iterator itPointer = listPointer.begin();

            // Postincrement
            Assert::AreEqual<int*>(*itPointer, &int1);
            Assert::AreEqual<int*>(*(itPointer++), &int1);
            Assert::AreEqual<int*>(*itPointer, &int2);

            // Preincrement
            Assert::AreEqual(*(++itPointer), &int3);
            Assert::AreEqual<int*>(*itPointer, &int3);

            // Foo test
            SList<Foo> listFoo;
            listFoo.PushBack(foo1);
            listFoo.PushBack(foo2);
            listFoo.PushBack(foo3);

            SList<Foo>::Iterator itFoo = listFoo.begin();

            // Postincrement
            Assert::AreEqual<Foo>(*itFoo, foo1);
            Assert::AreEqual<Foo>(*(itFoo++), foo1);
            Assert::AreEqual<Foo>(*itFoo, foo2);

            // Preincrement
            Assert::AreEqual(*(++itFoo), foo3);
            Assert::AreEqual<Foo>(*itFoo, foo3);
        }

        TEST_METHOD(IteratorDereference)
        {
            int int1 = 1;
            int int2 = 2;
            int int3 = 3;

            Foo foo1(1, 2);
            Foo foo2(2, 3);
            Foo foo3(3, 4);

            // int test
            SList<int> listInt;
            listInt.PushBack(int1);
            listInt.PushBack(int2);
            listInt.PushBack(int3);

            SList<int>::Iterator itInt = listInt.begin();
            Assert::AreEqual<int>(*itInt, int1);
            itInt++;
            Assert::AreEqual<int>(*itInt, int2);

            const SList<int>::Iterator constItInt = ++itInt;
            Assert::AreEqual<int>(*constItInt, int3);

            // pointer test
            SList<int*> listPointer;
            listPointer.PushBack(&int1);
            listPointer.PushBack(&int2);
            listPointer.PushBack(&int3);

            SList<int*>::Iterator itPointer = listPointer.begin();
            Assert::AreEqual<int*>(*itPointer, &int1);
            itPointer++;
            Assert::AreEqual<int*>(*itPointer, &int2);

            const SList<int*>::Iterator constItPointer = ++itPointer;
            Assert::AreEqual<int*>(*constItPointer, &int3);

            // Foo Test
            SList<Foo> listFoo;
            listFoo.PushBack(foo1);
            listFoo.PushBack(foo2);
            listFoo.PushBack(foo3);

            SList<Foo>::Iterator itFoo = listFoo.begin();
            Assert::AreEqual<Foo>(*itFoo, foo1);
            itFoo++;
            Assert::AreEqual<Foo>(*itFoo, foo2);

            const SList<Foo>::Iterator constItFoo = ++itFoo;
            Assert::AreEqual<Foo>(*constItFoo, foo3);
        }

		TEST_METHOD(MoveSemantics)
		{
			SList<Foo> list1;
			list1.PushBack(Foo(1,2));
			list1.PushBack(Foo(2,3));

			SList<Foo> list2(std::move(list1));
			Assert::IsTrue(list1.Size() == 0U);
			Assert::IsTrue(list2.Size() == 2U);
		}

    private:
        static _CrtMemState sStartMemState;
    };

    _CrtMemState SListTest::sStartMemState;
}
