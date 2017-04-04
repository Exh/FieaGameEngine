#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(ActionTest)
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

		TEST_METHOD(ConstructorTest)
		{
			ActionIncrement action;
			Assert::IsTrue(action.IsPrescribedAttribute(Action::KEY_NAME));
		}

		TEST_METHOD(UpdateTest)
		{
			ActionIncrement action;
			action["testInteger"] = 10;
			action[ActionIncrement::KEY_TARGET] = "testInteger";

			WorldState state;

			Assert::IsTrue(action["testInteger"] == 10);
			action.Update(state);
			Assert::IsTrue(action["testInteger"] == 11);
		}

		TEST_METHOD(NameTest)
		{
			ActionIncrement action;
			Assert::IsTrue(action.Name() == Action::DEFAULT_NAME);
			action.SetName("Beep");
			Assert::IsTrue(action.Name() == "Beep");

			const Action* constAction = &action;
			Assert::IsTrue(constAction->Name() == "Beep");
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ActionTest::sStartMemState;
}
