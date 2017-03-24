#include "pch.h"

namespace FieaGameEngine
{
	XmlParseHelperScope::XmlParseHelperScope()
	{

	}

	XmlParseHelperScope::~XmlParseHelperScope()
	{

	}

	bool XmlParseHelperScope::StartElementHandler(XmlParseMaster::SharedData& sharedData,
		const std::string& elementName,
		const HashMap<std::string, std::string>& attributes)
	{
		sharedData;
		elementName;
		attributes;

		return false;
	}

	bool XmlParseHelperScope::EndElementHandler(XmlParseMaster::SharedData& sharedData,
		const std::string& elementName)
	{
		sharedData;
		elementName;

		return false;
	}
}