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
									 const char* data,
									 std::int32_t length);

		virtual IXmlParseHelper* Clone() = 0;
	};
}
