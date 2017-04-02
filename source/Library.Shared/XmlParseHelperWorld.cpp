#include "pch.h"

namespace FieaGameEngine
{

	const std::string XmlParseHelperWorld::sWorldTag = "World";
	const std::string XmlParseHelperWorld::sSectorTag = "Sector";
	const std::string XmlParseHelperWorld::sEntityTag = "Entity";

	XmlParseHelperWorld::XmlParseHelperWorld()
	{
	
	}

	IXmlParseHelper* XmlParseHelperWorld::Clone() const
	{
		return new XmlParseHelperWorld();
	}

	bool XmlParseHelperWorld::StartElementHandler(XmlParseMaster::SharedData& sharedData,
												  const std::string& elementName,
												  const HashMap<std::string, std::string>& attributes)
	{
		ScopeSharedData* scopeSharedData = nullptr;
		scopeSharedData = sharedData.As<ScopeSharedData>();

		if (scopeSharedData != nullptr)
		{
			if (elementName == sWorldTag)
			{
				HandleWorld(*scopeSharedData, attributes);
				return true;
			}
			else if (elementName == sSectorTag)
			{
				HandleSector(*scopeSharedData, attributes);
				return true;
			}
			else if (elementName == sEntityTag)
			{
				HandleEntity(*scopeSharedData, attributes);
				return true;
			}
		}

		return false;
	}

	bool XmlParseHelperWorld::EndElementHandler(XmlParseMaster::SharedData& sharedData,
												const std::string& elementName)
	{
		ScopeSharedData* scopeSharedData = nullptr;
		scopeSharedData = sharedData.As<ScopeSharedData>();

		if (scopeSharedData != nullptr &&
			elementName == sSectorTag ||
			elementName == sEntityTag)
		{
			assert(scopeSharedData->Depth() > 1);
			scopeSharedData->mScope = scopeSharedData->mScope->GetParent();

			return true;
		}

		return false;
	}

	void XmlParseHelperWorld::HandleWorld(ScopeSharedData& scopeSharedData,
										  const HashMap<std::string, std::string>& attributes)
	{
		if (scopeSharedData.Depth() != 1)
		{
			throw std::exception("World element found at non-root level.");
		}

		assert(scopeSharedData.mScope == nullptr);

		scopeSharedData.mScope = new World();

		HashMap<std::string, std::string>::Iterator it = attributes.Find(World::KEY_NAME);

		if (it == attributes.end())
		{
			// LOG INFO: Using default world name
		}
		else
		{
			(*scopeSharedData.mScope)[World::KEY_NAME] = (*it).second;
		}
	}

	void XmlParseHelperWorld::HandleSector(ScopeSharedData& scopeSharedData,
										   const HashMap<std::string, std::string>& attributes)
	{
		if (scopeSharedData.mScope == nullptr)
		{
			throw std::exception("World parsing has encountered a Sector, but shared data contains no scope instance.");
		}

		if (!scopeSharedData.mScope->Is(World::TypeIdClass()))
		{
			throw std::exception("Sector element received but parent element is not a world.");
		}

		Sector* sector = static_cast<World*>(scopeSharedData.mScope)->CreateSector();
		
		auto it = attributes.Find(Sector::KEY_NAME);

		if (it == attributes.end())
		{
			// LOG INFO: No Sector name specified in xml file. Using default Sector name.
		}
		else
		{
			sector->SetName((*it).second);
		}

		scopeSharedData.mScope = sector;
	}

	void XmlParseHelperWorld::HandleEntity(ScopeSharedData& scopeSharedData,
										   const HashMap<std::string, std::string>& attributes)
	{
		if (scopeSharedData.mScope == nullptr)
		{
			throw std::exception("World parsing has encountered an Entity, but shared data contains no scope instance.");
		}

		if (!scopeSharedData.mScope->Is(Sector::TypeIdClass()))
		{
			throw std::exception("Entity element received but parent element is not a sector.");
		}

		Sector* sector = static_cast<Sector*>(scopeSharedData.mScope);

		auto it = attributes.Find("class");
		Entity* entity = nullptr;

		if (it != attributes.end())
		{
			entity = sector->CreateEntity((*it).second);
		}
		else
		{
			entity = sector->CreateEntity("Entity");
		}

		it = attributes.Find(Entity::KEY_NAME);

		if (it == attributes.end())
		{
			// LOG INFO: No Sector name specified in xml file. Using default Sector name.
		}
		else
		{
			entity->SetName((*it).second);
		}

		scopeSharedData.mScope = entity;
	}
}
