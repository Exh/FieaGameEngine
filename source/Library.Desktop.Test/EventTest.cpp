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
	TEST_CLASS(EventTest)
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

		TEST_METHOD(EventConstructor)
		{
			Foo foo(1, 10);
			Event<Foo>* fooEvent = new Event<Foo>(foo);
			Assert::IsTrue(foo == fooEvent->Message());
			Assert::IsTrue(fooEvent->Delay() == milliseconds(0));
			Assert::IsTrue(fooEvent->DeleteAfterPublishing() == true);

			Foo foo2(2, 20);
			Event<Foo> fooEvent2(foo2, false);
			Assert::IsTrue(fooEvent2.DeleteAfterPublishing() == false);

			delete fooEvent;
		}

		TEST_METHOD(EventTime)
		{
			Foo foo(1, 10);
			Event<Foo> fooEvent(foo, false);

			fooEvent.SetTime(high_resolution_clock::time_point(seconds(1)), milliseconds(0));
			Assert::IsTrue(fooEvent.TimeEnqueued().time_since_epoch() == seconds(1));
			Assert::IsTrue(fooEvent.Delay() == milliseconds(0));
		}

		TEST_METHOD(EventIsExpired)
		{
			Foo foo(1, 10);
			Event<Foo> fooEvent(foo, false);

			fooEvent.SetTime(high_resolution_clock::time_point(seconds(1)), milliseconds(500));
			Assert::IsTrue(fooEvent.TimeEnqueued().time_since_epoch() == seconds(1));
			Assert::IsTrue(fooEvent.Delay() == milliseconds(500));

			Assert::IsTrue(fooEvent.IsExpired(high_resolution_clock::time_point(seconds(0))) == false);
			Assert::IsTrue(fooEvent.IsExpired(high_resolution_clock::time_point(seconds(1) + milliseconds(200))) == false);
			Assert::IsTrue(fooEvent.IsExpired(high_resolution_clock::time_point(seconds(1) + milliseconds(600))) == true);
		}

		TEST_METHOD(EventDeliver)
		{
			Foo foo(1, 10);
			Event<Foo> fooEvent(foo, false);
			BasicSubscriber subscriber;

			Event<Foo>::Subscribe(subscriber);
			Assert::IsTrue(subscriber.GetFlag() == false);
			fooEvent.Deliver();
			Assert::IsTrue(subscriber.GetFlag() == true);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(EventDeleteAfterPublishing)
		{
			Foo foo1(1, 10);
			Event<Foo> foo1Event(foo1, false);

			Foo foo2(2, 20);
			Event<Foo>* foo2Event = new Event<Foo>(foo2, true);

			Assert::IsTrue(foo1Event.DeleteAfterPublishing() == false);
			Assert::IsTrue(foo2Event->DeleteAfterPublishing() == true);

			delete foo2Event;
		}

		TEST_METHOD(EventCopySemantics)
		{
			Foo foo1(1, 10);
			Event<Foo> foo1Event(foo1, false);
			foo1Event.SetTime(high_resolution_clock::time_point(seconds(3)), milliseconds(123));

			Event<Foo> foo2Event(foo1Event);

			Assert::IsTrue(foo1Event.TimeEnqueued() == foo2Event.TimeEnqueued());
			Assert::IsTrue(foo1Event.Delay() == foo2Event.Delay());
			Assert::IsTrue(foo1Event.DeleteAfterPublishing() == foo2Event.DeleteAfterPublishing());
		
			Event<Foo> foo3Event(Foo (3, 30));
			foo3Event = foo1Event;

			Assert::IsTrue(foo1Event.TimeEnqueued() == foo3Event.TimeEnqueued());
			Assert::IsTrue(foo1Event.Delay() == foo3Event.Delay());
			Assert::IsTrue(foo1Event.DeleteAfterPublishing() == foo3Event.DeleteAfterPublishing());

			foo3Event = foo3Event;
		}

		TEST_METHOD(EventMoveSemantics)
		{
			Foo foo1(1, 10);
			Event<Foo> foo1Event(foo1, true);
			foo1Event.SetTime(high_resolution_clock::time_point(seconds(3)), milliseconds(123));

			Event<Foo> foo2Event(move(foo1Event));

			Assert::IsTrue(foo2Event.TimeEnqueued() == high_resolution_clock::time_point(seconds(3)));
			Assert::IsTrue(foo2Event.Delay() == milliseconds(123));
			Assert::IsTrue(foo2Event.DeleteAfterPublishing() == true);

			Assert::IsTrue(foo1Event.DeleteAfterPublishing() == false);

			Event<Foo> foo3Event(Foo(3, 30));
			foo3Event = move(foo2Event);

			Assert::IsTrue(foo3Event.TimeEnqueued() == high_resolution_clock::time_point(seconds(3)));
			Assert::IsTrue(foo3Event.Delay() == milliseconds(123));
			Assert::IsTrue(foo3Event.DeleteAfterPublishing() == true);

			Assert::IsTrue(foo2Event.DeleteAfterPublishing() == false);

			foo3Event = foo3Event;
		}

		TEST_METHOD(EventSubscribe)
		{
			Foo foo(1, 10);
			Event<Foo> fooEvent(foo, false);
			BasicSubscriber subscriber;

			Event<Foo>::Subscribe(subscriber);
			Assert::IsTrue(subscriber.GetFlag() == false);
			fooEvent.Deliver();
			Assert::IsTrue(subscriber.GetFlag() == true);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(EventUnsubscribe)
		{
			Foo foo(1, 10);
			Event<Foo> fooEvent(foo, false);
			BasicSubscriber subscriber;
			BasicSubscriber subscriber2;

			Event<Foo>::Subscribe(subscriber);
			Event<Foo>::Subscribe(subscriber2);

			Assert::IsTrue(subscriber.GetFlag() == false);
			Assert::IsTrue(subscriber2.GetFlag() == false);
			fooEvent.Deliver();
			Assert::IsTrue(subscriber.GetFlag() == true);
			Assert::IsTrue(subscriber2.GetFlag() == true);

			Event<Foo>::Unsubscribe(subscriber);
			subscriber.ResetFlag();
			subscriber2.ResetFlag();

			fooEvent.Deliver();

			Assert::IsTrue(subscriber.GetFlag() == false);
			Assert::IsTrue(subscriber2.GetFlag() == true);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(UnsubscribeAll)
		{
			Foo foo(1, 10);
			Event<Foo> fooEvent(foo, false);
			BasicSubscriber subscriber;
			BasicSubscriber subscriber2;

			Event<Foo>::Subscribe(subscriber);
			Event<Foo>::Subscribe(subscriber2);

			Assert::IsTrue(subscriber.GetFlag() == false);
			Assert::IsTrue(subscriber2.GetFlag() == false);
			fooEvent.Deliver();
			Assert::IsTrue(subscriber.GetFlag() == true);
			Assert::IsTrue(subscriber2.GetFlag() == true);

			subscriber.ResetFlag();
			subscriber2.ResetFlag();
			Event<Foo>::UnsubscribeAll();

			fooEvent.Deliver();

			Assert::IsTrue(subscriber.GetFlag() == false);
			Assert::IsTrue(subscriber2.GetFlag() == false);
		}

		TEST_METHOD(EventMessage)
		{
			Foo foo(1, 10);
			Event<Foo> fooEvent(foo, false);

			Assert::IsTrue(foo == fooEvent.Message());
			foo.SetData(3);
			Assert::IsTrue(foo != fooEvent.Message());
		}

		TEST_METHOD(EventSubscriberNotify)
		{
			Foo foo(1, 10);
			Event<Foo> fooEvent(foo, false);
			BasicSubscriber subscriber;
			BasicSubscriber subscriber2;

			Event<Foo>::Subscribe(subscriber);
			Event<Foo>::Subscribe(subscriber2);

			Assert::IsTrue(subscriber.GetFlag() == false);
			Assert::IsTrue(subscriber2.GetFlag() == false);
			fooEvent.Deliver();
			Assert::IsTrue(subscriber.GetFlag() == true);
			Assert::IsTrue(subscriber2.GetFlag() == true);

			subscriber.ResetFlag();
			subscriber2.ResetFlag();
			Event<Foo>::UnsubscribeAll();

			fooEvent.Deliver();

			Assert::IsTrue(subscriber.GetFlag() == false);
			Assert::IsTrue(subscriber2.GetFlag() == false);
		}

		TEST_METHOD(EventRTTI)
		{
			Event<Foo> fooEvent(Foo(1, 10), false);
			EventPublisher* publisher = &fooEvent;

			Assert::IsTrue(fooEvent.Is(EventPublisher::TypeIdClass()));
			Assert::IsTrue(fooEvent.Is(Event<Foo>::TypeIdClass()));
			Assert::IsTrue(!fooEvent.Is(Attributed::TypeIdClass()));
			Assert::IsTrue(fooEvent.Is("EventPublisher"));

			Assert::IsTrue(!fooEvent.Is("Beep"));
			Assert::IsTrue(fooEvent.TypeIdInstance() == Event<Foo>::TypeIdClass());
			Assert::IsTrue(Event<Foo>::TypeName() != "Beep");

			Assert::IsTrue(fooEvent.QueryInterface(EventPublisher::TypeIdClass()) != nullptr);
			Assert::IsTrue(fooEvent.QueryInterface(Event<Foo>::TypeIdClass()) != nullptr);
			Assert::IsTrue(fooEvent.QueryInterface(Attributed::TypeIdClass()) == nullptr);


			Assert::IsTrue(publisher->Is(EventPublisher::TypeIdClass()));
			Assert::IsTrue(publisher->Is(Event<Foo>::TypeIdClass()));
			Assert::IsTrue(!publisher->Is(Attributed::TypeIdClass()));
			Assert::IsTrue(publisher->Is("EventPublisher"));

			Assert::IsTrue(!publisher->Is("Beep"));
			Assert::IsTrue(publisher->TypeIdInstance() == Event<Foo>::TypeIdClass());
			Assert::IsTrue(Event<Foo>::TypeName() != "Beep");

			Assert::IsTrue(publisher->QueryInterface(EventPublisher::TypeIdClass()) != nullptr);
			Assert::IsTrue(publisher->QueryInterface(Event<Foo>::TypeIdClass()) != nullptr);
			Assert::IsTrue(publisher->QueryInterface(Attributed::TypeIdClass()) == nullptr);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EventTest::sStartMemState;
}
