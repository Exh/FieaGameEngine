#include "pch.h"

using namespace FieaGameEngine;

#pragma region BarSharedData

BarSharedData::BarSharedData() :
	mRootBar(nullptr),
	mCurrentBar(nullptr)
{

}

BarSharedData::~BarSharedData()
{
	if (mRootBar != nullptr)
	{
		delete mRootBar;
		mRootBar = nullptr;
	}
}

#pragma endregion

#pragma region BarParseHelper

BarParseHelper::BarParseHelper()
{

}

BarParseHelper::~BarParseHelper()
{

}

void BarParseHelper::Initialize()
{

}

bool BarParseHelper::StartElementHandler(void* userData,
										 const std::string& elementName,
										 const HashMap<std::string, std::string>& attributes)
{
	
	XmlParseMaster::SharedData* sharedData = reinterpret_cast<XmlParseMaster::SharedData*>(userData);
	BarSharedData* barSharedData = nullptr;

	if (sharedData != nullptr)
	{
		barSharedData = sharedData->As<BarSharedData>();
	}

	if (barSharedData != nullptr &&
		elementName == "Bar")
	{
		Bar* parent = barSharedData->mCurrentBar;

		if (parent != nullptr)
		{
			Bar newBar;
			newBar.mParent = parent;
			newBar.mIntValue = std::stoi(attributes["intValue"]);
			newBar.mFloatValue = std::stof(attributes["floatValue"]);
			parent->mChildren.PushBack(newBar);

			barSharedData->mCurrentBar = &(parent->mChildren[parent->mChildren.Size() - 1]);
		}
		else
		{
			assert(barSharedData->mRootBar == nullptr);

			barSharedData->mRootBar = new Bar();
			barSharedData->mCurrentBar= barSharedData->mRootBar;

			barSharedData->mRootBar->mIntValue = std::stoi(attributes["intValue"]);
			barSharedData->mRootBar->mFloatValue = std::stof(attributes["floatValue"]);
		}

		return true;
	}

	return false;
}

bool BarParseHelper::EndElementHandler(void* userData,
									   const std::string& elementName)
{
	XmlParseMaster::SharedData* sharedData = reinterpret_cast<XmlParseMaster::SharedData*>(userData);
	BarSharedData* barSharedData = nullptr;

	if (sharedData != nullptr)
	{
		barSharedData = sharedData->As<BarSharedData>();
	}

	if (barSharedData != nullptr &&
		elementName == "Bar")
	{
		assert(barSharedData->mCurrentBar != nullptr);

		if (barSharedData->mCurrentBar->mString.size() > 0U)
		{
			barSharedData->mCurrentBar->mString = IXmlParseHelper::TrimCharData(barSharedData->mCurrentBar->mString);
		}

		barSharedData->mCurrentBar = barSharedData->mCurrentBar->mParent;

		return true;
	}

	return false;
}

bool BarParseHelper::CharDataHandler(void* userData,
									 const std::string& charData)
{
	XmlParseMaster::SharedData* sharedData = reinterpret_cast<XmlParseMaster::SharedData*>(userData);
	BarSharedData* barSharedData = nullptr;

	if (sharedData != nullptr)
	{
		barSharedData = sharedData->As<BarSharedData>();
	}

	if (barSharedData != nullptr &&
		barSharedData->mCurrentBar != nullptr)
	{
		barSharedData->mCurrentBar->mString.append(charData);
		return true;
	}

	return false;
}

IXmlParseHelper* BarParseHelper::Clone()
{
	return new BarParseHelper();
}

#pragma endregion