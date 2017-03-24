#pragma once

#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"

namespace FieaGameEngine
{
	class ScopeSharedData : public XmlParseMaster::SharedData
	{
	public:
		Scope* mScope;
	};

	class XmlParseHelperScope : public IXmlParseHelper
	{
	public:

		XmlParseHelperScope();

		virtual ~XmlParseHelperScope();

		virtual bool StartElementHandler(XmlParseMaster::SharedData& sharedData,
			const std::string& elementName,
			const HashMap<std::string, std::string>& attributes) override;

		virtual bool EndElementHandler(XmlParseMaster::SharedData& sharedData,
			const std::string& elementName) override;
	};
}