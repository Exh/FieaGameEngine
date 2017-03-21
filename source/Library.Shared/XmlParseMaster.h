#pragma once

#include <cstdint>
#include "IXmlParseHelper.h"
#include "RTTI.h"

struct XML_ParserStruct;
typedef XML_ParserStruct* XML_Parser;

#ifdef XML_UNICODE     /* Information is UTF-16 encoded. */
#ifdef XML_UNICODE_WCHAR_T
typedef wchar_t XML_Char;
typedef wchar_t XML_LChar;
#else
typedef unsigned short XML_Char;
typedef char XML_LChar;
#endif /* XML_UNICODE_WCHAR_T */
#else                  /* Information is UTF-8 encoded. */
typedef char XML_Char;
typedef char XML_LChar;
#endif /* XML_UNICODE */

namespace FieaGameEngine
{
	class XmlParseMaster final
	{
		public:

		class SharedData : public RTTI
		{
			RTTI_DECLARATIONS(SharedData, RTTI)

		public:

			/** Default constructor. Will have no association with an XmlParseMaster initially.*/
			SharedData();

			/** Destructor. Currently does nothing. */
			virtual ~SharedData();

			/** Initializes this user data by putting it in a state that is ready to store parsed objects
			from xml.*/
			virtual void Initialize();

			/** Works as a virtual constructor. Clone returns a copy of this SharedData, except it
				can be used with a new ParseMaster. The clone is ready to parse a new file even though
				it will retain its state.
				@return The new clone as a SharedData pointer.*/
			virtual SharedData* Clone() const = 0;

			/** Resets this into a state where it can begin interpreting new xml.*/
			virtual void Reset();

			/** Default constructor. Will have no association with an XmlParseMaster initially.
				@param parseMaster The XmlParseMaster object that this SharedData will no communicate with.*/
			void SetXmlParseMaster(XmlParseMaster* parseMaster);

			/** Gets the currently assigned parse master.
				@return The currently assigned parse master.*/
			XmlParseMaster* GetXmlParseMaster();

			/** Gets the currently assigned parse master.
				@return The currently assigned parse master.*/
			const XmlParseMaster* GetXmlParseMaster() const;

			/** Increments the depth counter on this SharedData instance. The higher the 
				depth, the more nested the xml parsing.*/
			void IncrementDepth();

			/** Decrements the depth counter on this SharedData instance. The higher the 
				depth, the more nested the xml parsing.
				@throw exception If depth is already at 0.*/
			void DecrementDepth();

			/** Gets the current depth.
				@return The current depth.*/
			std::uint32_t Depth();

		protected:

			std::uint32_t mDepth;

			XmlParseMaster* mParseMaster;
		};

		/** Constructor that takes an optional sharedData object to initialize it with.
			SharedData can always be assigned and reassigned later.
			@param sharedData The SharedData instance to use for parsing XML.*/
		explicit XmlParseMaster(SharedData* sharedData = nullptr);

		/** Destructor*/
		~XmlParseMaster();

		XmlParseMaster(const XmlParseMaster& rhs) = delete;
		XmlParseMaster& operator=(const XmlParseMaster& rhs) = delete;

		/** Makes a clone of this XmlParseMaster with copies of all its parse helpers.
			User cannot Add or Remove parse helpers on a cloned XmlParseMaster.
			@return The new clone. */
		XmlParseMaster* Clone() const;

		/** Adds a helper to the parsing chain of responsibility.
			@oaram Reference to the helper to add.
			@throw exception If this XmlParseMaster is cloned.*/
		void AddHelper(IXmlParseHelper& helper);

		/** Removes a previously added helper.
			@param helper Reference to the helper to remove..
			@throw exception If this XmlParseMaster is cloned.*/
		void RemoveHelper(IXmlParseHelper& helper);

		/** Parses an XML file using the currently assigned IXmlParseHelpers.
			Resulting data will be stored in the SharedData object which can be
			retrieved by called GetSharedData().
			@param filename The name of the file to load and parse.
			@throw exception If the file could not be opened.*/
		void ParseFromFile(const char* filename);

		/** Parses an string file using the currently assigned IXmlParseHelpers.
			Resulting data will be stored in the SharedData object which can be
			retrieved by called GetSharedData().
			@throw exception If the file could not be opened.*/
		void ParseFromString(const char* stringArray);

		/** Returns the filename of the file currently being parsed.
			@return File name as a C string.*/
		const char* GetFileName() const;

		/** Returns the currently assigned SharedData instance.
			@return Assigned SharedData instance.*/
		SharedData* GetSharedData();

		/** Returns the currently assigned SharedData instance.
			@return Assigned SharedData instance.*/
		const SharedData* GetSharedData() const;

		/** Returns the currently assigned SharedData instance.
			@param sharedData The new SharedData instance to assign to this XmlParseMaster.*/
		void SetSharedData(SharedData* sharedData);

	private:

		void Parse(const char* buffer,
				   std::int32_t length,
				   bool isFinal);

		static void StartElementHandler(void* userData,
										const XML_Char* elementName,
										const XML_Char** attributes);

		static void EndElementHandler(void* userData,
									  const XML_Char* elementName);

		static void CharDataHandler(void* userData,
									const XML_Char* charString,
									int32_t length);

		static void GenerateAttributeMap(HashMap<std::string, std::string>& attributeMap,
										 const char** attributes);

		void RecreateXmlParser();

	private:

		XML_Parser mParser;
		SharedData* mSharedData;
		bool mCloned;
		const char* mFilename;
		Vector<IXmlParseHelper*> mParseHelpers;
	};
}