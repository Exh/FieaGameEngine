#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(ReactionAttributedTest)
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

			Event<EventMessage>::UnsubscribeAll();
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
			ReactionAttributed reaction;
			Assert::IsTrue(reaction[ReactionAttributed::KEY_SUBTYPE] == ReactionAttributed::DEFAULT_SUBTYPE);
			Assert::IsTrue(reaction.IsPrescribedAttribute(ReactionAttributed::KEY_SUBTYPE));
		}

		TEST_METHOD(SetSubtype)
		{
			ReactionAttributed reaction;
			reaction.SetSubtype("Beep");

			Assert::IsTrue(reaction[ReactionAttributed::KEY_SUBTYPE] == "Beep");
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ReactionAttributedTest::sStartMemState;
}
