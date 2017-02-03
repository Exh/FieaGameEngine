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
			HashMap<int, int> intMap;
			Assert::AreEqual(intMap.Size(), 0U);
			Assert::AreEqual(intMap.Capacity(), DEFAULT_CAPACITY);

			// intPointer test

			// string test

			// Foo test

			// FooPointer test
		}


	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState HashMapTest::sStartMemState;
}
