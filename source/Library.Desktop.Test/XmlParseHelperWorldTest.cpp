#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;


#define SECTOR0_NAME "Sector0"
#define SECTOR1_NAME "Sector1"
#define ENTITY0_NAME "Entity0"
#define ENTITY0_HEALTH 100
#define ENTITY0_SPEED 3.0f


namespace LibraryDesktopTest
{
	TEST_CLASS(XmlParseHelperWorldTest)
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
			XmlParseHelperWorld parseHelper;
		}

		TEST_METHOD(ValidParseTest)
		{
			XmlParseMaster parseMaster;
			ScopeSharedData scopeData;
			XmlParseHelperWorld parseHelperWorld;
			XmlParseHelperScope parseHelperScope;
			EntityFactory entityFactory;

			parseMaster.SetSharedData(&scopeData);
			parseMaster.AddHelper(parseHelperWorld);
			parseMaster.AddHelper(parseHelperScope);

			parseMaster.ParseFromFile("../../../files/WorldTest1.xml");

			World* world = static_cast<World*>(scopeData.mScope);

			Assert::IsTrue(world->Sectors()[0].Is(Sector::TypeIdClass()));
			Assert::IsTrue(world->Sectors()[1].Is(Sector::TypeIdClass()));


			Sector& sector0 = static_cast<Sector&>(world->Sectors()[0]);
			Sector& sector1 = static_cast<Sector&>(world->Sectors()[1]);

			Assert::IsTrue(world->Sectors().Size() == 2);

			Assert::IsTrue(sector0.Name() == SECTOR0_NAME);
			Assert::IsTrue(sector1.Name() == SECTOR1_NAME);
			Assert::IsTrue(sector0.Entities().Size() == 1);
			Assert::IsTrue(sector1.Entities().Size() == 0);

			Assert::IsTrue(sector0.Entities()[0].Is(Entity::TypeIdClass()));

			Entity& entity0 = static_cast<Entity&>(sector0.Entities()[0]);
			Assert::IsTrue(entity0.Name() == ENTITY0_NAME);
			Assert::IsTrue(entity0["Health"] == ENTITY0_HEALTH);
			Assert::IsTrue(entity0["Speed"] == ENTITY0_SPEED);

			delete scopeData.mScope;
			scopeData.mScope = nullptr;
			parseMaster.ParseFromFile("../../../files/WorldTest2.xml");
		}

		TEST_METHOD(CloneTest)
		{
			XmlParseHelperWorld helper1;
			IXmlParseHelper* helper2 = helper1.Clone();

			Assert::IsTrue(&helper1 != helper2);
			delete helper2;
		}

		TEST_METHOD(StartElementHandler)
		{
			XmlParseMaster parseMaster;
			XmlParseHelperWorld parseHelperWorld;
			XmlParseHelperScope parseHelperScope;

			parseMaster.ParseFromString("<World></World>");
		}

		TEST_METHOD(EndElementHandler)
		{
			XmlParseMaster parseMaster;
			ScopeSharedData scopeData;
			XmlParseHelperWorld parseHelperWorld;
			XmlParseHelperScope parseHelperScope;
			EntityFactory entityFactory;

			parseMaster.SetSharedData(&scopeData);
			parseMaster.AddHelper(parseHelperWorld);
			parseMaster.AddHelper(parseHelperScope);

			parseMaster.ParseFromFile("../../../files/WorldTest1.xml");

			World* world = static_cast<World*>(scopeData.mScope);

			Assert::IsTrue(world->Sectors()[0].Is(Sector::TypeIdClass()));
			Assert::IsTrue(world->Sectors()[1].Is(Sector::TypeIdClass()));


			Sector& sector0 = static_cast<Sector&>(world->Sectors()[0]);
			Sector& sector1 = static_cast<Sector&>(world->Sectors()[1]);

			Assert::IsTrue(world->Sectors().Size() == 2);

			Assert::IsTrue(sector0.Name() == SECTOR0_NAME);
			Assert::IsTrue(sector1.Name() == SECTOR1_NAME);
			Assert::IsTrue(sector0.Entities().Size() == 1);
			Assert::IsTrue(sector1.Entities().Size() == 0);

			Assert::IsTrue(sector0.Entities()[0].Is(Entity::TypeIdClass()));

			Entity& entity0 = static_cast<Entity&>(sector0.Entities()[0]);
			Assert::IsTrue(entity0.Name() == ENTITY0_NAME);
			Assert::IsTrue(entity0["Health"] == ENTITY0_HEALTH);
			Assert::IsTrue(entity0["Speed"] == ENTITY0_SPEED);
		}

		TEST_METHOD(InvalidParseTests)
		{
			XmlParseMaster parseMaster;
			ScopeSharedData scopeData;
			XmlParseHelperWorld parseHelperWorld;
			XmlParseHelperScope parseHelperScope;
			EntityFactory entityFactory;

			parseMaster.SetSharedData(&scopeData);
			parseMaster.AddHelper(parseHelperWorld);
			parseMaster.AddHelper(parseHelperScope);

			Assert::ExpectException<std::exception>([&parseMaster] {parseMaster.ParseFromFile("../../../files/WorldTestInvalid1.xml"); });
			delete scopeData.mScope;
			scopeData.mScope = nullptr;

			Assert::ExpectException<std::exception>([&parseMaster] {parseMaster.ParseFromFile("../../../files/WorldTestInvalid2.xml"); });
			delete scopeData.mScope;
			scopeData.mScope = nullptr;

			Assert::ExpectException<std::exception>([&parseMaster] {parseMaster.ParseFromFile("../../../files/WorldTestInvalid3.xml"); });
			delete scopeData.mScope;
			scopeData.mScope = nullptr;

			Assert::ExpectException<std::exception>([&parseMaster] {parseMaster.ParseFromFile("../../../files/WorldTestInvalid4.xml"); });
			delete scopeData.mScope;
			scopeData.mScope = nullptr;

			Assert::ExpectException<std::exception>([&parseMaster] {parseMaster.ParseFromFile("../../../files/WorldTestInvalid5.xml"); });
			delete scopeData.mScope;
			scopeData.mScope = nullptr;

		}

		TEST_METHOD(ValidActionParseTest)
		{
			XmlParseMaster parseMaster;
			ScopeSharedData scopeData;
			XmlParseHelperWorld parseHelperWorld;
			XmlParseHelperScope parseHelperScope;
			EntityFactory entityFactory;
			ActionIncrementFactory actionIncrementFactory;
			ActionIfFactory actionIfFactory;

			parseMaster.SetSharedData(&scopeData);
			parseMaster.AddHelper(parseHelperWorld);
			parseMaster.AddHelper(parseHelperScope);

			parseMaster.ParseFromFile("../../../files/WorldTestAction1.xml");

			World* world = static_cast<World*>(scopeData.mScope);

			Assert::IsTrue(world->Sectors()[0].Is(Sector::TypeIdClass()));
			Assert::IsTrue(world->Sectors()[1].Is(Sector::TypeIdClass()));


			Sector& sector0 = static_cast<Sector&>(world->Sectors()[0]);
			Sector& sector1 = static_cast<Sector&>(world->Sectors()[1]);

			Assert::IsTrue(world->Sectors().Size() == 2);

			Assert::IsTrue(sector0.Name() == SECTOR0_NAME);
			Assert::IsTrue(sector1.Name() == SECTOR1_NAME);
			Assert::IsTrue(sector0.Entities().Size() == 1);
			Assert::IsTrue(sector1.Entities().Size() == 0);

			Assert::IsTrue(sector0.Entities()[0].Is(Entity::TypeIdClass()));

			Entity& entity0 = static_cast<Entity&>(sector0.Entities()[0]);
			Assert::IsTrue(entity0.Name() == ENTITY0_NAME);
			Assert::IsTrue(entity0["Health"] == ENTITY0_HEALTH);
			Assert::IsTrue(entity0["Speed"] == ENTITY0_SPEED);

			delete scopeData.mScope;
			scopeData.mScope = nullptr;
			Assert::ExpectException<std::exception>([&parseMaster] {parseMaster.ParseFromFile("../../../files/WorldTestAction2.xml");});
			
			while (scopeData.mScope->GetParent() != nullptr)
			{
				scopeData.mScope = scopeData.mScope->GetParent();
			}

			delete scopeData.mScope;
			scopeData.mScope = nullptr;
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XmlParseHelperWorldTest::sStartMemState;
}
