#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std::chrono;
using namespace std;

#define TEST_ITERATIONS 2000

namespace LibraryDesktopTest
{
	TEST_CLASS(AsyncEventTest)
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

		TEST_METHOD(EventDeliver)
		{
			MessageAddSubscriber messageAdd;
			Event<MessageAddSubscriber> eventAdd(messageAdd, false);

			// Allocate on heap to avoid any stack issues
			SubscriberAdder* adders = new SubscriberAdder[TEST_ITERATIONS];
			Assert::IsTrue(Event<MessageAddSubscriber>::SubscriberCount() == TEST_ITERATIONS);

			eventAdd.Deliver();
			Assert::IsTrue(Event<MessageAddSubscriber>::SubscriberCount() == TEST_ITERATIONS * 2);

			Event<MessageAddSubscriber>::UnsubscribeAll();
			delete [] adders;
			adders = nullptr;
		}

		TEST_METHOD(EventQueueUpdate)
		{
			GameTime gameTime;

			EventQueue eventQueue;
			gameTime.SetCurrentTime(high_resolution_clock::time_point(seconds(0)))
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AsyncEventTest::sStartMemState;
}
