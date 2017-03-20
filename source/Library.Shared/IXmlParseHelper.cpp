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
										  const std::string& charData)
	{
		userData;
		charData;

		return false;
	}

	std::string IXmlParseHelper::TrimCharData(const std::string& charData)
	{
		size_t stringBegin = charData.find_first_not_of(" \n\r\t");
		size_t stringEnd = charData.find_last_not_of(" \n\r\t") + 1;

		if (stringBegin == std::string::npos)
		{
			stringBegin = 0U;
		}

		if (stringEnd == std::string::npos)
		{
			stringEnd = 0U;
		}

		if (stringBegin < stringEnd)
		{
			return charData.substr(stringBegin, stringEnd - stringBegin);
		}
		else
		{
			return std::string();
		}
		
	}
}
