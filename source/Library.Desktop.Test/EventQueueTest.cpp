#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std::chrono;
using namespace std;

#define SECTOR0_NAME "Sector0"
#define SECTOR1_NAME "Sector1"
#define ENTITY0_NAME "Entity0"
#define ENTITY0_HEALTH 100
#define ENTITY0_SPEED 3.0f


namespace LibraryDesktopTest
{
	TEST_CLASS(EventQueueTest)
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
			EventQueue queue;
			Assert::IsTrue(queue.IsEmpty() == true);
			Assert::IsTrue(queue.Size() == 0U);
		}

		TEST_METHOD(EnqueueTest)
		{
			Foo foo(1, 10);
			Event<Foo> fooEvent(foo, false);
			BasicSubscriber subscriber;

			Event<Foo>::Subscribe(subscriber);
			Assert::IsTrue(subscriber.GetFlag() == false);

			EventQueue queue;
			GameTime gameTime;
			gameTime.SetCurrentTime(high_resolution_clock::time_point(seconds(0)));
			
			queue.Enqueue(fooEvent, gameTime, milliseconds(500));
			Assert::IsTrue(queue.Size() == 1);
			Assert::IsTrue(queue.IsEmpty() == false);

			// Not delivered before delay
			queue.Update(gameTime);
			Assert::IsTrue(queue.Size() == 1);
			Assert::IsTrue(queue.IsEmpty() == false);
			Assert::IsTrue(subscriber.GetFlag() == false);

			// Duplicate event cannot be added
			queue.Enqueue(fooEvent, gameTime, milliseconds(200));
			Assert::IsTrue(queue.Size() == 1);
			Assert::IsTrue(queue.IsEmpty() == false);
			Assert::IsTrue(subscriber.GetFlag() == false);

			// At appropriate time, event is sent
			gameTime.SetCurrentTime(high_resolution_clock::time_point(seconds(1)));
			queue.Update(gameTime);
			Assert::IsTrue(queue.Size() == 0);
			Assert::IsTrue(queue.IsEmpty() == true);
			Assert::IsTrue(subscriber.GetFlag() == true);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(SendTest)
		{
			Foo foo(1, 10);
			Event<Foo> fooEvent(foo, false);
			BasicSubscriber subscriber;

			Event<Foo>::Subscribe(subscriber);
			Assert::IsTrue(subscriber.GetFlag() == false);

			EventQueue queue;
			Assert::IsTrue(queue.IsEmpty() == true);
			Assert::IsTrue(queue.Size() == 0U);

			queue.Send(fooEvent);
			Assert::IsTrue(queue.IsEmpty() == true);
			Assert::IsTrue(queue.Size() == 0U);
			Assert::IsTrue(subscriber.GetFlag() == true);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(UpdateTest)
		{
			Foo foo(1, 10);
			Event<Foo> fooEvent(foo, false);
			Event<Foo>* fooEvent2 = new Event<Foo>(Foo(2, 20));

			BasicSubscriber subscriber;

			Event<Foo>::Subscribe(subscriber);
			Assert::IsTrue(subscriber.GetFlag() == false);

			EventQueue queue;
			GameTime gameTime;
			gameTime.SetCurrentTime(high_resolution_clock::time_point(seconds(0)));

			queue.Enqueue(fooEvent, gameTime, milliseconds(500));
			Assert::IsTrue(queue.Size() == 1);
			Assert::IsTrue(queue.IsEmpty() == false);

			queue.Enqueue(*fooEvent2, gameTime, milliseconds(1500));
			Assert::IsTrue(queue.Size() == 2);
			Assert::IsTrue(queue.IsEmpty() == false);

			queue.Update(gameTime);
			Assert::IsTrue(queue.Size() == 2);
			Assert::IsTrue(queue.IsEmpty() == false);
			Assert::IsTrue(subscriber.GetFlag() == false);

			gameTime.SetCurrentTime(high_resolution_clock::time_point(seconds(1)));
			queue.Update(gameTime);
			Assert::IsTrue(queue.Size() == 1);
			Assert::IsTrue(queue.IsEmpty() == false);
			Assert::IsTrue(subscriber.GetFlag() == true);

			gameTime.SetCurrentTime(high_resolution_clock::time_point(seconds(2)));
			queue.Update(gameTime);
			Assert::IsTrue(queue.Size() == 0);
			Assert::IsTrue(queue.IsEmpty() == true);
			Assert::IsTrue(subscriber.GetFlag() == true);

			Event<Foo>::UnsubscribeAll();

			// Ensure no memory leaks, thus fooEvent2 was deleted.
		}

		TEST_METHOD(ClearTest)
		{
			Foo foo(1, 10);
			Event<Foo> fooEvent(foo, false);
			Event<Foo>* fooEvent2 = new Event<Foo>(Foo(2, 20));

			EventQueue queue;
			GameTime gameTime;
			gameTime.SetCurrentTime(high_resolution_clock::time_point(seconds(0)));

			queue.Enqueue(fooEvent, gameTime, milliseconds(300));
			queue.Enqueue(*fooEvent2, gameTime, milliseconds(400));
			Assert::IsTrue(queue.Size() == 2);
			Assert::IsTrue(queue.IsEmpty() == false);

			queue.Clear();
			Assert::IsTrue(queue.Size() == 0U);
			Assert::IsTrue(queue.IsEmpty() == true);

			// Ensure Clear() will delete events that were flagged to be destroyed,
			// and thus, no memory leaks
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EventQueueTest::sStartMemState;
}
