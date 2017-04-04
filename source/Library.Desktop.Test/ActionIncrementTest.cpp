#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(ActionIncrementTest)
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
			ActionIncrement actionList;
			Assert::IsTrue(actionList.IsPrescribedAttribute(Action::KEY_NAME));
			Assert::IsTrue(actionList.Is(Action::TypeIdClass()));
			Assert::IsTrue(actionList.Is(ActionIncrement::TypeIdClass()));
		}

		TEST_METHOD(UpdateTest)
		{
			ActionList actionList;
			ActionIncrement* inc1 = new ActionIncrement();
			ActionIncrement* inc2 = new ActionIncrement();
			WorldState state;

			(*inc1)[ActionIncrement::KEY_TARGET] = "number";
			(*inc2)[ActionIncrement::KEY_TARGET] = "number";
			(*inc1)["number"] = 10;
			actionList["number"] = 20;

			actionList.Adopt(*inc1, ActionList::KEY_ACTIONS);
			actionList.Adopt(*inc2, ActionList::KEY_ACTIONS);

			Assert::IsTrue((*inc1)["number"].GetInteger() == 10);
			Assert::IsTrue(actionList["number"].GetInteger() == 20);

			actionList.Update(state);

			Assert::IsTrue((*inc1)["number"].GetInteger() == 11);
			Assert::IsTrue(actionList["number"].GetInteger() == 21);

			delete inc1;
			delete inc2;
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ActionIncrementTest::sStartMemState;
}
