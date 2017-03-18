#pragma once

#include <cstdint>

namespace FieaGameEngine
{

	class XmlParseMaster final
	{
		class SharedData
		{
			SharedData();

			virtual SharedData& Clone() const;

			void SetXmlParseMaster(XmlParseMaster* parseMaster);

			XmlParseMaster* GetXmlParseMaster();

			const XmlParseMaster* GetXmlParseMaster() const;

			void IncrementDepth();

			void DecrementDepth();

			std::uint32_t Depth();

		protected:

			std::uint32_t mDepth;
		};

	public:

		XmlParseMaster(SharedData& sharedData);
		~XmlParseMaster();

		XmlParseMaster& Clone() const;

		void AddHelper(IXmlParseHelper& helper);

		void RemoveHelper(IXmlParseHelper& helper);

		void Parse(const char* buffer,
				   std::uint32 length,
				   bool lastChunk);

		void ParseFromFile(const char* filename);

		const char* GetFileName() const;

		SharedData* GetSharedData();

		const SharedData* GetSharedData() const;

		void SetSharedData(SharedData* sharedData);

	private:

		//StartElementHandler
		//EndElementHandler
		//CharDataHandler

		SharedData* mSharedData;

		bool mCloned;
	};
}