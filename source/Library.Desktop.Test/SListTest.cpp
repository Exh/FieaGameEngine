#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

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

        TEST_METHOD(SListConstructors)
        {
            SList<int> list;
            list.PushFront(2);
            list.PopFront();
            list.PushBack(3);
            list.IsEmpty();
            list.Front();
            const int& front = list.Front();
            list.Back();
            const int& back = list.Back();
            list.Size();

            SList<int> list2;
            list2.PushBack(10);
            list2.PushBack(20);
            list2 = list;

            SList<int> list3(list2);



            // Remove warnings
            (front);
            (back);
            Assert::AreEqual(0, 0);
        }

    private:
        static _CrtMemState sStartMemState;
    };

    _CrtMemState SListTest::sStartMemState;
}