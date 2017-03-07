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
	TEST_CLASS(AttributedTest)
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
			Attributed::ClearPrescribedAttributeCache();

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
			CREATE_TEST_VARS

			AttributedFoo afoo;
			afoo.IsAttribute(AttributedFoo::INTERNAL_INTEGER_KEY);
			Assert::AreEqual(AttributedFoo::INTERNAL_INTEGER_DEFAULT, afoo[AttributedFoo::INTERNAL_INTEGER_KEY].GetInteger());

		}

		TEST_METHOD(CopySemantics)
		{
			CREATE_TEST_VARS

		}


#pragma endregion

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AttributedTest::sStartMemState;
}
