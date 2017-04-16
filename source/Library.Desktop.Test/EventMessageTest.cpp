#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(EventMessageTest)
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
			EventMessage eventMessage;
			Assert::IsTrue(eventMessage.GetWorldState() == nullptr);
			Assert::IsTrue(eventMessage.GetSubtype() == "");
		}

		TEST_METHOD(SubtypeTest)
		{
			EventMessage eventMessage;
			eventMessage.SetSubtype("Beep");

			Assert::IsTrue(eventMessage.GetSubtype() == "Beep");
		}

		TEST_METHOD(WorldStateTest)
		{
			WorldState state;
			EventMessage eventMessage;

			eventMessage.SetWorldState(&state);
			Assert::IsTrue(eventMessage.GetWorldState() == &state);

			const EventMessage* constMessage = &eventMessage;
			Assert::IsTrue(constMessage->GetWorldState() == &state);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EventMessageTest::sStartMemState;
}
