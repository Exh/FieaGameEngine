
#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(GameTest)
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
			Game game;
		}

		TEST_METHOD(InitializeTest)
		{
			Game game;
			game.Initialize();
		}

		TEST_METHOD(LoadWorldTest)
		{
			Game game;
			game.Initialize();
			game.LoadWorld("../../../files/WorldTest1.xml");
			//game.LoadWorld("../../../files/WorldTest1.xml");
		}

		TEST_METHOD(UpdateTest)
		{
			Game game;
			game.Initialize();
			game.Update();
			game.LoadWorld("../../../files/WorldTest1.xml");
			game.Update();
		}

		TEST_METHOD(RenderTest)
		{
			Game game;
			game.Initialize();
			game.Render();
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState GameTest::sStartMemState;
}
