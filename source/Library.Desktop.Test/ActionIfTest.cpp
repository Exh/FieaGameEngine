#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(ActionIfTest)
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
			ActionIf action;
			Assert::IsTrue(action.IsPrescribedAttribute(Action::KEY_NAME));
			Assert::IsTrue(action.IsPrescribedAttribute(ActionIf::KEY_CONDITION));
			Assert::IsTrue(action.Is(Action::TypeIdClass()));
			Assert::IsTrue(action.Is(ActionIf::TypeIdClass()));
		}

		TEST_METHOD(UpdateTest)
		{
			ActionIf actionIf;
			ActionIncrement* incOnce = new ActionIncrement();
			ActionList* incTwice = new ActionList();
			WorldState state;

			ActionIncrementFactory incFactory;

			ActionIncrement* inc1 = incTwice->CreateAction("ActionIncrement", "inc1")->As<ActionIncrement>();
			ActionIncrement* inc2 = incTwice->CreateAction("ActionIncrement", "inc2")->As<ActionIncrement>();
			
			actionIf["val"] = 10;
			(*inc1)[ActionIncrement::KEY_TARGET] = "val";
			(*inc2)[ActionIncrement::KEY_TARGET] = "val";
			(*incOnce)[ActionIncrement::KEY_TARGET] = "val";

			// Would execute then, but none found
			actionIf[ActionIf::KEY_CONDITION] = 1;
			Assert::IsTrue(actionIf["val"] == 10);
			actionIf.Update(state);
			Assert::IsTrue(actionIf["val"] == 10);

			// Would execute else, but none found
			actionIf[ActionIf::KEY_CONDITION] = 0;
			Assert::IsTrue(actionIf["val"] == 10);
			actionIf.Update(state);
			Assert::IsTrue(actionIf["val"] == 10);

			actionIf.Adopt(*incOnce, ActionIf::KEY_THEN);
			actionIf.Adopt(*incTwice, ActionIf::KEY_ELSE);

			// Hit the then clause
			actionIf[ActionIf::KEY_CONDITION] = 1;
			Assert::IsTrue(actionIf["val"] == 10);
			actionIf.Update(state);
			Assert::IsTrue(actionIf["val"] == 11);

			// Hit the else clause
			actionIf[ActionIf::KEY_CONDITION] = 0;
			Assert::IsTrue(actionIf["val"] == 11);
			actionIf.Update(state);
			Assert::IsTrue(actionIf["val"] == 13);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ActionIfTest::sStartMemState;
}
