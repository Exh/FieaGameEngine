#pragma once

#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"
#include "Bar.h"
#include <string>

class BarSharedData final : public FieaGameEngine::XmlParseMaster::SharedData
{
public:

	BarSharedData();
	~BarSharedData();
	
	Bar* mRootBar;
	Bar* mCurrentBar;
};

class BarParseHelper final : public FieaGameEngine::IXmlParseHelper
{
public:

	BarParseHelper();
	~BarParseHelper();

	BarParseHelper(const BarParseHelper& rhs) = delete;
	BarParseHelper& operator=(const BarParseHelper& rhs) = delete;

	virtual void Initialize() override;

	virtual bool StartElementHandler(void* userData,
									 const std::string& elementName,
									 const FieaGameEngine::HashMap<std::string, std::string>& attributes) override;

	virtual bool EndElementHandler(void* userData,
								   const std::string& elementName) override;

	virtual bool CharDataHandler(void* userData,
								 const char* data,
								 std::int32_t length) override;

	virtual IXmlParseHelper* Clone() override;
};
