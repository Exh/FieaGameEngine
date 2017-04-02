#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(EntityTest)
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
			Entity entity;
			const Entity* constEntity = &entity;
			Assert::IsTrue(entity.IsPrescribedAttribute("this"));
			Assert::IsTrue(entity.IsPrescribedAttribute(Entity::KEY_NAME));
			Assert::IsTrue(entity[Entity::KEY_NAME].GetString() == Entity::DEFAULT_NAME);

			Assert::ExpectException<std::exception>([&entity]{entity.GetSector();});
			Assert::ExpectException<std::exception>([&constEntity] {constEntity->GetSector(); });

		}

		TEST_METHOD(NameTest)
		{
			Entity entity;
			const std::string& name = entity.Name();

			Assert::IsTrue(name == Entity::DEFAULT_NAME);
			Assert::IsTrue(entity[Entity::KEY_NAME] == Entity::DEFAULT_NAME);

			entity.SetName("Beep");
			Assert::IsTrue(name == "Beep");
			Assert::IsTrue(entity[Entity::KEY_NAME] == "Beep");
		}

		TEST_METHOD(GetSectorTest)
		{
			EntityFactory entityFactory;

			Entity entity;
			Assert::ExpectException<std::exception>([&entity]{entity.GetSector();});

			Sector sector;
			Entity* entity2 = sector.CreateEntity("Entity");
			Assert::IsTrue(entity2->GetSector() == &sector);

			const Entity* constEntity2 = entity2;
			Assert::IsTrue(constEntity2->GetSector() == &sector);
		}

		TEST_METHOD(UpdateTest)
		{
			WorldState worldState;
			Entity entity;
			entity.Update(worldState);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EntityTest::sStartMemState;
}
