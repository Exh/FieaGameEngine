#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

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
