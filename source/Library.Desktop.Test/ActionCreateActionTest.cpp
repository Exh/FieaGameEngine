#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(ActionCreateActionTest)
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
			ActionCreateAction action;
			Assert::IsTrue(action.IsPrescribedAttribute(Action::KEY_NAME));
			Assert::IsTrue(action.IsPrescribedAttribute(ActionCreateAction::KEY_PROTOTYPE_CLASS));
			Assert::IsTrue(action.IsPrescribedAttribute(ActionCreateAction::KEY_INSTANCE_NAME));

			Assert::IsTrue(action[ActionCreateAction::KEY_PROTOTYPE_CLASS] == ActionCreateAction::DEFAULT_PROTOTYPE_CLASS);
			Assert::IsTrue(action[ActionCreateAction::KEY_INSTANCE_NAME] == ActionCreateAction::DEFAULT_INSTANCE_NAME);
		}

		TEST_METHOD(UpdateTest)
		{
			ActionCreateAction* create;
			ActionIncrementFactory incrementActionFactory;
			ActionCreateActionFactory createActionFactory;
			Entity entity;
			WorldState state;

			entity.SetName("Chips");

			entity.CreateAction("ActionCreateAction", "Creator");
			create = entity.Actions()[0].As<ActionCreateAction>();

			create->Append(ActionCreateAction::KEY_PROTOTYPE_CLASS) = "ActionIncrement";
			create->Append(ActionCreateAction::KEY_INSTANCE_NAME) = "Beep";

			Assert::IsTrue(entity.Actions().Size() == 1);
			Assert::IsTrue(&(entity.Actions()[0]) == create);
			create->Update(state);
			Assert::IsTrue(entity.Actions().Size() == 2);
			Assert::IsTrue(&(entity.Actions()[0]) == create);
			Assert::IsTrue(entity.Actions()[1][Action::KEY_NAME] == "Beep");
			Assert::IsTrue(entity.Actions()[1].Is(ActionIncrement::TypeIdClass()));
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ActionCreateActionTest::sStartMemState;
}
