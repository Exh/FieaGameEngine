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

			SharedData();

			virtual ~SharedData();

			virtual SharedData* Clone() const;

			void SetXmlParseMaster(XmlParseMaster* parseMaster);

			XmlParseMaster* GetXmlParseMaster();

			const XmlParseMaster* GetXmlParseMaster() const;

			void IncrementDepth();

			void DecrementDepth();

			std::uint32_t Depth();

		protected:

			std::uint32_t mDepth;

			XmlParseMaster* mParseMaster;
		};

		explicit XmlParseMaster(SharedData* sharedData = nullptr);
		~XmlParseMaster();

		XmlParseMaster(const XmlParseMaster& rhs) = delete;
		XmlParseMaster& operator=(const XmlParseMaster& rhs) = delete;

		XmlParseMaster* Clone() const;

		void AddHelper(IXmlParseHelper& helper);

		void RemoveHelper(IXmlParseHelper& helper);

		void Parse(const char* buffer,
				   std::int32_t length,
				   bool isFinal);

		void ParseFromFile(const char* filename);

		const char* GetFileName() const;

		SharedData* GetSharedData();

		const SharedData* GetSharedData() const;

		void SetSharedData(SharedData* sharedData);

	private:

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