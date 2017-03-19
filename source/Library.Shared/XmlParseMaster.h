#pragma once

#include <cstdint>
#include "expat.h"
#include "IXmlParseHelper.h"

namespace FieaGameEngine
{

	class XmlParseMaster final
	{
		class SharedData
		{
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

	public:

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

	private:

		XML_Parser mParser;
		SharedData* mSharedData;
		bool mCloned;
		const char* mFilename;
		Vector<IXmlParseHelper*> mParseHelpers;
	};
}