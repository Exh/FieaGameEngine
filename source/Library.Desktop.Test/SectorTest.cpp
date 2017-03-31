#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(SectorTest)
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
			Sector sector;
			Assert::IsTrue(sector.Name() == Sector::DEFAULT_NAME);
			Assert::IsTrue(sector.IsPrescribedAttribute(Sector::KEY_NAME));
			Assert::IsTrue(sector.IsPrescribedAttribute(Sector::KEY_ENTITIES));
			Assert::IsTrue(sector[Sector::KEY_ENTITIES].Size() == 0);
			Assert::IsTrue(sector.Entities().Size() == 0);
		}

		TEST_METHOD(Name)
		{
			Sector sector;
			Assert::IsTrue(sector.Name() == Sector::DEFAULT_NAME);
			Assert::IsTrue(sector[Sector::KEY_NAME] == Sector::DEFAULT_NAME);

			sector.SetName("Beep");
			Assert::IsTrue(sector.Name() == "Beep");
			Assert::IsTrue(sector[Sector::KEY_NAME] == "Beep");
		}

		TEST_METHOD(EntitiesTest)
		{
			EntityFactory entityFactor;
			Entity* entity = nullptr;
			Sector sector;

			Assert::IsTrue(sector.Entities().Size() == 0);
			entity = sector.CreateEntity("Entity");
			entity->SetName("Boop");

			Assert::IsTrue(sector.Entities().Size() == 1);
			Assert::IsTrue(sector.Entities()[0][Entity::KEY_NAME] == "Boop");

			const Sector* constSector = &sector;
			Assert::IsTrue(constSector->Entities().Size() == 1);
		}

		TEST_METHOD(CreateEntityTest)
		{
			Sector sector;
			Entity* entity = nullptr;
			EntityFactory entityFactory;

			Assert::IsTrue(sector.Entities().Size() == 0);
			Assert::ExpectException<std::exception>([&sector] {sector.CreateEntity("BadEntityType");});

			entity = sector.CreateEntity("Entity");

			Assert::IsTrue(sector.Entities().Size() == 1);
		}

		TEST_METHOD(GetWorld)
		{
			World world;
			Sector* sector = world.CreateSector();

			Assert::IsTrue(sector->GetWorld() == &world);

			const Sector* constSector = sector;
			Assert::IsTrue(sector->GetWorld() == constSector->GetWorld());
		}

		TEST_METHOD(Update)
		{
			WorldState state;
			Sector sector;
			EntityFactory entityFactory;

			sector.Update(state);

			Entity* entity1 = sector.CreateEntity("Entity");
			Entity* entity2 = sector.CreateEntity("Entity");

			sector.Update(state);

			Assert::IsTrue(state.mEntity == nullptr);
			entity1;
			entity2;
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SectorTest::sStartMemState;
}
