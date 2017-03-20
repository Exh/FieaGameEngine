#pragma once

#include <string>
#include "HashMap.h"

namespace FieaGameEngine
{
	class IXmlParseHelper
	{
	public:

		virtual ~IXmlParseHelper();

		void Initialize();

		bool StartElementHandler(void* sharedData,
								 const std::string& elementName,
								 const HashMap<std::string, std::string>& attributes);

		bool EndElementHandler(void* sharedData,
							   const std::string& elementName);

		bool CharDataHandler(void* sharedData,
							 const char* data,
							 std::int32_t length);

		virtual IXmlParseHelper* Clone() = 0;
	};
}
