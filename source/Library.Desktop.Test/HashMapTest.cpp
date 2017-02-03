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

		}


	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState HashMapTest::sStartMemState;
}
