#include "pch.h"

namespace FieaGameEngine
{
	IXmlParseHelper::~IXmlParseHelper()
	{

	}

	void IXmlParseHelper::Initialize()
	{

	}

	bool IXmlParseHelper::StartElementHandler(void* userData,
											  const std::string& elementName,
											  const HashMap<std::string, std::string>& attributes)
	{
		userData;
		elementName;
		attributes;

		return false;
	}

	bool IXmlParseHelper::EndElementHandler(void* userData,
											const std::string& elementName)
	{
		userData;
		elementName;

		return false;
	}

	bool IXmlParseHelper::CharDataHandler(void* userData,
										  const char* data,
										  std::int32_t length)
	{
		userData;
		data;
		length;

		return false;
	}
}
