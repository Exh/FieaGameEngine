#include "pch.h"

#define CREATE_TEST_VARS int32_t int1 = 10; \
int32_t int2 = 20; \
int32_t int3 = 30; \
float float1 = 10.0f; \
float float2 = 20.0f; \
float float3 = 30.0f; \
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
int32_t externalInts[] = {int1, int2, int3}; \
float externalFloats[] = {float1, float2, float3}; \
glm::vec4 externalVectors[] = {vector1, vector2, vector3}; \
glm::mat4 externalMatrices[] = {matrix1, matrix2, matrix3}; \
std::string externalStrings[] = {string1, string2, string3}; \
RTTI* externalPointers[] = {pointer1, pointer2, pointer3}; \
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
externalInts; \
externalFloats; \
externalVectors; \
externalMatrices; \
externalStrings; \
externalPointers;

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
		}
	}
}

namespace LibraryDesktopTest
{
	TEST_CLASS(DatumTest)
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
			Datum datum1;
			Assert::AreEqual(datum1.Size(), 0U);
			Assert::AreEqual(datum1.Type(), DatumType::Unknown);
		}

		TEST_METHOD(CopyConstructor)
		{
			int int1 = 10;

			Datum datum1;
			datum1.SetType(DatumType::Integer);
			datum1.PushBack(int1);
			Assert::AreEqual(datum1.Size(), 1U);
			Assert::AreEqual(datum1.Type(), DatumType::Integer);

			Datum datum2(datum1);
			Assert::AreEqual(datum2.Size(), 1U);
			Assert::AreEqual(datum2.Type(), DatumType::Integer);
			Assert::AreEqual(datum2.GetInteger(), int1);
		}

		TEST_METHOD(AssignmentOperators)
		{
			CREATE_TEST_VARS

			// Datum assignment
			{
				Datum datum1;
				datum1.SetType(DatumType::Integer);
				datum1.PushBack(int1);
				Assert::AreEqual(datum1.Size(), 1U);
				Assert::AreEqual(datum1.Type(), DatumType::Integer);

				Datum datum2;
				Assert::AreEqual(datum2.Size(), 0U);
				Assert::AreEqual(datum2.Type(), DatumType::Unknown);

				datum2 = datum1;
				Assert::AreEqual(datum2.Size(), 1U);
				Assert::AreEqual(datum2.Type(), DatumType::Integer);
				Assert::AreEqual(datum2.GetInteger(), int1);

				datum2 = datum2;
			}

			// int assignment
			{
				Datum datum;
				Assert::AreEqual(datum.Type(), DatumType::Unknown);
				Assert::AreEqual(datum.Size(), 0U);
				datum = int1;
				Assert::AreEqual(datum.Type(), DatumType::Integer);
				Assert::AreEqual(datum.Size(), 1U);
				Assert::AreEqual(datum.GetInteger(), int1);
				auto exceptionCase1 = [&datum, &float1]{ datum = float1; };
				Assert::ExpectException<std::exception>(exceptionCase1);
				datum = int2;
				Assert::AreEqual(datum.Size(), 1U);
				Assert::AreEqual(datum.GetInteger(), int2);
			}

			// float assignment
			{
				Datum datum;
				Assert::AreEqual(datum.Type(), DatumType::Unknown);
				Assert::AreEqual(datum.Size(), 0U);
				datum = float1;
				Assert::AreEqual(datum.Type(), DatumType::Float);
				Assert::AreEqual(datum.Size(), 1U);
				Assert::AreEqual(datum.GetFloat(), float1);
				auto exceptionCase1 = [&datum, &int1] { datum = int1; };
				Assert::ExpectException<std::exception>(exceptionCase1);
				datum = float2;
				Assert::AreEqual(datum.Size(), 1U);
				Assert::AreEqual(datum.GetFloat(), float2);
			}

			// vector assignment
			{
				Datum datum;
				Assert::AreEqual(datum.Type(), DatumType::Unknown);
				Assert::AreEqual(datum.Size(), 0U);
				datum = vector1;
				Assert::AreEqual(datum.Type(), DatumType::Vector);
				Assert::AreEqual(datum.Size(), 1U);
				Assert::AreEqual(datum.GetVector(), vector1);
				auto exceptionCase1 = [&datum, &float1] { datum = float1; };
				Assert::ExpectException<std::exception>(exceptionCase1);
				datum = vector2;
				Assert::AreEqual(datum.Size(), 1U);
				Assert::AreEqual(datum.GetVector(), vector2);
			}

			// matrix assignment
			{
				Datum datum;
				Assert::AreEqual(datum.Type(), DatumType::Unknown);
				Assert::AreEqual(datum.Size(), 0U);
				datum = matrix1;
				Assert::AreEqual(datum.Type(), DatumType::Matrix);
				Assert::AreEqual(datum.Size(), 1U);
				Assert::AreEqual(datum.GetMatrix(), matrix1);
				auto exceptionCase1 = [&datum, &float1] { datum = float1; };
				Assert::ExpectException<std::exception>(exceptionCase1);
				datum = matrix2;
				Assert::AreEqual(datum.Size(), 1U);
				Assert::AreEqual(datum.GetMatrix(), matrix2);
			}

			// string assignment
			{
				Datum datum;
				Assert::AreEqual(datum.Type(), DatumType::Unknown);
				Assert::AreEqual(datum.Size(), 0U);
				datum = string1;
				Assert::AreEqual(datum.Type(), DatumType::String);
				Assert::AreEqual(datum.Size(), 1U);
				Assert::AreEqual(datum.GetString(), string1);
				auto exceptionCase1 = [&datum, &float1] { datum = float1; };
				Assert::ExpectException<std::exception>(exceptionCase1);
				datum = string2;
				Assert::AreEqual(datum.Size(), 1U);
				Assert::AreEqual(datum.GetString(), string2);
			}

			// pointer assignment
			{
				Datum datum;
				Assert::AreEqual(datum.Type(), DatumType::Unknown);
				Assert::AreEqual(datum.Size(), 0U);
				datum = pointer1;
				Assert::AreEqual(datum.Type(), DatumType::Pointer);
				Assert::AreEqual(datum.Size(), 1U);
				Assert::AreEqual(datum.GetPointer(), pointer1);
				auto exceptionCase1 = [&datum, &float1] { datum = float1; };
				Assert::ExpectException<std::exception>(exceptionCase1);
				datum = pointer2;
				Assert::AreEqual(datum.Size(), 1U);
				Assert::AreEqual(datum.GetPointer(), pointer2);
			}
		}

		TEST_METHOD(GetTest)
		{
			CREATE_TEST_VARS

			{
				Datum datum;
				Assert::ExpectException<std::exception>([&datum] {datum.GetInteger();});
				datum = int1;
				Assert::AreEqual(datum.GetInteger(), int1);
				datum.PushBack(int2);
				datum.PushBack(int3);
				Assert::AreEqual(datum.GetInteger(1), int2);
				Assert::AreEqual(datum.GetInteger(2), int3);
				Assert::ExpectException<std::exception>([&datum]{datum.GetFloat();});
			}

			{
				Datum datum;
				Assert::ExpectException<std::exception>([&datum] {datum.GetFloat(); });
				datum = float1;
				Assert::AreEqual(datum.GetFloat(), float1);
				datum.PushBack(float2);
				datum.PushBack(float3);
				Assert::AreEqual(datum.GetFloat(1), float2);
				Assert::AreEqual(datum.GetFloat(2), float3);
				Assert::ExpectException<std::exception>([&datum] {datum.GetVector(); });
			}

			{
				Datum datum;
				Assert::ExpectException<std::exception>([&datum] {datum.GetVector(); });
				datum = vector1;
				Assert::AreEqual(datum.GetVector(), vector1);
				datum.PushBack(vector2);
				datum.PushBack(vector3);
				Assert::AreEqual(datum.GetVector(1), vector2);
				Assert::AreEqual(datum.GetVector(2), vector3);
				Assert::ExpectException<std::exception>([&datum] {datum.GetFloat(); });
			}

			{
				Datum datum;
				Assert::ExpectException<std::exception>([&datum] {datum.GetMatrix(); });
				datum = matrix1;
				Assert::AreEqual(datum.GetMatrix(), matrix1);
				datum.PushBack(matrix2);
				datum.PushBack(matrix3);
				Assert::AreEqual(datum.GetMatrix(1), matrix2);
				Assert::AreEqual(datum.GetMatrix(2), matrix3);
				Assert::ExpectException<std::exception>([&datum] {datum.GetFloat(); });
			}

			{
				Datum datum;
				Assert::ExpectException<std::exception>([&datum] {datum.GetString(); });
				datum = string1;
				Assert::AreEqual(datum.GetString(), string1);
				datum.PushBack(string2);
				datum.PushBack(string3);
				Assert::AreEqual(datum.GetString(1), string2);
				Assert::AreEqual(datum.GetString(2), string3);
				Assert::ExpectException<std::exception>([&datum] {datum.GetFloat(); });
			}

			{
				Datum datum;
				Assert::ExpectException<std::exception>([&datum] {datum.GetPointer(); });
				datum = pointer1;
				Assert::AreEqual(datum.GetPointer(), pointer1);
				datum.PushBack(pointer2);
				datum.PushBack(pointer3);
				Assert::AreEqual(datum.GetPointer(1), pointer2);
				Assert::AreEqual(datum.GetPointer(2), pointer3);
				Assert::ExpectException<std::exception>([&datum] {datum.GetFloat(); });
			}
		}

		TEST_METHOD(Type)
		{
			CREATE_TEST_VARS

			// Integer
			{
				Datum datum;
				Assert::AreEqual(datum.Type(), DatumType::Unknown);
				datum.SetType(DatumType::Integer);
				Assert::AreEqual(datum.Type(), DatumType::Integer);
				datum.SetType(DatumType::Integer);
				Assert::ExpectException<std::exception>([&datum]{datum.SetType(DatumType::Float);});
			}

			// Float
			{
				Datum datum;
				Assert::AreEqual(datum.Type(), DatumType::Unknown);
				datum.SetType(DatumType::Float);
				Assert::AreEqual(datum.Type(), DatumType::Float);
				datum.SetType(DatumType::Float);
				Assert::ExpectException<std::exception>([&datum] {datum.SetType(DatumType::Integer); });
			}

			// Vector
			{
				Datum datum;
				Assert::AreEqual(datum.Type(), DatumType::Unknown);
				datum.SetType(DatumType::Vector);
				Assert::AreEqual(datum.Type(), DatumType::Vector);
				datum.SetType(DatumType::Vector);
				Assert::ExpectException<std::exception>([&datum] {datum.SetType(DatumType::Float); });
			}

			// Matrix
			{
				Datum datum;
				Assert::AreEqual(datum.Type(), DatumType::Unknown);
				datum.SetType(DatumType::Matrix);
				Assert::AreEqual(datum.Type(), DatumType::Matrix);
				datum.SetType(DatumType::Matrix);
				Assert::ExpectException<std::exception>([&datum] {datum.SetType(DatumType::Float); });
			}

			// String
			{
				Datum datum;
				Assert::AreEqual(datum.Type(), DatumType::Unknown);
				datum.SetType(DatumType::String);
				Assert::AreEqual(datum.Type(), DatumType::String);
				datum.SetType(DatumType::String);
				Assert::ExpectException<std::exception>([&datum] {datum.SetType(DatumType::Float); });
			}

			// Pointer
			{
				Datum datum;
				Assert::AreEqual(datum.Type(), DatumType::Unknown);
				datum.SetType(DatumType::Pointer);
				Assert::AreEqual(datum.Type(), DatumType::Pointer);
				datum.SetType(DatumType::Pointer);
				Assert::ExpectException<std::exception>([&datum] {datum.SetType(DatumType::Float); });
			}
		}

		TEST_METHOD(Size)
		{
			CREATE_TEST_VARS

			// Integer
			{
				Datum datum;
				Assert::AreEqual(datum.Size(), 0U);
				datum.PushBack(int1);
				datum.PushBack(int2);
				Assert::AreEqual(datum.Size(), 2U);
				datum.Clear();
				Assert::AreEqual(datum.Size(), 0U);
			}

			// Float
			{
				Datum datum;
				Assert::AreEqual(datum.Size(), 0U);
				datum.PushBack(float1);
				datum.PushBack(float2);
				Assert::AreEqual(datum.Size(), 2U);
				datum.Clear();
				Assert::AreEqual(datum.Size(), 0U);
			}

			// Vector
			{
				Datum datum;
				Assert::AreEqual(datum.Size(), 0U);
				datum.PushBack(vector1);
				datum.PushBack(vector2);
				Assert::AreEqual(datum.Size(), 2U);
				datum.Clear();
				Assert::AreEqual(datum.Size(), 0U);
			}

			// Matrix
			{
				Datum datum;
				Assert::AreEqual(datum.Size(), 0U);
				datum.PushBack(matrix1);
				datum.PushBack(matrix2);
				Assert::AreEqual(datum.Size(), 2U);
				datum.Clear();
				Assert::AreEqual(datum.Size(), 0U);
			}

			// String
			{
				Datum datum;
				Assert::AreEqual(datum.Size(), 0U);
				datum.PushBack(string1);
				datum.PushBack(string2);
				Assert::AreEqual(datum.Size(), 2U);
				datum.Clear();
				Assert::AreEqual(datum.Size(), 0U);
			}

			// Pointer
			{
				Datum datum;
				Assert::AreEqual(datum.Size(), 0U);
				datum.PushBack(pointer1);
				datum.PushBack(pointer2);
				Assert::AreEqual(datum.Size(), 2U);
				datum.Clear();
				Assert::AreEqual(datum.Size(), 0U);
			}
		}

		TEST_METHOD(SetStorage)
		{
			CREATE_TEST_VARS

			int arr[] = {int1, int2, int3};
			{
				Datum datum;
				datum.SetStorage(externalInts, 3U);
				Assert::AreEqual(datum.Size(), 3U);
				Assert::AreEqual(datum.Type(), DatumType::Integer);
				datum.GetInteger(2) = int1;
				Assert::AreEqual(datum.GetInteger(2), int1);
				Assert::ExpectException<std::exception>([&datum, &externalFloats] {datum.SetStorage(externalFloats, 3);});
				Assert::ExpectException<std::exception>([&datum] {datum.Clear();});
				Assert::ExpectException<std::exception>([&datum, &int1] {datum.PushBack(int1);});

				Datum datum2;
				datum2.PushBack(int1);
				Assert::ExpectException<std::exception>([&datum2, &externalInts] {datum2.SetStorage(externalInts, 3);});
			}
		}

#pragma endregion

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState DatumTest::sStartMemState;
}
