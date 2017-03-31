#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(WorldTest)
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

			Attributed::ClearPrescribedAttributeCache();

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
			World world;
			Assert::IsTrue(world.Name() == World::DEFAULT_NAME);
			Assert::IsTrue(world.IsPrescribedAttribute(World::KEY_NAME));
			Assert::IsTrue(world.IsPrescribedAttribute(World::KEY_SECTORS));
			Assert::IsTrue(world.Sectors().Size() == 0);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState WorldTest::sStartMemState;
}
