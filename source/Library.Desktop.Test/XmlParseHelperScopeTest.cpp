#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

#define CREATE_TEST_SCOPE_1 Scope testScope1; \
testScope1["Integer1"] = 10; \
testScope1["Float1"] = 1.0f; \
Scope& testScope2 = testScope1.AppendScope("Scope2"); \
testScope2["Float2"] = 2.0f; \
testScope2["Integer2"] = 20; \
testScope2["String2"] = "Beep2!"; \
Scope& testScope3 = testScope2.AppendScope("Scope3"); \
testScope3["String3"] = "Beep3!"; \
testScope3["Float3"] = 3.0f; \
testScope3["Vector3"] = glm::vec4(3.0f, 4.0f, 5.0f, 6.0f); \
testScope1["Vector1"] = glm::vec4(1.0f, 2.0f, 3.0f, 4.0f); \
testScope1["Matrix1"] = glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f); \
Scope& testScope4 = testScope1.AppendScope("Scope4"); \
testScope4["Integer4"].PushBack(40); \
testScope4["Integer4"].PushBack(400); \
testScope4["Integer4"].PushBack(4000); \
testScope1["String1"] = "Beep1!";

namespace LibraryDesktopTest
{
	TEST_CLASS(XmlParseHelperScopeTest)
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

#pragma region SharedDataTests


		TEST_METHOD(ValidScopeParseTest)
		{
			XmlParseMaster parseMaster;
			ScopeSharedData scopeData;
			XmlParseHelperScope parseHelperScope;

			parseMaster.SetSharedData(&scopeData);
			parseMaster.AddHelper(parseHelperScope);

			parseMaster.ParseFromFile("../../../files/ScopeTest1.xml");

			Scope* result = scopeData.mScope;

			CREATE_TEST_SCOPE_1

			Assert::IsTrue(*result == testScope1);
		}

		TEST_METHOD(InvalidGrammarTest)
		{
			XmlParseMaster parseMaster;
			ScopeSharedData scopeData;
			XmlParseHelperScope parseHelperScope;

			parseMaster.SetSharedData(&scopeData);
			parseMaster.AddHelper(parseHelperScope);

			Assert::ExpectException<std::exception>([&parseMaster]{parseMaster.ParseFromFile("../../../files/ScopeTestInvalidName.xml");});

			Assert::ExpectException<std::exception>([&parseMaster] {parseMaster.ParseFromFile("../../../files/ScopeTestInvalidValue.xml");});

			Assert::ExpectException<std::exception>([&parseMaster] {parseMaster.ParseFromFile("../../../files/ScopeTestInvalidNameScope.xml"); });
		}

		TEST_METHOD(CloneTest)
		{
			XmlParseMaster parseMaster;
			ScopeSharedData scopeData;
			XmlParseHelperScope parseHelperScope;

			parseMaster.SetSharedData(&scopeData);
			parseMaster.AddHelper(parseHelperScope);

			parseMaster.ParseFromFile("../../../files/ScopeTest1.xml");

			XmlParseMaster::SharedData* clonedData = scopeData.Clone();
			Assert::IsTrue(clonedData->Is(ScopeSharedData::TypeIdClass()));
			Assert::IsTrue(clonedData->As<ScopeSharedData>()->mScope != scopeData.mScope);
			Assert::IsTrue(*(clonedData->As<ScopeSharedData>()->mScope) == *(scopeData.mScope));

			delete clonedData;
			clonedData = nullptr;

			IXmlParseHelper* clonedHelper = parseHelperScope.Clone();
			Assert::IsTrue(clonedHelper != &parseHelperScope);

			delete clonedHelper;
			clonedHelper = nullptr;
		}

		TEST_METHOD(SnatchScope)
		{
			XmlParseMaster parseMaster;
			ScopeSharedData scopeData;
			XmlParseHelperScope parseHelperScope;

			parseMaster.SetSharedData(&scopeData);
			parseMaster.AddHelper(parseHelperScope);

			parseMaster.ParseFromFile("../../../files/ScopeTest1.xml");

			Scope* snatchedScope = scopeData.SnatchScope();

			Assert::IsTrue(scopeData.mScope == nullptr);

			delete snatchedScope;
			snatchedScope = nullptr;
		}

#pragma endregion

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XmlParseHelperScopeTest::sStartMemState;
}
