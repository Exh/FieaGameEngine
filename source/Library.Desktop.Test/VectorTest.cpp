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
            Vector<Foo> vector;
            Assert::IsTrue(vector.IsEmpty());
        }

        TEST_METHOD(SubscriptOperator)
        {
            Vector<Foo> vector;

            auto exceptionalCase1 = [&vector]() { vector[0]; };
            Assert::ExpectException<std::exception>(exceptionalCase1, L"Out of bounds access threw no exception");

            vector.PushBack(Foo(1, 2));
            vector.PushBack(Foo(2, 3));
            vector.PushBack(Foo(3, 4));

            Assert::AreEqual<Foo>(vector[0], Foo(1, 2));
            Assert::AreEqual<Foo>(vector[1], Foo(2, 3));
            Assert::AreEqual<Foo>(vector[2], Foo(3, 4));
            auto exceptionalCase2 = [&vector](){ vector[3]; };
            Assert::ExpectException<std::exception>(exceptionalCase2, L"Out of bounds access threw no exception");
        }

        TEST_METHOD(CopySemantics)
        {
            // Copy constructor tests
            Vector<Foo> vector1;
            vector1.PushBack(Foo(1, 2));
            vector1.PushBack(Foo(2, 3));
            vector1.PushBack(Foo(3, 4));

            Vector<Foo> vector2(vector1);

            Assert::AreEqual<Foo>(vector1[0], vector2[0]);
            Assert::AreEqual<Foo>(vector1[1], vector2[1]);
            Assert::AreEqual<Foo>(vector1[2], vector2[2]);

            // Assignment operator
            //@@ TODO
        }

        

    private:
        static _CrtMemState sStartMemState;
    };

    _CrtMemState VectorTest::sStartMemState;
}