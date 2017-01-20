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
            intList.PushFront(10);
            Assert::AreEqual<int>(intList.Size(), 1);

            int intFront = intList.Front();
            Assert::AreEqual<int>(intFront, 10);

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
            intList.PushFront(1);
            intList.PushFront(2);

            Assert::AreEqual<int>(intList.Size(), 2);
            Assert::AreEqual<int>(intList.Front(), 2);
            intList.PopFront();
            Assert::AreEqual<int>(intList.Size(), 1);
            Assert::AreEqual<int>(intList.Front(), 1);
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
            intList.PushBack(1);
            Assert::AreEqual<int>(intList.Size(), 1);
            Assert::AreEqual<int>(intList.Front(), 1);
            intList.PushBack(2);
            Assert::AreEqual<int>(intList.Size(), 2);
            Assert::AreEqual<int>(intList.Front(), 1);

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
            intList.PushFront(1);
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
            intList.PushFront(1);
            Assert::AreEqual<int>(intList.Front(), 1);
            Assert::AreEqual<int>(constIntList->Front(), 1);
            intList.Front() = 5;
            Assert::AreEqual<int>(intList.Front(), 5);
            intList.PushFront(2);
            Assert::AreEqual<int>(intList.Front(), 2);
            intList.PushBack(3);
            Assert::AreEqual<int>(intList.Front(), 2);
            intList.PopFront();
            intList.PopFront();
            intList.PopFront();
            try { intList.Front(); Assert::Fail(); } 
            catch (...){ }

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
            try { pointerList.Front(); Assert::Fail(); }
            catch (...) {}

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
            try { fooList.Front(); Assert::Fail(); }
            catch (...) {}
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
            intList.PushBack(1);
            Assert::AreEqual<int>(intList.Back(), 1);
            Assert::AreEqual<int>(constIntList->Back(), 1);
            intList.Back() = 5;
            Assert::AreEqual<int>(intList.Back(), 5);
            intList.PushBack(2);
            Assert::AreEqual<int>(intList.Back(), 2);
            intList.PushFront(3);
            Assert::AreEqual<int>(intList.Back(), 2);
            intList.PopFront();
            intList.PopFront();
            intList.PopFront();
            try { intList.Back(); Assert::Fail(); }
            catch (...) {}

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
            try { pointerList.Back(); Assert::Fail(); }
            catch (...) {}

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
            try { fooList.Back(); Assert::Fail(); }
            catch (...) {}
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
            intList.PushFront(1);
            Assert::AreEqual<int>(intList.Size(), 1);
            intList.PushBack(2);
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
            intList.PushBack(1);
            intList.PushBack(2);
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
            intList.PushFront(3);
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
            SList<Foo> list;
            SList<Foo>::Iterator it = list.begin();
            
            if (it != list.end())
            {
                Assert::Fail();
            }

            list.PushFront(Foo(1, 2));
            list.PushFront(Foo(2, 3));

            it = list.begin();
            Assert::AreEqual<Foo>(*it, Foo(2,3));

            const SList<Foo>* constList = &list;
            const SList<Foo>::Iterator constIt = constList->begin();
            Assert::AreEqual<Foo>(*it, Foo(2,3));
        }

        TEST_METHOD(end)
        {
            SList<Foo> list;
            SList<Foo>::Iterator it = list.end();

            if (it != list.begin())
            {
                Assert::Fail();
            }

            list.PushFront(Foo(1, 2));
            list.PushFront(Foo(2, 3));
            int i = 0;
            for (it = list.begin(); it != list.end(); ++it)
            {
                i++;
            }
            Assert::AreEqual<int>(i, 2);

            const SList<Foo>* constList = &list;
            const SList<Foo>::Iterator constIt = constList->end();
            Assert::AreEqual<SList<Foo>::Iterator>(it, list.end());
        }

        TEST_METHOD(InsertAfter)
        {
            SList<Foo> list;
            SList<Foo>::Iterator it = list.begin();
            list.InsertAfter(Foo(0, 0), it);
            Assert::IsFalse(list.IsEmpty());
            list.PopFront();

            list.PushFront(Foo(1, 2));
            list.PushBack(Foo(2, 3));
            list.InsertAfter(Foo(3, 4), list.begin());
            it = list.begin();
            ++it;
            Assert::AreEqual<Foo>(*it, Foo(3, 4));
        }

        TEST_METHOD(Find)
        {
            SList<Foo> list;
            SList<Foo>::Iterator it = list.Find(Foo(1, 2));
            if (it != list.end()) 
            {
                Assert::Fail();
            }
            
            list.PushFront(Foo(1, 2));
            list.PushFront(Foo(2, 3));
            list.PushFront(Foo(3, 4));

            Assert::AreEqual<Foo>(*(list.Find(Foo(2, 3))), Foo(2, 3));
            Assert::AreEqual<Foo>(*(list.Find(Foo(3, 4))), Foo(3, 4));
            Assert::AreEqual<Foo>(*(list.Find(Foo(1, 2))), Foo(1, 2));

            const SList<Foo>* constList = &list;
            const SList<Foo>::Iterator constIt = constList->Find(Foo(2, 3));
            it = list.Find(Foo(2, 3));
            Assert::AreEqual<Foo>(*it, *constIt);
        }

        TEST_METHOD(Remove)
        {
            SList<Foo> list;
            Assert::IsFalse(list.Remove(Foo(1, 2)));

            list.PushFront(Foo(1, 2));
            list.PushFront(Foo(2, 3));
            list.PushFront(Foo(3, 4));
            list.PushFront(Foo(4, 5));

            Assert::IsFalse(list.Remove(Foo(5, 6)));
            Assert::AreEqual<int>(list.Size(), 4);
            Assert::IsTrue(list.Remove(Foo(2, 3)));
            Assert::AreEqual<int>(list.Size(), 3);
            Assert::IsFalse(list.Remove(Foo(2, 3)));
            Assert::AreEqual<int>(list.Size(), 3);
            Assert::IsTrue(list.Remove(Foo(1, 2)));
            Assert::AreEqual<int>(list.Size(), 2);
            Assert::IsTrue(list.Remove(Foo(4, 5)));
            Assert::AreEqual<int>(list.Size(), 1);
            Assert::IsTrue(list.Remove(Foo(3, 4)));
            Assert::IsTrue(list.IsEmpty());

            Assert::IsFalse(list.RemoveAll(Foo(1, 2)));
            list.PushFront(Foo(1, 2));
            list.PushFront(Foo(1, 2));
            list.PushFront(Foo(3, 4));
            list.PushFront(Foo(4, 5));
            list.PushFront(Foo(1, 2));

            Assert::AreEqual<int>(list.Size(), 5);
            Assert::IsTrue(list.RemoveAll(Foo(1, 2)));
            Assert::AreEqual<int>(list.Size(), 2);
            Assert::IsTrue(list.RemoveAll(Foo(3, 4)));
            Assert::IsFalse(list.RemoveAll(Foo(3, 4)));
        }

        TEST_METHOD(IteratorConstructors)
        {
            SList<Foo> list;
            SList<Foo>::Iterator it;
            Assert::AreNotEqual<SList<Foo>::Iterator>(it, list.end());

            SList<Foo>::Iterator it2 = list.begin();
            Assert::AreEqual<SList<Foo>::Iterator>(it2, list.begin());
        }

        TEST_METHOD(IteratorEquality)
        {
            SList<Foo> list;
            list.PushBack(Foo(1, 2));
            list.PushBack(Foo(2, 3));
            list.PushBack(Foo(3, 4));

            // Equality
            SList<Foo>::Iterator it1 = list.begin();
            SList<Foo>::Iterator it2 = list.begin();
            Assert::AreEqual<SList<Foo>::Iterator>(it1, it2);

            // Inequality
            int count = 0;
            for (auto it = list.begin(); it != list.end(); ++it)
            {
                count++;
            }
            Assert::AreEqual<int>(count, 3);
        }

        TEST_METHOD(IteratorAssignment)
        {
            SList<Foo> list;
            list.PushBack(Foo(1, 2));
            list.PushBack(Foo(2, 3));
            list.PushBack(Foo(3, 4));

            SList<Foo>::Iterator it1 = list.begin();
            SList<Foo>::Iterator it2 = list.begin();
            Assert::AreEqual<SList<Foo>::Iterator>(it1, it2);
            ++it1;
            Assert::AreNotEqual<SList<Foo>::Iterator>(it1, it2);
            it2 = it1;
            Assert::AreEqual<SList<Foo>::Iterator>(it1, it2);
        }

        TEST_METHOD(IteratorIncrements)
        {
            SList<Foo> list;
            list.PushBack(Foo(1, 2));
            list.PushBack(Foo(2, 3));
            list.PushBack(Foo(3, 4));

            SList<Foo>::Iterator it = list.begin();

            // Postincrement
            Assert::AreEqual<Foo>(*it, Foo(1, 2));
            Assert::AreEqual<Foo>(*(it++), Foo(1, 2));
            Assert::AreEqual<Foo>(*it, Foo(2, 3));

            // Preincrement
            Assert::AreEqual(*(++it), Foo(3, 4));
            Assert::AreEqual<Foo>(*it, Foo(3, 4));
        }

        TEST_METHOD(IteratorDereference)
        {
            SList<Foo> list;
            list.PushBack(Foo(1, 2));
            list.PushBack(Foo(2, 3));
            list.PushBack(Foo(3, 4));

            SList<Foo>::Iterator it = list.begin();
            Assert::AreEqual<Foo>(*it, Foo(1, 2));
            it++;
            Assert::AreEqual<Foo>(*it, Foo(2, 3));

            const SList<Foo>::Iterator constIt = ++it;
            Assert::AreEqual<Foo>(*constIt, Foo(3, 4));
        }

    private:
        static _CrtMemState sStartMemState;
    };

    _CrtMemState SListTest::sStartMemState;
}