#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			inline std::wstring ToString<HashMap<Foo, int, Foo::FooHashFunctor>::Iterator>(const HashMap<Foo, int, Foo::FooHashFunctor>::Iterator& it)
			{
				(it);
				return L"HashMap Iterator string!";
			}

			template<>
			inline std::wstring ToString<HashMap<Foo*, int, Foo::FooHashFunctor>::Iterator>(const HashMap<Foo*, int, Foo::FooHashFunctor>::Iterator& it)
			{
				(it);
				return L"HashMap Iterator string!";
			}

			template<>
			inline std::wstring ToString<HashMap<int, int>::Iterator>(const HashMap<int, int>::Iterator& it)
			{
				(it);
				return L"HashMap Iterator string!";
			}

			template<>
			inline std::wstring ToString<HashMap<int*, int>::Iterator>(const HashMap<int*, int>::Iterator& it)
			{
				(it);
				return L"HashMap Iterator string!";
			}

			template<>
			inline std::wstring ToString<HashMap<string, int>::Iterator>(const HashMap<string, int>::Iterator& it)
			{
				(it);
				return L"HashMap Iterator string!";
			}
		}
	}
}

namespace LibraryDesktopTest
{
	typedef Foo::FooHashFunctor FooHash;

	TEST_CLASS(HashMapTest)
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

#pragma region HashMapTestMethods

		TEST_METHOD(Constructor)
		{
			const std::uint32_t DEFAULT_CAPACITY = 13;

			// int test
			HashMap<int32_t, int> intMap;
			Assert::AreEqual(intMap.Size(), 0U);
			Assert::AreEqual(intMap.Capacity(), DEFAULT_CAPACITY);
			Assert::AreEqual(intMap.begin(), intMap.end());

			// intPointer test
			HashMap<int32_t*, int> intPointerMap;
			Assert::AreEqual(intPointerMap.Size(), 0U);
			Assert::AreEqual(intPointerMap.Capacity(), DEFAULT_CAPACITY);
			Assert::AreEqual(intPointerMap.begin(), intPointerMap.end());

			// string test
			HashMap<string, int> stringMap;
			Assert::AreEqual(stringMap.Size(), 0U);
			Assert::AreEqual(stringMap.Capacity(), DEFAULT_CAPACITY);
			Assert::AreEqual(stringMap.begin(), stringMap.end());

			// Foo test
			HashMap<Foo, int, FooHash> fooMap;
			Assert::AreEqual(fooMap.Size(), 0U);
			Assert::AreEqual(fooMap.Capacity(), DEFAULT_CAPACITY);
			Assert::AreEqual(fooMap.begin(), fooMap.end());

			// FooPointer test
			HashMap<Foo*, int, FooHash> fooPointerMap;
			Assert::AreEqual(fooPointerMap.Size(), 0U);
			Assert::AreEqual(fooPointerMap.Capacity(), DEFAULT_CAPACITY);
			Assert::AreEqual(fooPointerMap.begin(), fooPointerMap.end());
		}

		TEST_METHOD(CopySemantics)
		{
			int32_t int1 = 1;
			int32_t int2 = 2;
			string string1 = "one";
			string string2 = "two";
			Foo foo1(1, 2);
			Foo foo2(2, 3);
			int value1 = 10;
			int value2 = 20;

			// int tests
			HashMap<int32_t, int> intMap1;
			intMap1.Insert(pair<int32_t, int>(int1, value1));
			Assert::AreEqual(intMap1.Size(), 1U);
			HashMap<int32_t, int> intMap2(intMap1);
			Assert::AreEqual(intMap2[int1], value1);
			Assert::AreEqual(intMap2.Size(), 1U);
			intMap2[int2] = value2;
			Assert::AreNotEqual(intMap2[int2], intMap1[int2]);
			intMap1 = intMap2;
			Assert::AreEqual(intMap2[int2], intMap1[int2]);

			// intPointer tests
			HashMap<int32_t*, int> intPointerMap1;
			intPointerMap1.Insert(pair<int32_t*, int>(&int1, value1));
			Assert::AreEqual(intPointerMap1.Size(), 1U);
			HashMap<int32_t*, int> intPointerMap2(intPointerMap1);
			Assert::AreEqual(intPointerMap2[&int1], value1);
			Assert::AreEqual(intPointerMap2.Size(), 1U);
			intPointerMap2[&int2] = value2;
			Assert::AreNotEqual(intPointerMap2[&int2], intPointerMap1[&int2]);
			intPointerMap1 = intPointerMap2;
			Assert::AreEqual(intPointerMap2[&int2], intPointerMap1[&int2]);

			// string tests
			HashMap<string, int> stringMap1;
			stringMap1.Insert(pair<string, int>(string1, value1));
			Assert::AreEqual(stringMap1.Size(), 1U);
			HashMap<string, int> stringMap2(stringMap1);
			Assert::AreEqual(stringMap2[string1], value1);
			Assert::AreEqual(stringMap2.Size(), 1U);
			stringMap2[string2] = value2;
			Assert::AreNotEqual(stringMap2[string2], stringMap1[string2]);
			stringMap1 = stringMap2;
			Assert::AreEqual(stringMap2[string2], stringMap1[string2]);

			// Foo tests
			HashMap<Foo, int, FooHash> fooMap1;
			fooMap1.Insert(pair<Foo, int>(foo1, value1));
			Assert::AreEqual(fooMap1.Size(), 1U);
			HashMap<Foo, int, FooHash> fooMap2(fooMap1);
			Assert::AreEqual(fooMap2[foo1], value1);
			Assert::AreEqual(fooMap2.Size(), 1U);
			fooMap2[foo2] = value2;
			Assert::AreNotEqual(fooMap2[foo2], fooMap1[foo2]);
			fooMap1 = fooMap2;
			Assert::AreEqual(fooMap2[foo2], fooMap1[foo2]);

			// FooPointer tests
			HashMap<Foo*, int, FooHash> fooPointerMap1;
			fooPointerMap1.Insert(pair<Foo*, int>(&foo1, value1));
			Assert::AreEqual(fooPointerMap1.Size(), 1U);
			HashMap<Foo*, int, FooHash> fooPointerMap2(fooPointerMap1);
			Assert::AreEqual(fooPointerMap2[&foo1], value1);
			Assert::AreEqual(fooPointerMap2.Size(), 1U);
			fooPointerMap2[&foo2] = value2;
			Assert::AreNotEqual(fooPointerMap2[&foo2], fooPointerMap1[&foo2]);
			fooPointerMap1 = fooPointerMap2;
			Assert::AreEqual(fooPointerMap2[&foo2], fooPointerMap1[&foo2]);
		}

		TEST_METHOD(Find)
		{
			int32_t int1 = 1;
			int32_t int2 = 2;
			string string1 = "one";
			string string2 = "two";
			Foo foo1(1, 2);
			Foo foo2(2, 3);
			int value1 = 10;

			// int tests
			HashMap<int32_t, int> intMap1;
			Assert::AreEqual(intMap1.Find(int1), intMap1.end());
			intMap1[int1] = value1;
			intMap1[int2] = value1;
			Assert::AreEqual((*(intMap1.Find(int1))).first, int1);
			Assert::AreEqual((*(intMap1.Find(int1))).second, value1);

			// intPointer tests
			HashMap<int32_t*, int> intPointerMap1;
			Assert::AreEqual(intPointerMap1.Find(&int1), intPointerMap1.end());
			intPointerMap1[&int1] = value1;
			intPointerMap1[&int2] = value1;
			Assert::AreEqual((*(intPointerMap1.Find(&int1))).first, &int1);
			Assert::AreEqual((*(intPointerMap1.Find(&int1))).second, value1);

			// string tests
			HashMap<string, int> stringMap1;
			Assert::AreEqual(stringMap1.Find(string1), stringMap1.end());
			stringMap1[string1] = value1;
			stringMap1[string2] = value1;
			Assert::AreEqual((*(stringMap1.Find(string1))).first, string1);
			Assert::AreEqual((*(stringMap1.Find(string2))).second, value1);

			// Foo tests
			HashMap<Foo, int, FooHash> fooMap1;
			Assert::AreEqual(fooMap1.Find(foo1), fooMap1.end());
			fooMap1[foo1] = value1;
			fooMap1[foo2] = value1;
			Assert::AreEqual((*(fooMap1.Find(foo1))).first, foo1);
			Assert::AreEqual((*(fooMap1.Find(foo2))).second, value1);

			// FooPointer tests
			HashMap<Foo*, int, FooHash> fooPointerMap1;
			Assert::AreEqual(fooPointerMap1.Find(&foo1), fooPointerMap1.end());
			fooPointerMap1[&foo1] = value1;
			fooPointerMap1[&foo2] = value1;
			Assert::AreEqual(reinterpret_cast<void*>((*(fooPointerMap1.Find(&foo1))).first), reinterpret_cast<void*>(&foo1));
			Assert::AreEqual((*(fooPointerMap1.Find(&foo2))).second, value1);
		}

		TEST_METHOD(Insert)
		{
			int32_t int1 = 1;
			int32_t int2 = 2;
			string string1 = "one";
			string string2 = "two";
			Foo foo1(1, 2);
			Foo foo2(2, 3);
			int value1 = 10;
			int value2 = 20;

			// int tests
			HashMap<int32_t, int> intMap;
			Assert::AreEqual(intMap.Size(), 0U);
			intMap.Insert(pair<int32_t, int>(int1, value1));
			Assert::AreEqual(intMap.Size(), 1U);
			intMap.Insert(pair<int32_t, int>(int1, value2));
			Assert::AreEqual(intMap[int1], value1);
			Assert::AreEqual(intMap.Size(), 1U);
			intMap.Insert(pair<int32_t, int>(int2, value1));
			Assert::AreEqual(intMap[int2], value1);
			Assert::AreEqual(intMap.Size(), 2U);

			// int* tests
			HashMap<int32_t*, int> intPointerMap;
			Assert::AreEqual(intPointerMap.Size(), 0U);
			intPointerMap.Insert(pair<int32_t*, int>(&int1, value1));
			Assert::AreEqual(intPointerMap.Size(), 1U);
			intPointerMap.Insert(pair<int32_t*, int>(&int1, value2));
			Assert::AreEqual(intPointerMap[&int1], value1);
			Assert::AreEqual(intPointerMap.Size(), 1U);
			intPointerMap.Insert(pair<int32_t*, int>(&int2, value1));
			Assert::AreEqual(intPointerMap[&int2], value1);
			Assert::AreEqual(intPointerMap.Size(), 2U);

			// string tests
			HashMap<string, int> stringMap;
			Assert::AreEqual(stringMap.Size(), 0U);
			stringMap.Insert(pair<string, int>(string1, value1));
			Assert::AreEqual(stringMap.Size(), 1U);
			stringMap.Insert(pair<string, int>(string1, value2));
			Assert::AreEqual(stringMap[string1], value1);
			Assert::AreEqual(stringMap.Size(), 1U);
			stringMap.Insert(pair<string, int>(string2, value1));
			Assert::AreEqual(stringMap[string2], value1);
			Assert::AreEqual(stringMap.Size(), 2U);

			// Foo tests
			HashMap<Foo, int, FooHash> fooMap;
			Assert::AreEqual(fooMap.Size(), 0U);
			fooMap.Insert(pair<Foo, int>(foo1, value1));
			Assert::AreEqual(fooMap.Size(), 1U);
			fooMap.Insert(pair<Foo, int>(foo1, value2));
			Assert::AreEqual(fooMap[foo1], value1);
			Assert::AreEqual(fooMap.Size(), 1U);
			fooMap.Insert(pair<Foo, int>(foo2, value1));
			Assert::AreEqual(fooMap[foo2], value1);
			Assert::AreEqual(fooMap.Size(), 2U);

			// Foo* tests
			HashMap<Foo*, int, FooHash> fooPointerMap;
			Assert::AreEqual(fooPointerMap.Size(), 0U);
			fooPointerMap.Insert(pair<Foo*, int>(&foo1, value1));
			Assert::AreEqual(fooPointerMap.Size(), 1U);
			fooPointerMap.Insert(pair<Foo*, int>(&foo1, value2));
			Assert::AreEqual(fooPointerMap[&foo1], value1);
			Assert::AreEqual(fooPointerMap.Size(), 1U);
			fooPointerMap.Insert(pair<Foo*, int>(&foo2, value1));
			Assert::AreEqual(fooPointerMap[&foo2], value1);
			Assert::AreEqual(fooPointerMap.Size(), 2U);
		}

		TEST_METHOD(SubscriptOperator)
		{
			int32_t int1 = 1;
			int32_t int2 = 2;
			string string1 = "one";
			string string2 = "two";
			Foo foo1(1, 2);
			Foo foo2(2, 3);
			int value1 = 10;
			int value2 = 20;

			// int tests
			HashMap<int32_t, int> intMap;
			intMap[int1] = value1;
			Assert::AreEqual(intMap.Size(), 1U);
			try { intMap.At(int2); Assert::Fail(); } catch (std::exception) {};
			intMap[int2] = value2;
			Assert::AreEqual(intMap.Size(), 2U);
			intMap[int1] = value2;
			Assert::AreEqual(intMap[int1], intMap[int2]);
			const_cast<const HashMap<int32_t, int>*>(&intMap)->operator[](int1);
			const_cast<const HashMap<int32_t, int>*>(&intMap)->At(int1);

			// int* tests
			HashMap<int32_t*, int> intPointerMap;
			intPointerMap[&int1] = value1;
			Assert::AreEqual(intPointerMap.Size(), 1U);
			try { intPointerMap.At(&int2); Assert::Fail(); }
			catch (std::exception) {};
			intPointerMap[&int2] = value2;
			Assert::AreEqual(intPointerMap.Size(), 2U);
			intPointerMap[&int1] = value2;
			Assert::AreEqual(intPointerMap[&int1], intPointerMap[&int2]);
			const_cast<const HashMap<int32_t*, int>*>(&intPointerMap)->operator[](&int1);
			const_cast<const HashMap<int32_t*, int>*>(&intPointerMap)->At(&int1);
			
			// string tests
			HashMap<string, int> stringMap;
			stringMap[string1] = value1;
			Assert::AreEqual(stringMap.Size(), 1U);
			try { stringMap.At(string2); Assert::Fail(); }
			catch (std::exception) {};
			stringMap[string2] = value2;
			Assert::AreEqual(stringMap.Size(), 2U);
			stringMap[string1] = value2;
			Assert::AreEqual(stringMap[string1], stringMap[string2]);
			const_cast<const HashMap<string, int>*>(&stringMap)->operator[](string1);
			const_cast<const HashMap<string, int>*>(&stringMap)->At(string1);

			// Foo tests
			HashMap<Foo, int, FooHash> fooMap;
			fooMap[foo1] = value1;
			Assert::AreEqual(fooMap.Size(), 1U);
			try { fooMap.At(foo2); Assert::Fail(); }
			catch (std::exception) {};
			fooMap[foo2] = value2;
			Assert::AreEqual(fooMap.Size(), 2U);
			fooMap[foo1] = value2;
			Assert::AreEqual(fooMap[foo1], fooMap[foo2]);
			const_cast<const HashMap<Foo, int, FooHash>*>(&fooMap)->operator[](foo1);
			const_cast<const HashMap<Foo, int, FooHash>*>(&fooMap)->At(foo1);

			// Foo* tests
			HashMap<Foo*, int, FooHash> fooPointerMap;
			fooPointerMap[&foo1] = value1;
			Assert::AreEqual(fooPointerMap.Size(), 1U);
			try { fooPointerMap.At(&foo2); Assert::Fail(); }
			catch (std::exception) {};
			fooPointerMap[&foo2] = value2;
			Assert::AreEqual(fooPointerMap.Size(), 2U);
			fooPointerMap[&foo1] = value2;
			Assert::AreEqual(fooPointerMap[&foo1], fooPointerMap[&foo2]);
			const_cast<const HashMap<Foo*, int, FooHash>*>(&fooPointerMap)->operator[](&foo1);
			const_cast<const HashMap<Foo*, int, FooHash>*>(&fooPointerMap)->At(&foo1);
		}

		TEST_METHOD(Remove)
		{
			int32_t int1 = 1;
			int32_t int2 = 2;
			int32_t int3 = 3;
			string string1 = "one";
			string string2 = "two";
			string string3 = "three";
			Foo foo1(1, 2);
			Foo foo2(2, 3);
			Foo foo3(3, 4);
			int value1 = 10;
			int value2 = 20;
			int value3 = 30;

			// int tests
			HashMap<int32_t, int> intMap;
			intMap[int1] = value1;
			intMap[int2] = value2;
			intMap[int3] = value3;
			Assert::AreEqual(intMap.Size(), 3U);
			intMap.Remove(int2);
			Assert::AreEqual(intMap.Size(), 2U);
			Assert::AreEqual(intMap[int1], value1);
			Assert::AreEqual(intMap[int3], value3);
			intMap.Remove(int2);
			Assert::AreEqual(intMap.Size(), 2U);
			intMap.Remove(int1);
			intMap.Remove(int3);
			Assert::AreEqual(intMap.Size(), 0U);
			intMap.Remove(int1);

			// int* tests
			HashMap<int32_t*, int> intPointerMap;
			intPointerMap[&int1] = value1;
			intPointerMap[&int2] = value2;
			intPointerMap[&int3] = value3;
			Assert::AreEqual(intPointerMap.Size(), 3U);
			intPointerMap.Remove(&int2);
			Assert::AreEqual(intPointerMap.Size(), 2U);
			Assert::AreEqual(intPointerMap[&int1], value1);
			Assert::AreEqual(intPointerMap[&int3], value3);
			intPointerMap.Remove(&int2);
			Assert::AreEqual(intPointerMap.Size(), 2U);
			intPointerMap.Remove(&int1);
			intPointerMap.Remove(&int3);
			Assert::AreEqual(intPointerMap.Size(), 0U);
			intPointerMap.Remove(&int1);

			// string tests
			HashMap<string, int> stringMap;
			stringMap[string1] = value1;
			stringMap[string2] = value2;
			stringMap[string3] = value3;
			Assert::AreEqual(stringMap.Size(), 3U);
			stringMap.Remove(string2);
			Assert::AreEqual(stringMap.Size(), 2U);
			Assert::AreEqual(stringMap[string1], value1);
			Assert::AreEqual(stringMap[string3], value3);
			stringMap.Remove(string2);
			Assert::AreEqual(stringMap.Size(), 2U);
			stringMap.Remove(string1);
			stringMap.Remove(string3);
			Assert::AreEqual(stringMap.Size(), 0U);
			stringMap.Remove(string1);

			// Foo tests
			HashMap<Foo, int, FooHash> fooMap;
			fooMap[foo1] = value1;
			fooMap[foo2] = value2;
			fooMap[foo3] = value3;
			Assert::AreEqual(fooMap.Size(), 3U);
			fooMap.Remove(foo2);
			Assert::AreEqual(fooMap.Size(), 2U);
			Assert::AreEqual(fooMap[foo1], value1);
			Assert::AreEqual(fooMap[foo3], value3);
			fooMap.Remove(foo2);
			Assert::AreEqual(fooMap.Size(), 2U);
			fooMap.Remove(foo1);
			fooMap.Remove(foo3);
			Assert::AreEqual(fooMap.Size(), 0U);
			fooMap.Remove(foo1);

			// Foo* tests
			HashMap<Foo*, int, FooHash> fooPointerMap;
			fooPointerMap[&foo1] = value1;
			fooPointerMap[&foo2] = value2;
			fooPointerMap[&foo3] = value3;
			Assert::AreEqual(fooPointerMap.Size(), 3U);
			fooPointerMap.Remove(&foo2);
			Assert::AreEqual(fooPointerMap.Size(), 2U);
			Assert::AreEqual(fooPointerMap[&foo1], value1);
			Assert::AreEqual(fooPointerMap[&foo3], value3);
			fooPointerMap.Remove(&foo2);
			Assert::AreEqual(fooPointerMap.Size(), 2U);
			fooPointerMap.Remove(&foo1);
			fooPointerMap.Remove(&foo3);
			Assert::AreEqual(fooPointerMap.Size(), 0U);
			fooPointerMap.Remove(&foo1);
		}

		TEST_METHOD(Clear)
		{
			int32_t int1 = 1;
			int32_t int2 = 2;
			string string1 = "one";
			string string2 = "two";
			Foo foo1(1, 2);
			Foo foo2(2, 3);
			int value1 = 10;
			int value2 = 20;

			// int tests
			HashMap<int32_t, int> intMap;
			intMap.Clear();
			Assert::AreEqual(intMap.Size(), 0U);
			intMap[int1] = value1;
			intMap[int2] = value2;
			Assert::AreEqual(intMap.Size(), 2U);
			intMap.Clear();
			Assert::AreEqual(intMap.Size(), 0U);

			// int* tests
			HashMap<int32_t*, int> intPointerMap;
			intPointerMap.Clear();
			Assert::AreEqual(intPointerMap.Size(), 0U);
			intPointerMap[&int1] = value1;
			intPointerMap[&int2] = value2;
			Assert::AreEqual(intPointerMap.Size(), 2U);
			intPointerMap.Clear();
			Assert::AreEqual(intPointerMap.Size(), 0U);

			// string tests
			HashMap<string, int> stringMap;
			stringMap.Clear();
			Assert::AreEqual(stringMap.Size(), 0U);
			stringMap[string1] = value1;
			stringMap[string2] = value2;
			Assert::AreEqual(stringMap.Size(), 2U);
			stringMap.Clear();
			Assert::AreEqual(stringMap.Size(), 0U);

			// Foo tests
			HashMap<Foo, int, FooHash> fooHash;
			fooHash.Clear();
			Assert::AreEqual(fooHash.Size(), 0U);
			fooHash[foo1] = value1;
			fooHash[foo2] = value2;
			Assert::AreEqual(fooHash.Size(), 2U);
			fooHash.Clear();
			Assert::AreEqual(fooHash.Size(), 0U);

			// Foo* tests
			HashMap<Foo*, int, FooHash> fooPointerHash;
			fooPointerHash.Clear();
			Assert::AreEqual(fooPointerHash.Size(), 0U);
			fooPointerHash[&foo1] = value1;
			fooPointerHash[&foo2] = value2;
			Assert::AreEqual(fooPointerHash.Size(), 2U);
			fooPointerHash.Clear();
			Assert::AreEqual(fooPointerHash.Size(), 0U);
		}

		TEST_METHOD(Size)
		{
			int32_t int1 = 1;
			int32_t int2 = 2;
			string string1 = "one";
			string string2 = "two";
			Foo foo1(1, 2);
			Foo foo2(2, 3);
			int value1 = 10;
			int value2 = 20;

			// int tests
			HashMap<int32_t, int> intMap;
			intMap.Clear();
			Assert::AreEqual(intMap.Size(), 0U);
			intMap[int1] = value1;
			intMap[int2] = value2;
			Assert::AreEqual(intMap.Size(), 2U);
			intMap[int1] = value2;
			Assert::AreEqual(intMap.Size(), 2U);
			intMap.Clear();
			Assert::AreEqual(intMap.Size(), 0U);

			// int* tests
			HashMap<int32_t*, int> intPointerMap;
			intPointerMap.Clear();
			Assert::AreEqual(intPointerMap.Size(), 0U);
			intPointerMap[&int1] = value1;
			intPointerMap[&int2] = value2;
			Assert::AreEqual(intPointerMap.Size(), 2U);
			intPointerMap[&int1] = value2;
			Assert::AreEqual(intPointerMap.Size(), 2U);
			intPointerMap.Clear();
			Assert::AreEqual(intPointerMap.Size(), 0U);

			// string tests
			HashMap<string, int> stringMap;
			stringMap.Clear();
			Assert::AreEqual(stringMap.Size(), 0U);
			stringMap[string1] = value1;
			stringMap[string2] = value2;
			Assert::AreEqual(stringMap.Size(), 2U);
			stringMap[string1] = value2;
			Assert::AreEqual(stringMap.Size(), 2U);
			stringMap.Clear();
			Assert::AreEqual(stringMap.Size(), 0U);

			// Foo tests
			HashMap<Foo, int, FooHash> fooMap;
			fooMap.Clear();
			Assert::AreEqual(fooMap.Size(), 0U);
			fooMap[foo1] = value1;
			fooMap[foo2] = value2;
			Assert::AreEqual(fooMap.Size(), 2U);
			fooMap[foo1] = value2;
			Assert::AreEqual(fooMap.Size(), 2U);
			fooMap.Clear();
			Assert::AreEqual(fooMap.Size(), 0U);

			// Foo* tests
			HashMap<Foo*, int, FooHash> fooPointerMap;
			fooPointerMap.Clear();
			Assert::AreEqual(fooPointerMap.Size(), 0U);
			fooPointerMap[&foo1] = value1;
			fooPointerMap[&foo2] = value2;
			Assert::AreEqual(fooPointerMap.Size(), 2U);
			fooPointerMap[&foo1] = value2;
			Assert::AreEqual(fooPointerMap.Size(), 2U);
			fooPointerMap.Clear();
			Assert::AreEqual(fooPointerMap.Size(), 0U);
		}

		TEST_METHOD(ContainsKey)
		{
			int32_t int1 = 1;
			int32_t int2 = 2;
			string string1 = "one";
			string string2 = "two";
			Foo foo1(1, 2);
			Foo foo2(2, 3);
			int value1 = 10;

			// int test
			HashMap<int32_t, int> intMap;
			Assert::IsFalse(intMap.ContainsKey(int1));
			intMap[int1] = value1;
			Assert::IsTrue(intMap.ContainsKey(int1));
			Assert::IsFalse(intMap.ContainsKey(int2));
			intMap.Remove(int1);
			Assert::IsFalse(intMap.ContainsKey(int1));

			// int* test
			HashMap<int32_t*, int> intPointerMap;
			Assert::IsFalse(intPointerMap.ContainsKey(&int1));
			intPointerMap[&int1] = value1;
			Assert::IsTrue(intPointerMap.ContainsKey(&int1));
			Assert::IsFalse(intPointerMap.ContainsKey(&int2));
			intPointerMap.Remove(&int1);
			Assert::IsFalse(intPointerMap.ContainsKey(&int1));

			// string test
			HashMap<string, int> stringMap;
			Assert::IsFalse(stringMap.ContainsKey(string1));
			stringMap[string1] = value1;
			Assert::IsTrue(stringMap.ContainsKey(string1));
			Assert::IsFalse(stringMap.ContainsKey(string2));
			stringMap.Remove(string1);
			Assert::IsFalse(stringMap.ContainsKey(string1));

			// Foo test
			HashMap<Foo, int, FooHash> fooMap;
			Assert::IsFalse(fooMap.ContainsKey(foo1));
			fooMap[foo1] = value1;
			Assert::IsTrue(fooMap.ContainsKey(foo1));
			Assert::IsFalse(fooMap.ContainsKey(foo2));
			fooMap.Remove(foo1);
			Assert::IsFalse(fooMap.ContainsKey(foo1));

			// Foo* test
			HashMap<Foo*, int, FooHash> fooPointerMap;
			Assert::IsFalse(fooPointerMap.ContainsKey(&foo1));
			fooPointerMap[&foo1] = value1;
			Assert::IsTrue(fooPointerMap.ContainsKey(&foo1));
			Assert::IsFalse(fooPointerMap.ContainsKey(&foo2));
			fooPointerMap.Remove(&foo1);
			Assert::IsFalse(fooPointerMap.ContainsKey(&foo1));
		}

		TEST_METHOD(beginEnd)
		{
			int32_t int1 = 1;
			int32_t int2 = 2;
			string string1 = "one";
			string string2 = "two";
			Foo foo1(1, 2);
			Foo foo2(2, 3);
			int value1 = 10;
			int value2 = 20;

			// int test
			{
				HashMap<int32_t, int> map;
				Assert::AreEqual(map.begin(), map.end());
				map[int1] = value1;
				Assert::AreNotEqual(map.begin(), map.end());
				map[int2] = value2;
				uint32_t count = 0;
				for (auto it = map.begin(); it != map.end(); ++it)
				{
					count++;
				}
				Assert::AreEqual(count, map.Size());
			}

			// int* test
			{
				HashMap<int32_t*, int> map;
				Assert::AreEqual(map.begin(), map.end());
				map[&int1] = value1;
				Assert::AreNotEqual(map.begin(), map.end());
				map[&int2] = value2;
				uint32_t count = 0;
				for (auto it = map.begin(); it != map.end(); ++it)
				{
					count++;
				}
				Assert::AreEqual(count, map.Size());
			}

			// string test
			{
				HashMap<string, int> map;
				Assert::AreEqual(map.begin(), map.end());
				map[string1] = value1;
				Assert::AreNotEqual(map.begin(), map.end());
				map[string2] = value2;
				uint32_t count = 0;
				for (auto it = map.begin(); it != map.end(); ++it)
				{
					count++;
				}
				Assert::AreEqual(count, map.Size());
			}

			// Foo test
			{
				HashMap<Foo, int, FooHash> map;
				Assert::AreEqual(map.begin(), map.end());
				map[foo1] = value1;
				Assert::AreNotEqual(map.begin(), map.end());
				map[foo2] = value2;
				uint32_t count = 0;
				for (auto it = map.begin(); it != map.end(); ++it)
				{
					count++;
				}
				Assert::AreEqual(count, map.Size());
			}

			// Foo* test
			{
				HashMap<Foo*, int, FooHash> map;
				Assert::AreEqual(map.begin(), map.end());
				map[&foo1] = value1;
				Assert::AreNotEqual(map.begin(), map.end());
				map[&foo2] = value2;
				uint32_t count = 0;
				for (auto it = map.begin(); it != map.end(); ++it)
				{
					count++;
				}
				Assert::AreEqual(count, map.Size());
			}
		}

		TEST_METHOD(HighVolume)
		{
			const std::uint32_t COUNT = 1000;
			const std::uint32_t CAPACITY = 20;

			// int test
			{
				HashMap<std::uint32_t, int> map;

				for (std::uint32_t i = 0; i < COUNT; i++)
				{
					map[i] = i % 7;
				}

				Assert::AreEqual(map.Size(), COUNT);
			}
		}

		TEST_METHOD(SpecializationTest)
		{
			// Assures that two int pointers/ foo pointers that point to equivalent 
			// data are hashed to the same value.
			string string1 = "Beep";
			string string2(string1);
			int value1 = 10;
			int value2 = 20;

			HashMap<string, int> stringMap1;
			stringMap1[string1] = value1;
			stringMap1[string2] = value2;

			// operator[] does not create a new element in map,
			// so therefore, subscripting string2 will get the same 
			// element as string1, and now its value is value2.
			Assert::AreEqual(stringMap1[string1], value2);
			Assert::AreEqual(stringMap1[string2], value2);
			Assert::AreEqual(stringMap1.Size(), 1U);
		}

#pragma endregion

#pragma region IteratorTestMethods

		TEST_METHOD(IteratorConstructor)
		{
			// int test
			{
				HashMap<int32_t, int> map;
				auto it = HashMap<int32_t, int>::Iterator();
				try { *it; Assert::Fail(); } catch (std::exception) { };
				try { it++; Assert::Fail(); } catch (std::exception) { };
				it = map.begin();
				it++;
			}

			// int* test
			{
				HashMap<int32_t*, int> map;
				auto it = HashMap<int32_t*, int>::Iterator();
				try { *it; Assert::Fail(); }
				catch (std::exception) {};
				try { it++; Assert::Fail(); }
				catch (std::exception) {};
				it = map.begin();
				it++;
			}

			// string test
			{
				HashMap<string, int> map;
				auto it = HashMap<string, int>::Iterator();
				try { *it; Assert::Fail(); }
				catch (std::exception) {};
				try { it++; Assert::Fail(); }
				catch (std::exception) {};
				it = map.begin();
				it++;
			}

			// Foo test
			{
				HashMap<Foo, int, FooHash> map;
				auto it = HashMap<Foo, int, FooHash>::Iterator();
				try { *it; Assert::Fail(); }
				catch (std::exception) {};
				try { it++; Assert::Fail(); }
				catch (std::exception) {};
				it = map.begin();
				it++;
			}

			// Foo* test
			{
				HashMap<Foo*, int, FooHash> map;
				auto it = HashMap<Foo*, int, FooHash>::Iterator();
				try { *it; Assert::Fail(); }
				catch (std::exception) {};
				try { it++; Assert::Fail(); }
				catch (std::exception) {};
				it = map.begin();
				it++;
			}
		}

		TEST_METHOD(IteratorIncrement)
		{
			int32_t int1 = 1;
			int32_t int2 = 2;
			string string1 = "one";
			string string2 = "two";
			Foo foo1(1, 2);
			Foo foo2(2, 3);
			int value1 = 10;
			int value2 = 20;

			// int test
			{
				HashMap<int32_t, int> map;
				Assert::AreEqual(map.begin(), map.end());
				map[int1] = value1;
				Assert::AreNotEqual(map.begin(), map.end());
				map[int2] = value2;
				auto it = map.begin();
				auto prevIt= it++;
				Assert::AreNotEqual((*prevIt).first, (*(it)).first);
				Assert::AreEqual(++it, map.end());
			}

			// int* test
			{
				HashMap<int32_t*, int> map;
				Assert::AreEqual(map.begin(), map.end());
				map[&int1] = value1;
				Assert::AreNotEqual(map.begin(), map.end());
				map[&int2] = value2;
				auto it = map.begin();
				auto prevIt = it++;
				Assert::AreNotEqual((*prevIt).first, (*(it)).first);
				Assert::AreEqual(++it, map.end());
			}

			// string test
			{
				HashMap<string, int> map;
				Assert::AreEqual(map.begin(), map.end());
				map[string1] = value1;
				Assert::AreNotEqual(map.begin(), map.end());
				map[string2] = value2;
				auto it = map.begin();
				auto prevIt = it++;
				Assert::AreNotEqual((*prevIt).first, (*(it)).first);
				Assert::AreEqual(++it, map.end());
			}

			// Foo test
			{
				HashMap<Foo, int, FooHash> map;
				Assert::AreEqual(map.begin(), map.end());
				map[foo1] = value1;
				Assert::AreNotEqual(map.begin(), map.end());
				map[foo2] = value2;
				auto it = map.begin();
				auto prevIt = it++;
				Assert::AreNotEqual((*prevIt).first, (*(it)).first);
				Assert::AreEqual(++it, map.end());
			}

			// Foo* test
			{
				HashMap<Foo*, int, FooHash> map;
				Assert::AreEqual(map.begin(), map.end());
				map[&foo1] = value1;
				Assert::AreNotEqual(map.begin(), map.end());
				map[&foo2] = value2;
				auto it = map.begin();
				auto prevIt = it++;
				Assert::AreNotEqual(reinterpret_cast<void*>((*prevIt).first), reinterpret_cast<void*>((*(it)).first));
				Assert::AreEqual(++it, map.end());
			}
		}

		TEST_METHOD(IteratorDereference)
		{
			int32_t int1 = 1;
			string string1 = "one";
			Foo foo1(1, 2);
			int value1 = 10;

			// int test
			{
				HashMap<int32_t, int> map;
				auto it = HashMap<int32_t, int>::Iterator();
				try { *it; Assert::Fail();} catch (std::exception) { }
				it = map.begin();
				try { *it; Assert::Fail();} catch (std::exception) { }
				map[int1] = value1;
				it = map.begin();
				Assert::AreEqual((*it).first, int1);
			}

			// pointer test
			{
				HashMap<int32_t*, int> map;
				auto it = HashMap<int32_t*, int>::Iterator();
				try { *it; Assert::Fail(); }
				catch (std::exception) {}
				it = map.begin();
				try { *it; Assert::Fail(); }
				catch (std::exception) {}
				map[&int1] = value1;
				it = map.begin();
				Assert::AreEqual((*it).first, &int1);
			}

			// string test
			{
				HashMap<string, int> map;
				auto it = HashMap<string, int>::Iterator();
				try { *it; Assert::Fail(); }
				catch (std::exception) {}
				it = map.begin();
				try { *it; Assert::Fail(); }
				catch (std::exception) {}
				map[string1] = value1;
				it = map.begin();
				Assert::AreEqual((*it).first, string1);
			}

			// Foo test
			{
				HashMap<Foo, int, FooHash> map;
				auto it = HashMap<Foo, int, FooHash>::Iterator();
				try { *it; Assert::Fail(); }
				catch (std::exception) {}
				it = map.begin();
				try { *it; Assert::Fail(); }
				catch (std::exception) {}
				map[foo1] = value1;
				it = map.begin();
				Assert::AreEqual((*it).first, foo1);
			}

			// Foo* test
			{
				HashMap<Foo*, int, FooHash> map;
				auto it = HashMap<Foo*, int, FooHash>::Iterator();
				try { *it; Assert::Fail(); }
				catch (std::exception) {}
				it = map.begin();
				try { *it; Assert::Fail(); }
				catch (std::exception) {}
				map[&foo1] = value1;
				it = map.begin();
				Assert::AreEqual(reinterpret_cast<void*>((*it).first), reinterpret_cast<void*>(&foo1));
			}
		}

		TEST_METHOD(IteratorComparison)
		{
			int32_t int1 = 1;
			string string1 = "one";
			Foo foo1(1, 2);
			int value1 = 10;

			// int test
			{
				HashMap<int32_t, int> map;
				auto it1 = map.begin();
				auto it2 = HashMap<int32_t, int>::Iterator();
				Assert::AreNotEqual(it1, it2);
				map[int1] = value1;
				it1 = map.begin();
				it2 = it1;
				Assert::AreEqual(it1, it2);
				it1++;
				Assert::AreNotEqual(it1, it2);
			}

			// int* test
			{
				HashMap<int32_t*, int> map;
				auto it1 = map.begin();
				auto it2 = HashMap<int32_t*, int>::Iterator();
				Assert::AreNotEqual(it1, it2);
				map[&int1] = value1;
				it1 = map.begin();
				it2 = it1;
				Assert::AreEqual(it1, it2);
				it1++;
				Assert::AreNotEqual(it1, it2);
			}

			// string test
			{
				HashMap<string, int> map;
				auto it1 = map.begin();
				auto it2 = HashMap<string, int>::Iterator();
				Assert::AreNotEqual(it1, it2);
				map[string1] = value1;
				it1 = map.begin();
				it2 = it1;
				Assert::AreEqual(it1, it2);
				it1++;
				Assert::AreNotEqual(it1, it2);
			}

			// Foo test
			{
				HashMap<Foo, int, FooHash> map;
				auto it1 = map.begin();
				auto it2 = HashMap<Foo, int, FooHash>::Iterator();
				Assert::AreNotEqual(it1, it2);
				map[foo1] = value1;
				it1 = map.begin();
				it2 = it1;
				Assert::AreEqual(it1, it2);
				it1++;
				Assert::AreNotEqual(it1, it2);
			}
		}

#pragma endregion

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState HashMapTest::sStartMemState;
}
