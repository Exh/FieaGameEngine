#pragma once

#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"
#include "World.h"

namespace FieaGameEngine
{

	//class WorldSharedData : public XmlParseMaster::SharedData
	//{
	//	RTTI_DECLARATIONS(WorldSharedData, XmlParseMaster::SharedData)

	//public:

	//	WorldSharedData();

	//	virtual WorldSharedData() = default;

	//	virtual SharedData* Clone() const override;

	//	virtual void Initialize() override;

	//public:

	//	World* mWorld;

	//};

	class XmlParseHelperWorld : public IXmlParseHelper
	{
	
	public:

		XmlParseHelperWorld();

		virtual ~XmlParseHelperWorld() = default;

		/** Override of IXmlParseHelper interface's StartElementHandler method. This method will
		handle World/Sector/Entity tags.
		@param sharedData A reference to the currently used shared data by the parse master.
		@param elementName A string containing the name of the current element being processed.
		@param attributes A map of name, value pairs mapping to the received XML element's attributes.
		@throw exception If there are missing "name" or "value" attributes for Datum values.
		@throw exception If non-root scope has no "name" attribute.
		@return true if the element was handled by this method. */
		virtual bool StartElementHandler(XmlParseMaster::SharedData& sharedData,
										 const std::string& elementName,
										 const HashMap<std::string, std::string>& attributes) override;

		/** Override of IXmlParseHelper interface's EndElementHandler method. This method will
		handle World/Sector/Entity tags.
		@param sharedData A reference to the currently used shared data by the parse master.
		@param elementName A string containing the name of the current element being processed.
		@return true if the element was handled by this method. */
		virtual bool EndElementHandler(XmlParseMaster::SharedData& sharedData,
									   const std::string& elementName) override;

		/** Makes a clone of this parse helper in its current state.
		@return A pointer to the newly allocated parse helper.*/
		virtual IXmlParseHelper* Clone() const override;

	private:

		void HandleWorld(ScopeSharedData& scopeSharedData,
						 const HashMap<std::string, std::string>& attributes);

		void HandleSector(ScopeSharedData& scopeSharedData,
						  const HashMap<std::string, std::string>& attributes);

		void HandleEntity(ScopeSharedData& scopeSharedData,
						  const HashMap<std::string, std::string>& attributes);

		void HandleAction(ScopeSharedData& scopeSharedData,
						  const HashMap<std::string, std::string>& attributes);

		//void HandleActionIf(ScopeSharedData& scopeSharedData,
		//					const HashMap<std::string, std::string>& attributes);
	
	private:

		const static std::string sWorldTag;
		const static std::string sSectorTag;
		const static std::string sEntityTag;
		const static std::string sActionTag;
	};
}