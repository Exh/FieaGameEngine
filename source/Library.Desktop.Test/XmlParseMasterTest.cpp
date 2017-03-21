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

#define CREATE_ROOT_BAR Bar rootBar; \
rootBar.mIntValue = 10; \
rootBar.mFloatValue = 1.0f; \
rootBar.mParent = nullptr; \
rootBar.mString = "Bar String 1!";


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

#pragma region ParseMasterTests

		TEST_METHOD(XmlParseMasterConstructor)
		{
			XmlParseMaster parseMaster1;
			Assert::IsTrue(parseMaster1.GetSharedData() == nullptr);

			BarSharedData barSharedData;
			XmlParseMaster parseMaster2(&barSharedData);
			Assert::IsTrue(parseMaster2.GetSharedData() == &barSharedData);
		}

		TEST_METHOD(XmlParseMasterClone)
		{
			XmlParseMaster parseMaster1;
			BarParseHelper barParseHelper1;
			BarParseHelper barParseHelper2;
			BarParseHelper barParseHelper3;
			BarSharedData barSharedData;

			parseMaster1.SetSharedData(&barSharedData);
			parseMaster1.AddHelper(barParseHelper1);
			parseMaster1.AddHelper(barParseHelper2);

			parseMaster1.ParseFromFile("../../../files/BarTestAttributes.xml");

			XmlParseMaster* clone = parseMaster1.Clone();

			Assert::IsTrue(clone->GetFileName() == nullptr);
			Assert::IsTrue(clone->GetSharedData() != nullptr);
			Assert::IsTrue(clone->GetSharedData() != parseMaster1.GetSharedData());

			Assert::ExpectException<std::exception>([clone, &barParseHelper2]{clone->RemoveHelper(barParseHelper2);});
			Assert::ExpectException<std::exception>([clone, &barParseHelper3]{clone->AddHelper(barParseHelper3);});

			delete clone;
			clone = nullptr;
		}

		TEST_METHOD(XmlParseMasterAddRemoveHelper)
		{
			XmlParseMaster parseMaster1;
			BarParseHelper barParseHelper1;
			BarParseHelper barParseHelper2;
			BarSharedData barSharedData;

			parseMaster1.SetSharedData(&barSharedData);
			parseMaster1.AddHelper(barParseHelper1);
			parseMaster1.RemoveHelper(barParseHelper1);

			parseMaster1.ParseFromFile("../../../files/BarTestAttributes.xml");
			Assert::IsTrue(barSharedData.mRootBar == nullptr);

			parseMaster1.AddHelper(barParseHelper2);
			parseMaster1.ParseFromFile("../../../files/BarTestAttributes.xml");
			Assert::IsTrue(barSharedData.mRootBar != nullptr);
		}

		TEST_METHOD(XmlParseMasterParseFromFile)
		{
			XmlParseMaster parseMaster;
			BarSharedData sharedData1;
			BarParseHelper barParseHelper;

			parseMaster.SetSharedData(&sharedData1);
			parseMaster.AddHelper(barParseHelper);

			parseMaster.ParseFromFile("../../../files/BarTestAttributes.xml");
			WriteParseResults(sharedData1, "BarTestAttributesResults.txt");

			Assert::IsTrue(sharedData1.mRootBar->mIntValue == 10);
			Assert::IsTrue(sharedData1.mRootBar->mFloatValue == 1.0f);
			Assert::IsTrue(sharedData1.mRootBar->mString == "Bar String 1!");
			Assert::IsTrue(sharedData1.mRootBar->mChildren[0].mIntValue == 20);
			Assert::IsTrue(sharedData1.mRootBar->mChildren[0].mFloatValue == 2.0f);
			Assert::IsTrue(sharedData1.mRootBar->mChildren[0].mString == "Bar String 2!");
			Assert::IsTrue(sharedData1.mRootBar->mChildren[0].mChildren[0].mIntValue == 40);
			Assert::IsTrue(sharedData1.mRootBar->mChildren[0].mChildren[0].mFloatValue == 4.0f);
			Assert::IsTrue(sharedData1.mRootBar->mChildren[0].mChildren[0].mString == "");
			Assert::IsTrue(sharedData1.mRootBar->mChildren[1].mIntValue == 30);
			Assert::IsTrue(sharedData1.mRootBar->mChildren[1].mFloatValue == 3.0f);
			Assert::IsTrue(sharedData1.mRootBar->mChildren[1].mString == "Bar String 3!");

			BarSharedData sharedData2;
			parseMaster.SetSharedData(&sharedData2);
			parseMaster.ParseFromFile("../../../files/BarTestCharData.xml");
			WriteParseResults(sharedData2, "BarTestCharDataResults.txt");

			Assert::IsTrue(sharedData2.mRootBar->mIntValue == 10);
			Assert::IsTrue(sharedData2.mRootBar->mFloatValue == 1.0f);
			Assert::IsTrue(sharedData2.mRootBar->mString == "Bar String 1!");
			Assert::IsTrue(sharedData2.mRootBar->mChildren[0].mIntValue == 20);
			Assert::IsTrue(sharedData2.mRootBar->mChildren[0].mFloatValue == 2.0f);
			Assert::IsTrue(sharedData2.mRootBar->mChildren[0].mString == "Bar String 2!");
			Assert::IsTrue(sharedData2.mRootBar->mChildren[0].mChildren[0].mIntValue == 40);
			Assert::IsTrue(sharedData2.mRootBar->mChildren[0].mChildren[0].mFloatValue == 4.0f);
			Assert::IsTrue(sharedData2.mRootBar->mChildren[0].mChildren[0].mString == "");
			Assert::IsTrue(sharedData2.mRootBar->mChildren[1].mIntValue == 30);
			Assert::IsTrue(sharedData2.mRootBar->mChildren[1].mFloatValue == 3.0f);
			Assert::IsTrue(sharedData2.mRootBar->mChildren[1].mString == "Bar String 3!");

			Assert::IsTrue(*(sharedData1.mRootBar) == *(sharedData2.mRootBar));

			Assert::ExpectException<std::exception>([&parseMaster]{parseMaster.ParseFromFile("What");});
		}

		TEST_METHOD(XmlParseFromString)
		{
			CREATE_ROOT_BAR

			static const char* xmlString = "<Bar intValue=\"10\" floatValue=\"1.0f\">Bar String 1!<Bar intValue = \"20\" floatValue = \"2.0f\">Bar String 2!<Bar intValue = \"40\" floatValue = \"4.0f\" / >< / Bar><Bar intValue = \"30\" floatValue = \"3.0f\">Bar String 3!< / Bar>< / Bar>";
			XmlParseMaster parseMaster;
			BarSharedData sharedData1;
			BarParseHelper barParseHelper;

			parseMaster.SetSharedData(&sharedData1);
			parseMaster.AddHelper(barParseHelper);

			parseMaster.ParseFromFile("../../../files/BarTestAttributes.xml");
			WriteParseResults(sharedData1, "StringBarTestResults.txt");

			Assert::IsTrue(sharedData1.mRootBar->mIntValue == 10);
			Assert::IsTrue(sharedData1.mRootBar->mFloatValue == 1.0f);
			Assert::IsTrue(sharedData1.mRootBar->mString == "Bar String 1!");
			Assert::IsTrue(sharedData1.mRootBar->mChildren[0].mIntValue == 20);
			Assert::IsTrue(sharedData1.mRootBar->mChildren[0].mFloatValue == 2.0f);
			Assert::IsTrue(sharedData1.mRootBar->mChildren[0].mString == "Bar String 2!");
			Assert::IsTrue(sharedData1.mRootBar->mChildren[0].mChildren[0].mIntValue == 40);
			Assert::IsTrue(sharedData1.mRootBar->mChildren[0].mChildren[0].mFloatValue == 4.0f);
			Assert::IsTrue(sharedData1.mRootBar->mChildren[0].mChildren[0].mString == "");
			Assert::IsTrue(sharedData1.mRootBar->mChildren[1].mIntValue == 30);
			Assert::IsTrue(sharedData1.mRootBar->mChildren[1].mFloatValue == 3.0f);
			Assert::IsTrue(sharedData1.mRootBar->mChildren[1].mString == "Bar String 3!");
		}

#pragma endregion

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XmlParseMasterTest::sStartMemState;
}
