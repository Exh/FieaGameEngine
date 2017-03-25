#pragma once

#include <string>
#include "HashMap.h"
#include "XmlParseMaster.h"

namespace FieaGameEngine
{
	class IXmlParseHelper
	{
	public:

		/** Virtual Destructor. Does not do anything itself.*/
		virtual ~IXmlParseHelper();

		/** Called before an XML parsing sequence begins.*/
		virtual void Initialize();

		/** A callback to handle the start of an XML element tag.
			@param userData The SharedData pointer that has been assigned
				to the XmlParseMaster from which this callback was invoked.
			@param elementName The name of the XML element.
			@param attributes A Hashmap of string, string pairs, where the first
				string is the key of the attribute, and the second string is its 
				assigned value.
			@bool True if the element could be handled. False otherwise.*/
		virtual bool StartElementHandler(XmlParseMaster::SharedData& sharedData,
										 const std::string& elementName,
										 const HashMap<std::string, std::string>& attributes) = 0;

		/** A callback to handle the end of an XML element tag.
			@param sharedData The SharedData pointer that has been assigned
				to the XmlParseMaster from which this callback was invoked.
			@param elementName The name of the XML element.
			@bool True if the element could be handled. False otherwise.*/
		virtual bool EndElementHandler(XmlParseMaster::SharedData& sharedData,
									   const std::string& elementName) = 0;
		/** A callback to handle any Character data between the start and 
			end tags of an element.
			@param sharedData The SharedData pointer that has been assigned
				to the XmlParseMaster from which this callback was invoked.
			@param charData The string of character data.
			@bool True if the character data could be handled. False otherwise.*/
		virtual bool CharDataHandler(XmlParseMaster::SharedData& sharedData,
									 const std::string& charData);

		/** Clones the helper. Must be implemented by any derived classes.
			@return A Pointer to the new clone as an IXmlParseHelper.*/
		virtual IXmlParseHelper* Clone() const = 0;

	protected:

		static std::string TrimCharData(const std::string& charData);
	};
}
