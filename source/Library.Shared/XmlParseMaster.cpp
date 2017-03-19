#include "XmlParseMaster.h"
#include "expat.h"
#include <assert.h>

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
	}

	void XmlParseMaster::SharedData::SetXmlParseMaster(XmlParseMaster* parseMaster)
	{
		mParseMaster = parseMaster;
	}

	XmlParseMaster* XmlParseMaster::SharedData::GetXmlParseMaster()
	{
		return mParseMaster;
	}

	const XmlParseMaster* XmlParseMaster::SharedData::GetXmlParseMaster()
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
			mSharedData = nulltr;

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
	}

	void XmlParseMaster::AddHelper(IXmlParseHelper& helper)
	{
		mParseHelpers.PushBack(&helper);
	}

	void XmlParseMaster::RemoveHelper(IXmlParseHelper& helper)
	{
		mParseHelpers.Remove(&helper);
	}


}
