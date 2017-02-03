#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			inline std::wstring ToString<HashMap<Foo, int>::Iterator>(const HashMap<Foo, int>::Iterator& it)
			{
				(it);
				return L"HashMap Iterator string!";
			}

			template<>
			inline std::wstring ToString<HashMap<Foo*, int>::Iterator>(const HashMap<Foo*, int>::Iterator& it)
			{
				(it);
				return L"HashMap Iterator string!";
			}

			template<>
			inline std::wstring ToString<HashMap<int, int>::Iterator>(const HashMap<int, int>::Iterator& it)
			{
				(it);
				return L"HashMap Iterator string!";
			}

			template<>
			inline std::wstring ToString<HashMap<int*, int>::Iterator>(const HashMap<int*, int>::Iterator& it)
			{
				(it);
				return L"HashMap Iterator string!";
			}

			template<>
			inline std::wstring ToString<HashMap<string, int>::Iterator>(const HashMap<string, int>::Iterator& it)
			{
				(it);
				return L"HashMap Iterator string!";
			}
		}
	}
}

namespace LibraryDesktopTest
{
	typedef Foo::FooHashFunctor FooHash;

	TEST_CLASS(HashMapTest)
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
			const std::uint32_t DEFAULT_CAPACITY = 13;

			// int test
			HashMap<int32_t, int> intMap;
			Assert::AreEqual(intMap.Size(), 0U);
			Assert::AreEqual(intMap.Capacity(), DEFAULT_CAPACITY);
			Assert::AreEqual(intMap.begin(), intMap.end());

			// intPointer test
			HashMap<int32_t*, int> intPointerMap;
			Assert::AreEqual(intPointerMap.Size(), 0U);
			Assert::AreEqual(intPointerMap.Capacity(), DEFAULT_CAPACITY);
			Assert::AreEqual(intPointerMap.begin(), intPointerMap.end());

			// string test
			HashMap<string, int> stringMap;
			Assert::AreEqual(stringMap.Size(), 0U);
			Assert::AreEqual(stringMap.Capacity(), DEFAULT_CAPACITY);
			Assert::AreEqual(stringMap.begin(), stringMap.end());

			// Foo test
			HashMap<Foo, int> fooMap;
			Assert::AreEqual(fooMap.Size(), 0U);
			Assert::AreEqual(fooMap.Capacity(), DEFAULT_CAPACITY);
			Assert::AreEqual(fooMap.begin(), fooMap.end());

			// FooPointer test
			HashMap<Foo*, int> fooPointerMap;
			Assert::AreEqual(fooPointerMap.Size(), 0U);
			Assert::AreEqual(fooPointerMap.Capacity(), DEFAULT_CAPACITY);
			Assert::AreEqual(fooPointerMap.begin(), fooPointerMap.end());
		}

		TEST_METHOD(CopySemantics)
		{
			int int1 = 1;
			int int2 = 2;
			string string1 = "one";
			string string2 = "two";
			Foo foo1(1, 2);
			Foo foo2(2, 3);
			int value1 = 10;
			int value2 = 20;

			// int tests
			HashMap<int32_t, int> intMap1;
			intMap1.Insert(pair<int32_t, int>(int1, value1));
			Assert::AreEqual(intMap1.Size(), 1U);
			HashMap<int32_t, int> intMap2(intMap1);
			Assert::AreEqual(intMap2[int1], value1);
			Assert::AreEqual(intMap2.Size(), 1U);
			intMap2[int2] = value2;
			Assert::AreNotEqual(intMap2[int2], intMap1[int2]);
			intMap1 = intMap2;
			Assert::AreEqual(intMap2[int2], intMap1[int2]);

			// intPointer tests
			HashMap<int32_t*, int> intPointerMap1;
			intPointerMap1.Insert(pair<int32_t*, int>(&int1, value1));
			Assert::AreEqual(intPointerMap1.Size(), 1U);
			HashMap<int32_t*, int> intPointerMap2(intPointerMap1);
			Assert::AreEqual(intPointerMap2[&int1], value1);
			Assert::AreEqual(intPointerMap2.Size(), 1U);
			intPointerMap2[&int2] = value2;
			Assert::AreNotEqual(intPointerMap2[&int2], intPointerMap1[&int2]);
			intPointerMap1 = intPointerMap2;
			Assert::AreEqual(intPointerMap2[&int2], intPointerMap1[&int2]);

			// string tests
			HashMap<string, int> stringMap1;
			stringMap1.Insert(pair<string, int>(string1, value1));
			Assert::AreEqual(stringMap1.Size(), 1U);
			HashMap<string, int> stringMap2(stringMap1);
			Assert::AreEqual(stringMap2[string1], value1);
			Assert::AreEqual(stringMap2.Size(), 1U);
			stringMap2[string2] = value2;
			Assert::AreNotEqual(stringMap2[string2], stringMap1[string2]);
			stringMap1 = stringMap2;
			Assert::AreEqual(stringMap2[string2], stringMap1[string2]);

			// Foo tests
			HashMap<Foo, int, FooHash> fooMap1;
			fooMap1.Insert(pair<Foo, int>(foo1, value1));
			Assert::AreEqual(fooMap1.Size(), 1U);
			HashMap<Foo, int, FooHash> fooMap2(fooMap1);
			Assert::AreEqual(fooMap2[foo1], value1);
			Assert::AreEqual(fooMap2.Size(), 1U);
			fooMap2[foo2] = value2;
			Assert::AreNotEqual(fooMap2[foo2], fooMap1[foo2]);
			fooMap1 = fooMap2;
			Assert::AreEqual(fooMap2[foo2], fooMap1[foo2]);

			// FooPointer tests
			HashMap<Foo*, int, FooHash> fooPointerMap1;
			fooPointerMap1.Insert(pair<Foo*, int>(&foo1, value1));
			Assert::AreEqual(fooPointerMap1.Size(), 1U);
			HashMap<Foo*, int, FooHash> fooPointerMap2(fooPointerMap1);
			Assert::AreEqual(fooPointerMap2[&foo1], value1);
			Assert::AreEqual(fooPointerMap2.Size(), 1U);
			fooPointerMap2[&foo2] = value2;
			Assert::AreNotEqual(fooPointerMap2[&foo2], fooPointerMap1[&foo2]);
			fooPointerMap1 = fooPointerMap2;
			Assert::AreEqual(fooPointerMap2[&foo2], fooPointerMap1[&foo2]);

		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState HashMapTest::sStartMemState;
}
