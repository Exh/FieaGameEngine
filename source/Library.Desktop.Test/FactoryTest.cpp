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

		TEST_METHOD(Constructor)
		{
			FooFactory fooFactory;
			BoopFactory boopFactory;
			FooFactory secondFooFactory;

			Assert::IsTrue(fooFactory.ClassName() == "Foo");
			Assert::IsTrue(boopFactory.ClassName() == "Boop");

			Assert::IsTrue(Factory<RTTI>::Find(fooFactory.ClassName()) != nullptr);
			Assert::IsTrue(Factory<RTTI>::Find(boopFactory.ClassName()) != nullptr);
		}

		TEST_METHOD(Destructor)
		{
			FooFactory* fooFactory = new FooFactory();
			BoopFactory* boopFactory = new BoopFactory();

			std::string fooName = fooFactory->ClassName();
			std::string boopName = boopFactory->ClassName();

			Assert::IsTrue(Factory<RTTI>::Find(fooName) != nullptr);
			Assert::IsTrue(Factory<RTTI>::Find(boopName) != nullptr);

			delete fooFactory;
			delete boopFactory;

			Assert::IsTrue(Factory<RTTI>::Find(fooName) == nullptr);
			Assert::IsTrue(Factory<RTTI>::Find(boopName) == nullptr);
		}

		TEST_METHOD(Find)
		{
			FooFactory* fooFactory = new FooFactory();
			BoopFactory* boopFactory = new BoopFactory();

			std::string fooName = fooFactory->ClassName();
			std::string boopName = boopFactory->ClassName();

			Assert::IsTrue(Factory<RTTI>::Find(fooName) != nullptr);
			Assert::IsTrue(Factory<RTTI>::Find(boopName) != nullptr);

			delete fooFactory;
			delete boopFactory;

			Assert::IsTrue(Factory<RTTI>::Find(fooName) == nullptr);
			Assert::IsTrue(Factory<RTTI>::Find(boopName) == nullptr);
		}

		TEST_METHOD(Create)
		{
			FooFactory fooFactory;
			BoopFactory boopFactory;

			RTTI* fooInstance = Factory<RTTI>::Create("Foo");
			RTTI* boopInstance = Factory<RTTI>::Create("Boop");
			RTTI* nullInstance = Factory<RTTI>::Create("BadClass");

			Assert::IsTrue(fooInstance->Is(Foo::TypeIdClass()));
			Assert::IsTrue(boopInstance->Is(Boop::TypeIdClass()));
			Assert::IsTrue(nullInstance == nullptr);

			delete fooInstance;
			delete boopInstance;
		}

		TEST_METHOD(IteratorBeginEnd)
		{
			Assert::IsTrue(Factory<RTTI>::begin() == Factory<RTTI>::end());

			FooFactory fooFactory;
			Assert::IsTrue((*Factory<RTTI>::begin()).second == &fooFactory);

			BoopFactory boopFactory;
			auto it = Factory<RTTI>::begin();
			++it;
			Assert::IsTrue((*it).second == &boopFactory);
		}

		TEST_METHOD(ClassName)
		{
			FooFactory fooFactory;
			BoopFactory boopFactory;

			Assert::IsTrue(fooFactory.ClassName() == "Foo");
			Assert::IsTrue(boopFactory.ClassName() == "Boop");
		}

		TEST_METHOD(Factories)
		{
			FooFactory fooFactory;
			BoopFactory boopFactory;
			HappyBarFactory happyBarFactory;

			HashMap<std::string, Factory<RTTI>*> rttiFactories = Factory<RTTI>::Factories();
			HashMap<std::string, Factory<Bar>*> barFactories = Factory<Bar>::Factories();

			Assert::IsTrue(rttiFactories.Size() == 2);
			Assert::IsTrue(barFactories.Size() == 1);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState FactoryTest::sStartMemState;
}
