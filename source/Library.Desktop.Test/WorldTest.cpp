#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(WorldTest)
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
			World world;
			Assert::IsTrue(world.Name() == World::DEFAULT_NAME);
			Assert::IsTrue(world.IsPrescribedAttribute(World::KEY_NAME));
			Assert::IsTrue(world.IsPrescribedAttribute(World::KEY_SECTORS));
			Assert::IsTrue(world.Sectors().Size() == 0);
		}

		TEST_METHOD(NameTest)
		{
			World world;
			Assert::IsTrue(world.Name() == World::DEFAULT_NAME);
			Assert::IsTrue(world[World::KEY_NAME] == World::DEFAULT_NAME);

			world.SetName("Beep");
			Assert::IsTrue(world.Name() == "Beep");
			Assert::IsTrue(world[World::KEY_NAME] == "Beep");
		}

		TEST_METHOD(SectorsTest)
		{
			World world;
			Assert::IsTrue(world.Sectors().Size() == 0);

			Sector* sector = world.CreateSector();
			Assert::IsTrue(world.Sectors().Size() == 1);
			Assert::IsTrue(&world[World::KEY_SECTORS][0] == sector);

			const World* constWorld = &world;
			Assert::IsTrue(constWorld->Sectors().Size() == 1);
		}

		TEST_METHOD(CreateSector)
		{
			World world;

			Assert::IsTrue(world.Sectors().Size() == 0);

			Sector* sector1 = world.CreateSector();
			Sector* sector2 = world.CreateSector();

			Assert::IsTrue(world.Sectors().Size() == 2);

			Assert::IsTrue(sector1->GetParent() == &world);
			Assert::IsTrue(sector2->GetParent() == &world);
		}

		TEST_METHOD(Update)
		{
			World world;
			WorldState state;

			world.Update(state);

			Sector* sector1 = world.CreateSector();
			Sector* sector2 = world.CreateSector();

			Assert::IsTrue(world.Sectors().Size() == 2);

			Assert::IsTrue(state.mSector == nullptr);
			sector1;
			sector2;
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState WorldTest::sStartMemState;
}
