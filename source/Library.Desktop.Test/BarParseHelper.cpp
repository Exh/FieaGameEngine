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
	delete mRootBar;
	mRootBar = nullptr;
}

void BarSharedData::Initialize()
{
	SharedData::Initialize();

	delete mRootBar;
	mRootBar = nullptr;

	mCurrentBar = nullptr;
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
	IXmlParseHelper::Initialize();
	mCharData.clear();
	mBarDepthStack.Clear();
}

bool BarParseHelper::StartElementHandler(void* userData,
										 const std::string& elementName,
										 const HashMap<std::string, std::string>& attributes)
{
	
	XmlParseMaster::SharedData* sharedData = reinterpret_cast<XmlParseMaster::SharedData*>(userData);
	BarSharedData* barSharedData = nullptr;

	mCharData.clear();

	if (sharedData != nullptr)
	{
		barSharedData = sharedData->As<BarSharedData>();
	}

	if (barSharedData != nullptr &&
		elementName == "Bar")
	{
		Bar* parent = barSharedData->mCurrentBar;
		mBarDepthStack.PushFront(barSharedData->Depth());

		if (parent != nullptr)
		{
			Bar newBar;
			newBar.mParent = parent;

			AssignAttributes(newBar, attributes);
			
			parent->mChildren.PushBack(newBar);

			barSharedData->mCurrentBar = &(parent->mChildren[parent->mChildren.Size() - 1]);
		}
		else
		{
			assert(barSharedData->mRootBar == nullptr);

			barSharedData->mRootBar = new Bar();
			barSharedData->mCurrentBar = barSharedData->mRootBar;

			AssignAttributes(*barSharedData->mRootBar, attributes);
		}

		return true;
	}

	return false;
}

void BarParseHelper::AssignAttributes(Bar& bar, const HashMap<std::string, std::string>& attributes)
{
	if (attributes.ContainsKey("intValue"))
	{
		bar.mIntValue = std::stoi(attributes["intValue"]);
	}

	if (attributes.ContainsKey("floatValue"))
	{
		bar.mFloatValue = std::stof(attributes["floatValue"]);
	}
}

bool BarParseHelper::EndElementHandler(void* userData,
									   const std::string& elementName)
{
	XmlParseMaster::SharedData* sharedData = reinterpret_cast<XmlParseMaster::SharedData*>(userData);
	BarSharedData* barSharedData = nullptr;

	std::string thisCharData = mCharData;
	mCharData.clear();

	if (sharedData != nullptr)
	{
		barSharedData = sharedData->As<BarSharedData>();
	}

	if (barSharedData != nullptr)
	{
		if(elementName == "Bar")
		{
			assert(barSharedData->mCurrentBar != nullptr);

			if (barSharedData->mCurrentBar->mString.size() > 0U)
			{
				barSharedData->mCurrentBar->mString = IXmlParseHelper::TrimCharData(barSharedData->mCurrentBar->mString);
			}

			mBarDepthStack.PopFront();
			barSharedData->mCurrentBar = barSharedData->mCurrentBar->mParent;

			return true;
		}
		else if (elementName == "intValue")
		{
			if (barSharedData->mCurrentBar != nullptr)
			{
				barSharedData->mCurrentBar->mIntValue = std::stoi(thisCharData);
			}

			return true;
		}
		else if (elementName == "floatValue")
		{
			if (barSharedData->mCurrentBar != nullptr)
			{
				barSharedData->mCurrentBar->mFloatValue = std::stof(thisCharData);
			}

			return true;
		}
	}

	return false;
}

bool BarParseHelper::CharDataHandler(void* userData,
									 const std::string& charData)
{
	XmlParseMaster::SharedData* sharedData = reinterpret_cast<XmlParseMaster::SharedData*>(userData);
	BarSharedData* barSharedData = nullptr;

	mCharData.append(charData);

	if (sharedData != nullptr)
	{
		barSharedData = sharedData->As<BarSharedData>();
	}

	if (barSharedData != nullptr &&
		barSharedData->mCurrentBar != nullptr &&
		barSharedData->Depth() == mBarDepthStack.Front())
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
