#include "pch.h"

#define KEY_INT1 "int1"
#define KEY_INT2 " int2"
#define KEY_FLOAT1 "float1"
#define KEY_STRING1 "string1"
#define KEY_CHILD1 "child1"
#define KEY_CHILD2 "child2"
#define AUXILIARY_KEY_1 "aux1"
#define AUXILIARY_KEY_2 "aux2"
#define AUXILIARY_KEY_3 "aux3"

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
			Assert::IsTrue(afoo.IsAttribute(AttributedFoo::INTERNAL_INTEGER_KEY));
			Assert::AreEqual(AttributedFoo::INTERNAL_INTEGER_DEFAULT, afoo[AttributedFoo::INTERNAL_INTEGER_KEY].GetInteger());

		}

		TEST_METHOD(CopySemantics)
		{
			CREATE_TEST_VARS

		}

		TEST_METHOD(IsAttributeMethods)
		{
			CREATE_TEST_VARS

			AttributedFoo afoo;

			// IsAttribute()
			Assert::IsTrue(afoo.IsAttribute(AttributedFoo::INTERNAL_INTEGER_KEY));
			Assert::IsTrue(afoo.IsAttribute(AttributedFoo::INTERNAL_FLOAT_KEY));
			Assert::IsTrue(afoo.IsAttribute(AttributedFoo::INTERNAL_VECTOR_KEY));
			Assert::IsTrue(afoo.IsAttribute(AttributedFoo::INTERNAL_MATRIX_KEY));
			Assert::IsTrue(afoo.IsAttribute(AttributedFoo::INTERNAL_STRING_KEY));
			Assert::IsTrue(afoo.IsAttribute(AttributedFoo::INTERNAL_POINTER_KEY));
			Assert::IsTrue(afoo.IsAttribute(AttributedFoo::EXTERNAL_INTEGER_KEY));
			Assert::IsTrue(afoo.IsAttribute(AttributedFoo::EXTERNAL_FLOAT_KEY));
			Assert::IsTrue(afoo.IsAttribute(AttributedFoo::EXTERNAL_VECTOR_KEY));
			Assert::IsTrue(afoo.IsAttribute(AttributedFoo::EXTERNAL_MATRIX_KEY));
			Assert::IsTrue(afoo.IsAttribute(AttributedFoo::EXTERNAL_STRING_KEY));
			Assert::IsTrue(afoo.IsAttribute(AttributedFoo::EXTERNAL_POINTER_KEY));
			Assert::IsTrue(afoo.IsAttribute(AttributedFoo::NESTED_SCOPE_KEY));

			// IsPrescribedAttribute()
			Assert::IsTrue(afoo.IsPrescribedAttribute(AttributedFoo::INTERNAL_INTEGER_KEY));
			Assert::IsTrue(afoo.IsPrescribedAttribute(AttributedFoo::INTERNAL_FLOAT_KEY));
			Assert::IsTrue(afoo.IsPrescribedAttribute(AttributedFoo::INTERNAL_VECTOR_KEY));
			Assert::IsTrue(afoo.IsPrescribedAttribute(AttributedFoo::INTERNAL_MATRIX_KEY));
			Assert::IsTrue(afoo.IsPrescribedAttribute(AttributedFoo::INTERNAL_STRING_KEY));
			Assert::IsTrue(afoo.IsPrescribedAttribute(AttributedFoo::INTERNAL_POINTER_KEY));
			Assert::IsTrue(afoo.IsPrescribedAttribute(AttributedFoo::EXTERNAL_INTEGER_KEY));
			Assert::IsTrue(afoo.IsPrescribedAttribute(AttributedFoo::EXTERNAL_FLOAT_KEY));
			Assert::IsTrue(afoo.IsPrescribedAttribute(AttributedFoo::EXTERNAL_VECTOR_KEY));
			Assert::IsTrue(afoo.IsPrescribedAttribute(AttributedFoo::EXTERNAL_MATRIX_KEY));
			Assert::IsTrue(afoo.IsPrescribedAttribute(AttributedFoo::EXTERNAL_STRING_KEY));
			Assert::IsTrue(afoo.IsPrescribedAttribute(AttributedFoo::EXTERNAL_POINTER_KEY));
			Assert::IsTrue(afoo.IsPrescribedAttribute(AttributedFoo::NESTED_SCOPE_KEY));

			// IsAuxiliaryAttribute()
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AttributedFoo::INTERNAL_INTEGER_KEY));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AttributedFoo::INTERNAL_FLOAT_KEY));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AttributedFoo::INTERNAL_VECTOR_KEY));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AttributedFoo::INTERNAL_MATRIX_KEY));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AttributedFoo::INTERNAL_STRING_KEY));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AttributedFoo::INTERNAL_POINTER_KEY));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AttributedFoo::EXTERNAL_INTEGER_KEY));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AttributedFoo::EXTERNAL_FLOAT_KEY));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AttributedFoo::EXTERNAL_VECTOR_KEY));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AttributedFoo::EXTERNAL_MATRIX_KEY));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AttributedFoo::EXTERNAL_STRING_KEY));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AttributedFoo::EXTERNAL_POINTER_KEY));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AttributedFoo::NESTED_SCOPE_KEY));

			// Test non existent keys
			Assert::IsFalse(afoo.IsAttribute(AUXILIARY_KEY_1));
			Assert::IsFalse(afoo.IsAttribute(AUXILIARY_KEY_2));
			Assert::IsFalse(afoo.IsAttribute(AUXILIARY_KEY_3));
			Assert::IsFalse(afoo.IsPrescribedAttribute(AUXILIARY_KEY_1));
			Assert::IsFalse(afoo.IsPrescribedAttribute(AUXILIARY_KEY_2));
			Assert::IsFalse(afoo.IsPrescribedAttribute(AUXILIARY_KEY_3));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AUXILIARY_KEY_1));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AUXILIARY_KEY_2));
			Assert::IsFalse(afoo.IsAuxiliaryAttribute(AUXILIARY_KEY_3));

			// Add auxiliary attributes
			afoo.AddAuxiliaryAttribute(AUXILIARY_KEY_1);
			afoo.AddAuxiliaryAttribute(AUXILIARY_KEY_2);
			afoo.AddAuxiliaryAttribute(AUXILIARY_KEY_3);

			// Test new auxiliary attributes
			Assert::IsTrue(afoo.IsAttribute(AUXILIARY_KEY_1));
			Assert::IsTrue(afoo.IsAttribute(AUXILIARY_KEY_2));
			Assert::IsTrue(afoo.IsAttribute(AUXILIARY_KEY_3));
			Assert::IsTrue(afoo.IsAuxiliaryAttribute(AUXILIARY_KEY_1));
			Assert::IsTrue(afoo.IsAuxiliaryAttribute(AUXILIARY_KEY_2));
			Assert::IsTrue(afoo.IsAuxiliaryAttribute(AUXILIARY_KEY_3));
			Assert::IsFalse(afoo.IsPrescribedAttribute(AUXILIARY_KEY_1));
			Assert::IsFalse(afoo.IsPrescribedAttribute(AUXILIARY_KEY_2));
			Assert::IsFalse(afoo.IsPrescribedAttribute(AUXILIARY_KEY_3));
		}

		TEST_METHOD(ExternalAssignment)
		{
			// Ensure that editing Datum assignment for external variables and c++ assignment
			// both edit the same variables.
			AttributedFoo afoo;

			std::int32_t& value = afoo[AttributedFoo::EXTERNAL_INTEGER_KEY].GetInteger();
			Assert::AreEqual(afoo.mInteger, value);

			value++;
			Assert::AreEqual(afoo.mInteger, value);

			afoo.mInteger++;
			Assert::AreEqual(afoo.mInteger, value);
		}

		TEST_METHOD(TestRTTI)
		{
			Attributed* attributed = new Attributed();
			Attributed* attributed2 = new Attributed();
			AttributedFoo* afoo = new AttributedFoo();

			Assert::IsTrue(attributed->Is(Attributed::TypeIdClass()));
			Assert::IsTrue(attributed->Is("Attributed"));
			Assert::IsFalse(attributed->Is(AttributedFoo::TypeIdClass()));
			Assert::IsFalse(attributed->Is("AttributedFoo"));

			Assert::IsTrue(attributed->As<Attributed>() != nullptr);
			Assert::IsTrue(attributed->As<Scope>() != nullptr);
			Assert::IsTrue(attributed->As<AttributedFoo>() == nullptr);

			Assert::AreEqual(attributed->ToString(), std::string("0"));

			Assert::IsTrue(attributed->Equals(attributed2));
			Assert::IsFalse(attributed->Equals(afoo));

			RTTI* result = attributed->QueryInterface(Attributed::TypeIdClass());
			Assert::IsTrue(result != nullptr);
			result = attributed->QueryInterface(AttributedFoo::TypeIdClass());
			Assert::IsTrue(result == nullptr);
			result = afoo->QueryInterface(Attributed::TypeIdClass());
			Assert::IsTrue(result != nullptr);

			delete attributed;
			attributed = nullptr;
			delete attributed2;
			attributed2 = nullptr;
			delete afoo;
			afoo = nullptr;
		}

#pragma endregion

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AttributedTest::sStartMemState;
}
