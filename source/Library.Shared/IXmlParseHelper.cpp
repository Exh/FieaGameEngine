#include "pch.h"

namespace FieaGameEngine
{
	IXmlParseHelper::~IXmlParseHelper()
	{

	}

	void IXmlParseHelper::Initialize()
	{
	
	}

	bool IXmlParseHelper::StartElementHandler(const std::string& elementName,
											  const HashMap<std::string, std::string>& attributes)
	{
		elementName;
		attributes;

		return false;
	}

	bool IXmlParseHelper::EndElementHandler(const std::string& elementName)
	{
		elementName;

		return false;
	}

	bool IXmlParseHelper::CharDataHandler(const char* data,
										  std::int32_t length)
	{
		data;
		length;

		return false;
	}
}
