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

		TEST_METHOD(GeneralParseTest)
		{
			XmlParseMaster parseMaster;
			BarSharedData sharedData;
			BarParseHelper barParseHelper;

			parseMaster.SetSharedData(&sharedData);
			parseMaster.AddHelper(barParseHelper);

			parseMaster.ParseFromFile("C:/Users/mholtkamp/Desktop/barTest.xml");
			WriteParseResults(sharedData, "results.txt");
			__nop();
		}



	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XmlParseMasterTest::sStartMemState;
}
