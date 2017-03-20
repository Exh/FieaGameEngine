#pragma once

#include <string>
#include "HashMap.h"

namespace FieaGameEngine
{
	class IXmlParseHelper
	{
	public:

		virtual ~IXmlParseHelper();

		virtual void Initialize();

		virtual bool StartElementHandler(void* userData,
										 const std::string& elementName,
										 const HashMap<std::string, std::string>& attributes) = 0;

		virtual bool EndElementHandler(void* sharedData,
									   const std::string& elementName) = 0;

		virtual bool CharDataHandler(void* sharedData,
									 const std::string& charData);

		virtual IXmlParseHelper* Clone() = 0;

	protected:

		static std::string TrimCharData(const std::string& charData);
	};
}
