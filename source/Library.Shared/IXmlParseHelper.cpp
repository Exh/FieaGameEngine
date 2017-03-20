#include "pch.h"

namespace FieaGameEngine
{
	IXmlParseHelper::~IXmlParseHelper()
	{

	}

	void IXmlParseHelper::Initialize()
	{
		mDepth = nullptr;
	}

	bool IXmlParseHelper::StartElementHandler(void* userData,
											  const std::string& elementName,
											  const HashMap<std::string, std::string>& attributes)
	{
		sharedData;
		elementName;
		attributes;

		return false;
	}

	bool IXmlParseHelper::EndElementHandler(void* userData,
											const std::string& elementName)
	{
		sharedData;
		elementName;

		return false;
	}

	bool IXmlParseHelper::CharDataHandler(void* userData,
										  const char* data,
										  std::int32_t length)
	{
		sharedData;
		data;
		length;

		return false;
	}
}
