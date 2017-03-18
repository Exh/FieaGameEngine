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

		bool StartElementHandler(const std::string& elementName,
								 HashMap<std::string, std::string>& attributes);

		bool EndElementHandler(const std::string& elementName);

		bool CharDataHandler(const char* data,
							 std::int32_t length);

		virtual IXmlParseHelper& Clone() = 0;
	};
}
