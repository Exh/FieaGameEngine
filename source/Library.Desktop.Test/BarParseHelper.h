#pragma once

#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"
#include "Bar.h"
#include "SList.h"
#include <string>

using namespace FieaGameEngine;

class BarSharedData final : public FieaGameEngine::XmlParseMaster::SharedData
{
public:

	BarSharedData();
	~BarSharedData();

	virtual void Initialize() override;

	virtual SharedData* Clone() const override;
	
	Bar* mRootBar;
	Bar* mCurrentBar;

protected:

	BarSharedData(const BarSharedData& rhs);
};

class BarParseHelper final : public FieaGameEngine::IXmlParseHelper
{
public:

	BarParseHelper();
	~BarParseHelper();

	BarParseHelper(const BarParseHelper& rhs) = delete;
	BarParseHelper& operator=(const BarParseHelper& rhs) = delete;

	virtual void Initialize() override;

	virtual bool StartElementHandler(XmlParseMaster::SharedData& sharedData,
									 const std::string& elementName,
									 const FieaGameEngine::HashMap<std::string, std::string>& attributes) override;

	virtual bool EndElementHandler(XmlParseMaster::SharedData& sharedData,
								   const std::string& elementName) override;

	virtual bool CharDataHandler(XmlParseMaster::SharedData& sharedData,
								 const std::string& charData) override;

	virtual IXmlParseHelper* Clone() const override;

private:

	void AssignAttributes(Bar& bar, const FieaGameEngine::HashMap<std::string, std::string>& attributes);

	std::string mCharData;
	FieaGameEngine::SList<std::uint32_t> mBarDepthStack;
};
