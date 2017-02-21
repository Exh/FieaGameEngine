#include "pch.h"

#define KEY_INT1 "int1"
#define KEY_INT2 " int2"
#define KEY_FLOAT1 "float1"
#define KEY_STRING1 "string1"
#define KEY_CHILD1 "child1"
#define KEY_CHILD2 "child2"

#define CREATE_TEST_VARS int32_t int1 = 10; \
int32_t int2 = 20; \
int32_t int3 = 30; \
float float1 = 1.0f; \
float float2 = 2.0f; \
float float3 = 3.0f; \
glm::vec4 vector1 = glm::vec4(10.0f, 11.0f, 12.0f, 13.0f); \
glm::vec4 vector2 = glm::vec4(20.0f, 21.0f, 22.0f, 23.0f); \
glm::vec4 vector3 = glm::vec4(30.0f, 31.0f, 32.0f, 33.0f); \
glm::mat4 matrix1 = glm::translate(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f)); \
glm::mat4 matrix2 = glm::translate(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f)); \
glm::mat4 matrix3 = glm::translate(glm::mat4(), glm::vec3(3.0f, 3.0f, 3.0f)); \
string string1 = "one"; \
string string2 = "two"; \
string string3 = "three"; \
Foo foo1(1, 2); \
Foo foo2(2, 3); \
Foo foo3(3, 4); \
RTTI* pointer1 = &foo1; \
RTTI* pointer2 = &foo2; \
RTTI* pointer3 = &foo3; \
Scope scope1; \
const Scope* constScope1 = &scope1; \
int1; \
int2; \
int3; \
float1; \
float2; \
float3; \
vector1; \
vector2; \
vector3; \
matrix1; \
matrix2; \
matrix3; \
string1; \
string2; \
string3; \
foo1; \
foo2; \
foo3; \
pointer1; \
pointer2; \
pointer3; \
scope1; \
constScope1;

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
			inline std::wstring ToString<DatumType>(const DatumType& type)
			{
				(type);
				return L"DatumType testing ToString.";
			}

			template<>
			inline std::wstring ToString<Datum>(const Datum& type)
			{
				(type);
				return L"Datum testing ToString.";
			}

			template<>
			inline std::wstring ToString<glm::vec4>(const glm::vec4& type)
			{
				(type);
				return L"Vec4 testing ToString.";
			}

			template<>
			inline std::wstring ToString<glm::mat4>(const glm::mat4& type)
			{
				(type);
				return L"Mat4 testing ToString.";
			}

			template<>
			inline std::wstring ToString<RTTI>(RTTI* type)
			{
				(type);
				return L"Pointer testing ToString.";
			}

			template<>
			inline std::wstring ToString<RTTI>(const RTTI& type)
			{
				(type);
				return L"Pointer testing ToString.";
			}

			template<>
			inline std::wstring ToString<Foo>(const Foo* type)
			{
				(type);
				return L"Pointer testing ToString.";
			}

			template<>
			inline std::wstring ToString<Scope>(const Scope& type)
			{
				(type);
				return L"Scope testing ToString.";
			}

			template<>
			inline std::wstring ToString<Scope>(const Scope* type)
			{
				(type);
				return L"Scope testing ToString.";
			}

			template<>
			inline std::wstring ToString<Datum>(const Datum* type)
			{
				(type);
				return L"Datum testing ToString.";
			}
		}
	}
}

namespace LibraryDesktopTest
{
	TEST_CLASS(ScopeTest)
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

#pragma region ScopeTestMethods

		TEST_METHOD(Constructor)
		{
			Scope* scope = new Scope();
			Scope* scope2 = new Scope(30);

			delete scope2;
			delete scope;
		}

		TEST_METHOD(CopySemantics)
		{
			CREATE_TEST_VARS
			Scope scope2;

			scope1.Append(KEY_INT1) = int1;
			scope1.Append(KEY_FLOAT1) = float1;
			Scope& scopeChild1 = scope1.AppendScope("scopeChild1");
			scopeChild1.Append("child1_int1") = int1;

			scope2 = scope1;
			Assert::AreEqual(scope1, scope2);

			Scope scope3(scope1);
			Assert::AreEqual(scope3, scope2);
			Assert::AreEqual(scope3, scope1);
		}

		TEST_METHOD(Find)
		{
			CREATE_TEST_VARS
			Assert::IsTrue(scope1.Find(KEY_INT1) == nullptr);
			Assert::IsTrue(constScope1->Find(KEY_INT1) == nullptr);
			scope1.Append(KEY_INT1) = int1;
			scope1.Append(KEY_FLOAT1) = float1;
			Assert::IsTrue(scope1.Find(KEY_INT1) != nullptr);
			Assert::IsTrue(scope1.Find(KEY_FLOAT1) != nullptr);
			Assert::IsTrue(scope1.Find(KEY_STRING1) == nullptr);
			Assert::IsTrue(constScope1->Find(KEY_INT1) != nullptr);

			Scope& scope2 = scope1.AppendScope(KEY_CHILD1);
			scope2.Append(KEY_STRING1) = string1;

			Assert::IsTrue(scope2.Find(KEY_INT1) == nullptr);
			Assert::IsTrue(scope2.Find(KEY_FLOAT1) == nullptr);
			Assert::IsTrue(scope2.Find(KEY_STRING1) != nullptr);

			Assert::IsTrue(scope1.Find(KEY_INT1) != nullptr);
			Assert::IsTrue(scope1.Find(KEY_FLOAT1) != nullptr);
			Assert::IsTrue(scope1.Find(KEY_STRING1) == nullptr);
		}

		TEST_METHOD(Search)
		{
			CREATE_TEST_VARS
			Scope* containingScope = nullptr;
			Datum* foundDatum = nullptr;

			foundDatum = scope1.Search(KEY_INT1, &containingScope);
			Assert::IsTrue(foundDatum == nullptr);
			Assert::IsTrue(containingScope == nullptr);

			Datum& intDatum = scope1.Append(KEY_INT1);
			intDatum = int1;
			Datum& floatDatum = scope1.Append(KEY_FLOAT1);
			floatDatum = float1;
			foundDatum = scope1.Search(KEY_INT1, &containingScope);
			Assert::IsTrue(containingScope == &scope1);
			Assert::IsTrue(foundDatum == &intDatum);

			foundDatum = scope1.Search(KEY_FLOAT1, &containingScope);
			Assert::IsTrue(foundDatum == &floatDatum);
			Assert::IsTrue(scope1.Search(KEY_STRING1) == nullptr);

			Scope& scope2 = scope1.AppendScope(KEY_CHILD1);
			Datum& stringDatum = scope2.Append(KEY_STRING1);
			stringDatum = string1;
			foundDatum = scope1.Search(KEY_STRING1, &containingScope);
			Assert::IsTrue(foundDatum == nullptr);
			Assert::IsTrue(containingScope == nullptr);
			foundDatum = scope2.Search(KEY_STRING1, &containingScope);
			Assert::IsTrue(foundDatum == &stringDatum);
			Assert::IsTrue(containingScope == &scope2);
			foundDatum = scope2.Search(KEY_INT1, &containingScope);
			Assert::IsTrue(foundDatum == &intDatum);
			Assert::IsTrue(containingScope == &scope1);
			foundDatum = scope2.Search(KEY_FLOAT1, &containingScope);
			Assert::IsTrue(foundDatum == &floatDatum);
			Assert::IsTrue(containingScope == &scope1);

			// Const version
			Assert::IsTrue(constScope1->Search(KEY_INT1) != nullptr);
		}

		TEST_METHOD(Append)
		{
			CREATE_TEST_VARS

			Datum& intDatum = scope1.Append(KEY_INT1);
			intDatum = int1;
			Assert::IsTrue(&scope1.Append(KEY_INT1) == &intDatum);

			Assert::IsTrue(&scope1[KEY_INT1] == &intDatum);
			Assert::IsTrue(scope1[KEY_INT1] == int1);

			Datum& floatDatum = scope1.Append(KEY_FLOAT1);
			Assert::IsTrue(&floatDatum != &intDatum);
		}

		TEST_METHOD(AppendScope)
		{
			CREATE_TEST_VARS

			// Exception when AppendScope is called with key that is non-scope data.
			Datum& intDatum = scope1.Append(KEY_INT1);
			intDatum = int1;
			Assert::ExpectException<std::exception>( [&scope1]{scope1.AppendScope(KEY_INT1);});

			Scope& child1_1 = scope1.AppendScope(KEY_CHILD1);
			Assert::IsTrue(&child1_1 == &(*scope1.Find(KEY_CHILD1))[0]);
			Assert::IsTrue(child1_1.GetParent() == &scope1);

			Scope& child1_2 = scope1.AppendScope(KEY_CHILD1);
			Assert::IsTrue(&child1_2 == &(*scope1.Find(KEY_CHILD1))[1]);
			Assert::IsTrue(child1_2.GetParent() == &scope1);

			// Make sure the parents are set appropriately 
			Scope* containingScope = nullptr;
			Datum* foundDatum = child1_1.Search(KEY_INT1, &containingScope);
			Assert::IsTrue(foundDatum == &intDatum);
			Assert::IsTrue(containingScope == &scope1);
			foundDatum = child1_2.Search(KEY_INT1, &containingScope);
			Assert::IsTrue(foundDatum == &intDatum);
			Assert::IsTrue(containingScope == &scope1);
		}

		TEST_METHOD(Adopt)
		{
			CREATE_TEST_VARS

			Scope scope2;

			scope1.Append(KEY_INT1) = int1;
			scope2.Append(KEY_FLOAT1) = float1;

			// Create child1 as a child of scope1 first
			Scope& child1 = scope1.AppendScope(KEY_CHILD1);
			child1.Append(KEY_INT2) = int2;

			// child1 should be a child of scope1 
			Assert::IsTrue(child1.Search(KEY_INT1) != nullptr);
			Assert::IsTrue(child1.Search(KEY_FLOAT1) == nullptr);

			Assert::IsTrue(child1.GetParent() == &scope1);
			scope1.Adopt(scope1, KEY_CHILD2);
			Assert::IsTrue(scope1.Find(KEY_CHILD2) == nullptr);

			// Have scope2 adopt child1
			Assert::ExpectException<std::exception>( [&scope2, &child1] {scope2.Adopt(child1, KEY_FLOAT1);});
			scope2.Adopt(child1, KEY_CHILD1);
			Assert::IsTrue(child1.Search(KEY_INT1) == nullptr);
			Assert::IsTrue(child1.Search(KEY_FLOAT1) != nullptr);

			Assert::IsTrue(scope1.Find(KEY_CHILD1) != nullptr);
			Assert::IsTrue((*scope1.Find(KEY_CHILD1)).Size() == 0);
			Assert::IsTrue((*scope2.Find(KEY_CHILD1)).Size() == 1);

			Assert::IsTrue(child1.GetParent() == &scope2);
		}

		TEST_METHOD(GetParent)
		{
			Scope scope1;
			Scope scope2;

			Scope& child1 = scope1.AppendScope(KEY_CHILD1);
			Assert::IsTrue(child1.GetParent() == &scope1);

			Scope& child2 = child1.AppendScope(KEY_CHILD2);
			Assert::IsTrue(child2.GetParent() == &child1);
			Assert::IsTrue(child2.GetParent()->GetParent() == &scope1);

			scope2.Adopt(child1, KEY_CHILD1);
			Assert::IsTrue(child1.GetParent() == &scope2);
			Assert::IsTrue(child2.GetParent()->GetParent() == &scope2);
		}

		TEST_METHOD(SubscriptOperators)
		{
			CREATE_TEST_VARS

			scope1[KEY_INT1] = int1;
			scope1[KEY_FLOAT1] = float1;
			Assert::IsTrue(scope1[KEY_INT1].GetInteger() == int1);
			Assert::IsTrue(scope1[KEY_FLOAT1].GetFloat() == float1);
			Assert::IsTrue(scope1[0].Type() == DatumType::Integer);
			Assert::IsTrue(scope1[1].Type() == DatumType::Float);
			Assert::ExpectException<std::exception>([&scope1] {scope1[2];});
			Assert::IsTrue((*constScope1)[0].Type() == DatumType::Integer);
		}

		TEST_METHOD(EqualityOperator)
		{
			CREATE_TEST_VARS

			Scope scope2;
			Assert::IsTrue(scope1 == scope2);

			Scope& child1 = scope1.AppendScope(KEY_CHILD1);
			Assert::IsTrue(scope1 != scope2);
			scope1.Append(KEY_INT1) = int1;

			child1[KEY_INT1] = int1;
			child1[KEY_INT2] = int2;
			child1[KEY_STRING1] = string1;
			Assert::AreNotEqual(scope1, scope2);

			Scope* child2 = new Scope(child1);
			scope2.Adopt(*child2, KEY_CHILD1);
			Assert::AreNotEqual(scope1, scope2);

			scope2[KEY_INT1] = int1;
			Assert::AreEqual(scope1, scope2);

			delete child2;
		}

		TEST_METHOD(RTTIMethods)
		{
			CREATE_TEST_VARS
			Scope scope2;

			Scope* result = nullptr;
			Assert::IsTrue(scope1.Is(Scope::TypeIdClass()));
			Assert::IsTrue(scope1.Is("Scope"));
			Assert::IsFalse(scope1.Is(Foo::TypeIdClass()));
			Assert::IsFalse(scope1.Is("Foo"));

			result = scope1.As<Scope>();
			Assert::IsTrue(result != nullptr);
			result = reinterpret_cast<Scope*>(scope1.As<Foo>());
			Assert::IsTrue(result == nullptr);

			Assert::AreEqual(scope1.ToString(), std::string("0"));

			Assert::IsTrue(scope1.Equals(&scope2));
			scope2[KEY_INT1] = int1;
			Assert::IsFalse(scope1.Equals(&scope2));
			Assert::IsFalse(scope1.Equals(&foo1));

			RTTI* rResult = scope1.QueryInterface(Scope::TypeIdClass());
			Assert::IsTrue(rResult != nullptr);
			rResult = scope1.QueryInterface(Foo::TypeIdClass());
			Assert::IsTrue(rResult == nullptr);
		}

#pragma endregion

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ScopeTest::sStartMemState;
}
