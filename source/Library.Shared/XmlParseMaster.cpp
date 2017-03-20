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
		mParseHelpers.Remove(mParseHelpers.Find(&helper));
	}

	void XmlParseMaster::Parse(const char* buffer,
							   std::int32_t length,
							   bool isFinal)
	{
		for (IXmlParseHelper* helper : mParseHelpers)
		{
			if (helper != nullptr)
			{
				helper->Initialize();
			}
		}

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

		RecreateXmlParser();

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
					if (helper->CharDataHandler(sharedData, charString, length))
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

	void XmlParseMaster::RecreateXmlParser()
	{
		assert(mParser != nullptr);

		XML_ParserFree(mParser);
		mParser = nullptr;

		mParser = XML_ParserCreate(nullptr);

		assert(mParser != nullptr);
	}
}
