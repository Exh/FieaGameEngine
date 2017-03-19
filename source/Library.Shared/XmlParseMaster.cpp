#include "pch.h"

namespace FieaGameEngine
{

#pragma region SharedDataMethods

	XmlParseMaster::SharedData::SharedData() :
		mDepth(0),
		mParseMaster(nullptr)
	{

	}

	XmlParseMaster::SharedData::~SharedData()
	{
	
	}

	XmlParseMaster::SharedData* XmlParseMaster::SharedData::Clone() const
	{
		SharedData* clone = new SharedData();
		clone->mDepth = 0;
		clone->mParseMaster = nullptr;

		return clone;
	}

	void XmlParseMaster::SharedData::SetXmlParseMaster(XmlParseMaster* parseMaster)
	{
		mParseMaster = parseMaster;
	}

	XmlParseMaster* XmlParseMaster::SharedData::GetXmlParseMaster()
	{
		return mParseMaster;
	}

	const XmlParseMaster* XmlParseMaster::SharedData::GetXmlParseMaster() const
	{
		return mParseMaster;
	}

	void XmlParseMaster::SharedData::IncrementDepth()
	{
		++mDepth;
	}

	void XmlParseMaster::SharedData::DecrementDepth()
	{
		--mDepth;
	}

	std::uint32_t XmlParseMaster::SharedData::Depth()
	{
		return mDepth;
	}
#pragma endregion

	XmlParseMaster::XmlParseMaster(SharedData* sharedData) :
		mParser(nullptr),
		mSharedData(sharedData),
		mCloned(false),
		mFilename(nullptr)
	{
		mParser = XML_ParserCreate(nullptr);
		assert(mParser != nullptr);

		XML_SetElementHandler(mParser,
							  &XmlParseMaster::StartElementHandler,
							  &XmlParseMaster::EndElementHandler);

		XML_SetCharacterDataHandler(mParser, &XmlParseMaster::CharDataHandler);

		XML_SetUserData(mParser, sharedData);
	}

	XmlParseMaster::~XmlParseMaster()
	{
		if (mCloned)
		{
			delete mSharedData;
			mSharedData = nullptr;

			for (IXmlParseHelper* helper : mParseHelpers)
			{
				delete helper;
				helper = nullptr;
			}
		}

		XML_ParserFree(mParser);
		mParser = nullptr;
	}

	XmlParseMaster* XmlParseMaster::Clone() const
	{
		XmlParseMaster* clone = new XmlParseMaster();

		// Flag the new xml parser as a clone so that it cleans up 
		// its parse helpers and its SharedData.
		clone->mCloned = true;

		if (mSharedData != nullptr)
		{
			clone->mSharedData = mSharedData->Clone();
			clone->mSharedData->SetXmlParseMaster(clone);
		}

		for (IXmlParseHelper* helper : mParseHelpers)
		{
			if (helper != nullptr)
			{
				clone->mParseHelpers.PushBack(helper->Clone());
			}
		}

		return clone;
	}

	void XmlParseMaster::AddHelper(IXmlParseHelper& helper)
	{
		mParseHelpers.PushBack(&helper);
	}

	void XmlParseMaster::RemoveHelper(IXmlParseHelper& helper)
	{
		mParseHelpers.Remove(&helper);
	}

	void XmlParseMaster::Parse(const char* buffer,
							   std::int32_t length,
							   bool isFinal)
	{
		XML_Parse(mParser, buffer, length, isFinal);
	}

	void XmlParseMaster::ParseFromFile(const char* filename)
	{
		assert(filename != nullptr);

		FILE* file = nullptr;
		fopen_s(&file, filename, "r");

		if (file == nullptr)
		{
			throw std::exception("Invalid file path.");
		}

		mFilename = filename;

		fseek(file, 0, SEEK_END);
		std::int32_t length = ftell(file);
		fseek(file, 0, SEEK_SET);

		char* buffer = reinterpret_cast<char*>(malloc(length));
		fread(buffer, 1, length, file);

		Parse(buffer, length, true);

		free(buffer);
		buffer = nullptr;

		fclose(file);
		file = nullptr;
	}

	const char* XmlParseMaster::GetFileName() const
	{
		return mFilename;
	}

	XmlParseMaster::SharedData* XmlParseMaster::GetSharedData()
	{
		return mSharedData;
	}

	const XmlParseMaster::SharedData* XmlParseMaster::GetSharedData() const
	{
		return mSharedData;	
	}

	void XmlParseMaster::SetSharedData(SharedData* sharedData)
	{
		mSharedData = sharedData;
	}
}
