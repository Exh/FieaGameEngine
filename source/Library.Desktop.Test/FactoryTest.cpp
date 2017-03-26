#pragma once

#include "pch.h"
#include "Beep.h"

#include <exception>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(FactoryTest)
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

		TEST_METHOD(ConstructorTest)
		{
			FooFactory fooFactory;
			BoopFactory boopFactory;

			Assert::IsTrue(fooFactory.ClassName() == "Foo");
			Assert::IsTrue(boopFactory.ClassName() == "Boop");

			Assert::IsTrue(Factory<RTTI>::Find(fooFactory.ClassName()) != nullptr);
			Assert::IsTrue(Factory<RTTI>::Find(boopFactory.ClassName()) != nullptr);
		}

		TEST_METHOD(DestructorTest)
		{
		
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState FactoryTest::sStartMemState;
}
