#include "pch.h"

namespace FieaGameEngine
{
#pragma region SharedDataMethods

	RTTI_DEFINITIONS(XmlParseMaster::SharedData)

	XmlParseMaster::SharedData::SharedData() :
		mDepth(0),
		mParseMaster(nullptr)
	{

	}

	XmlParseMaster::SharedData::~SharedData()
	{
	
	}

	void XmlParseMaster::SharedData::Initialize()
	{
		mDepth = 0U;
	}

	void XmlParseMaster::SharedData::Reset()
	{
		mDepth = 0U;
		mParseMaster = nullptr;
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
		if (mDepth == 0)
		{
			throw std::exception("DecrementDepth called when at 0 depth.");
		}

		--mDepth;
	}

	std::uint32_t XmlParseMaster::SharedData::Depth()
	{
		return mDepth;
	}
#pragma endregion

	XmlParseMaster::XmlParseMaster(SharedData* sharedData) :
		mParser(nullptr),
		mSharedData(nullptr),
		mCloned(false),
		mFilename(nullptr)
	{
		mParser = XML_ParserCreate(nullptr);
		assert(mParser != nullptr);

		XML_SetElementHandler(mParser,
							  &XmlParseMaster::StartElementHandler,
							  &XmlParseMaster::EndElementHandler);

		XML_SetCharacterDataHandler(mParser, &XmlParseMaster::CharDataHandler);

		SetSharedData(sharedData);
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
		if (mCloned)
		{
			throw std::exception("Cannot add helper to cloned XmlParseMaster");
		}

		if (mParseHelpers.Find(&helper) != mParseHelpers.end())
		{
			throw std::exception("Cannot add duplicate parse helper to parse master.");
		}

		mParseHelpers.PushBack(&helper);
	}

	void XmlParseMaster::RemoveHelper(IXmlParseHelper& helper)
	{
		if (mCloned)
		{
			throw std::exception("Cannot add helper to cloned XmlParseMaster");
		}

		mParseHelpers.Remove(mParseHelpers.Find(&helper));
	}

	void XmlParseMaster::Parse(const char* buffer,
							   std::int32_t length,
							   bool isFinal)
	{
		Reset();

		XML_Status status = XML_Parse(mParser, buffer, length, isFinal);


		status;
		XML_Error error = XML_GetErrorCode(mParser);
		const char* errorString = XML_ErrorString(error);
		errorString;
	}

	void XmlParseMaster::Reset()
	{
		if (mSharedData != nullptr)
		{
			mSharedData->Initialize();
		}

		for (IXmlParseHelper* helper : mParseHelpers)
		{
			if (helper != nullptr)
			{
				helper->Initialize();
			}
		}

		XML_ParserReset(mParser, nullptr);

		XML_SetElementHandler(mParser,
			&XmlParseMaster::StartElementHandler,
			&XmlParseMaster::EndElementHandler);

		XML_SetCharacterDataHandler(mParser,
			&XmlParseMaster::CharDataHandler);

		SetSharedData(mSharedData);
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
		length = static_cast<std::int32_t>(fread(buffer, 1, length, file));

		Parse(buffer, length, true);

		free(buffer);
		buffer = nullptr;

		fclose(file);
		file = nullptr;
	}

	void XmlParseMaster::ParseFromString(const char* stringArray)
	{
		mFilename = nullptr;

		Parse(stringArray, static_cast<int32_t>(strlen(stringArray)), true);
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
		if (mCloned)
		{
			throw std::exception("Cannot change shared data of cloned XmlParseMaster.");
		}

		assert(mParser != nullptr);
		mSharedData = sharedData;
		XML_SetUserData(mParser, mSharedData);

		if (sharedData != nullptr)
		{
			mSharedData->SetXmlParseMaster(this);
		}
	}

	void XmlParseMaster::StartElementHandler(void* userData,
											 const XML_Char* elementName,
											 const XML_Char** attributes)
	{
		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
		HashMap<std::string, std::string> attributeMap;

		if (sharedData != nullptr)
		{
			sharedData->IncrementDepth();
			Vector<IXmlParseHelper*> parseHelpers = sharedData->GetXmlParseMaster()->mParseHelpers;

			GenerateAttributeMap(attributeMap, attributes);

			for (IXmlParseHelper* helper : parseHelpers)
			{
				if (helper != nullptr)
				{
					if (helper->StartElementHandler(sharedData, elementName, attributeMap))
					{
						break;
					}
				}
			}
		}
	}

	void XmlParseMaster::EndElementHandler(void* userData,
												  const XML_Char* elementName)
	{
		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);

		if (sharedData != nullptr)
		{
			sharedData->DecrementDepth();
			Vector<IXmlParseHelper*> parseHelpers = sharedData->GetXmlParseMaster()->mParseHelpers;

			for (IXmlParseHelper* helper : parseHelpers)
			{
				if (helper != nullptr)
				{
					if (helper->EndElementHandler(sharedData, elementName))
					{
						break;
					}
				}
			}
		}
	}

	void XmlParseMaster::CharDataHandler(void* userData,
												const XML_Char* charString,
												int32_t length)
	{
		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);

		if (sharedData != nullptr)
		{
			Vector<IXmlParseHelper*> parseHelpers = sharedData->GetXmlParseMaster()->mParseHelpers;

			for (IXmlParseHelper* helper : parseHelpers)
			{
				if (helper != nullptr)
				{
					if (helper->CharDataHandler(sharedData, std::string(charString, length)))
					{
						break;
					}
				}
			}
		}
	}

	void XmlParseMaster::GenerateAttributeMap(HashMap<std::string, std::string>& attributeMap,
													  const char** attributes)
	{
		assert(attributes != nullptr);

		for (std::int32_t i = 0; attributes[i] != nullptr; i += 2)
		{
			attributeMap.Insert(std::pair<std::string, std::string>(attributes[i], attributes[i+1]));
		}
	}
}
