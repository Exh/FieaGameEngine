#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

#define INT_VALUE_KEY "intValue"
#define FLOAT_VALUE_KEY "floatValue"

#define CREATE_TEST_VARS int32_t int1 = 10; \
int32_t int2 = 20; \
int32_t int3 = 30; \
float float1 = 1.0f; \
float float2 = 2.0f; \
float float3 = 3.0f; \
std::string string1 = "Bar String 1!"; \
std::string string2 = "Bar String 2!"; \
std::string string3 = "Bar String 3!"; \
XmlParseMaster parseMaster1; \
XmlParseMaster parseMaster2; \
BarParseHelper barParseHelper1; \
BarParseHelper barParseHelper2; \
BarSharedData barSharedData1; \
BarSharedData barSharedData2; \
int1; \
int2; \
int3; \
float1; \
float2; \
float3; \
string1; \
string2; \
string3; \
parseMaster1; \
parseMaster2; \
barParseHelper1; \
barParseHelper2; \
barSharedData1; \
barSharedData2;


namespace LibraryDesktopTest
{
	TEST_CLASS(XmlParseMasterTest)
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

		void WriteParseResults(BarSharedData& resultData, const char* filename)
		{
			FILE* file = nullptr;

			fopen_s(&file, filename, "w");

			if (file != nullptr)
			{
				resultData.mRootBar->PrintStringToFile(file, 0);

				fclose(file);
				file = nullptr;
			}
		}

#pragma region SharedDataTests

		TEST_METHOD(SharedDataContructor)
		{
			CREATE_TEST_VARS

			Assert::IsTrue(barSharedData1.Depth() == 0);
			Assert::IsTrue(barSharedData1.GetXmlParseMaster() == nullptr);
			Assert::IsTrue(barSharedData1.mCurrentBar == nullptr);
			Assert::IsTrue(barSharedData1.mRootBar == nullptr);
		}

		TEST_METHOD(SharedDataDestructor)
		{
			CREATE_TEST_VARS

			BarSharedData* barSharedData = new BarSharedData();
			barSharedData->mRootBar = new Bar();
			XmlParseMaster::SharedData* sharedData1 = static_cast<BarSharedData*>(barSharedData);
			delete sharedData1;
			sharedData1 = nullptr;
			barSharedData = nullptr;

			// Ensure no memory leaks.
		}

		TEST_METHOD(SharedDataInitialize)
		{
			CREATE_TEST_VARS

			barSharedData1.mRootBar = new Bar();
			barSharedData1.mCurrentBar = barSharedData1.mRootBar;
			barSharedData1.IncrementDepth();
			
			barSharedData1.Initialize();

			Assert::IsTrue(barSharedData1.mRootBar == nullptr);
			Assert::IsTrue(barSharedData1.mCurrentBar == nullptr);
			Assert::IsTrue(barSharedData1.Depth() == 0U);
		}

		TEST_METHOD(SharedDataClone)
		{
			CREATE_TEST_VARS

			BarSharedData barSharedData;
			barSharedData.IncrementDepth();
			barSharedData.SetXmlParseMaster(&parseMaster1);
			barSharedData.mRootBar = new Bar();

			XmlParseMaster::SharedData* clone = barSharedData.Clone();
			Assert::IsTrue(clone->Is(BarSharedData::TypeIdClass()));
			Assert::IsTrue(clone->Depth() == 0U);
			Assert::IsTrue(clone->GetXmlParseMaster() == nullptr);
			Assert::IsTrue(barSharedData.Depth() != 0U);
			Assert::IsTrue(barSharedData.GetXmlParseMaster() != nullptr);
			Assert::IsTrue(clone->As<BarSharedData>()->mRootBar != nullptr);
			Assert::IsTrue(barSharedData.mRootBar != nullptr);
			Assert::IsTrue(barSharedData.mRootBar != clone->As<BarSharedData>()->mRootBar);

			delete clone;
		}

		TEST_METHOD(SharedDataGetSetParseMaster)
		{
			XmlParseMaster parseMaster1;
			BarSharedData barSharedData1;

			Assert::IsTrue(barSharedData1.GetXmlParseMaster() == nullptr);
			barSharedData1.SetXmlParseMaster(&parseMaster1);
			Assert::IsTrue(barSharedData1.GetXmlParseMaster() == &parseMaster1);

			const BarSharedData* constPointer = &barSharedData1;
			Assert::IsTrue(constPointer->GetXmlParseMaster() == &parseMaster1);
		}

		TEST_METHOD(SharedDataDepth)
		{
			BarSharedData barSharedData1;
			Assert::IsTrue(barSharedData1.Depth() == 0U);
			barSharedData1.IncrementDepth();
			Assert::IsTrue(barSharedData1.Depth() == 1U);
			barSharedData1.DecrementDepth();
			Assert::IsTrue(barSharedData1.Depth() == 0U);

			Assert::ExpectException<std::exception>([&barSharedData1]{barSharedData1.DecrementDepth();});
		}


#pragma endregion

		TEST_METHOD(GenericParseTest)
		{
			XmlParseMaster parseMaster;
			BarSharedData sharedData1;
			BarParseHelper barParseHelper;

			parseMaster.SetSharedData(&sharedData1);
			parseMaster.AddHelper(barParseHelper);

			parseMaster.ParseFromFile("../../../files/BarTestAttributes.xml");
			WriteParseResults(sharedData1, "BarTestAttributesResults.txt");

			BarSharedData sharedData2;
			parseMaster.SetSharedData(&sharedData2);
			parseMaster.ParseFromFile("../../../files/BarTestCharData.xml");
			WriteParseResults(sharedData2, "BarTestCharDataResults.txt");

			Assert::IsTrue(*(sharedData1.mRootBar) == *(sharedData2.mRootBar));
		}



	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XmlParseMasterTest::sStartMemState;
}
