#include "pch.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ScopeSharedData)

	std::string XmlParseHelperScope::sScopeTag("Scope");
	std::string XmlParseHelperScope::sIntegerTag("Integer");
	std::string XmlParseHelperScope::sFloatTag("Float");
	std::string XmlParseHelperScope::sVectorTag("Vector");
	std::string XmlParseHelperScope::sMatrixTag("Matrix");
	std::string XmlParseHelperScope::sStringTag("String");

	ScopeSharedData::ScopeSharedData() :
		mScope(nullptr)
	{
	
	}

	ScopeSharedData::~ScopeSharedData()
	{
		delete mScope;
		mScope = nullptr;
	}

	void ScopeSharedData::Initialize()
	{
		XmlParseMaster::SharedData::Initialize();
		
		delete mScope;
		mScope = nullptr;
	}

	XmlParseMaster::SharedData* ScopeSharedData::Clone() const
	{
		ScopeSharedData* clone = new ScopeSharedData();
		
		if (mScope != nullptr)
		{
			clone->mScope = new Scope(*mScope);
		}

		return clone;
	}

	Scope* ScopeSharedData::SnatchScope()
	{
		Scope* snatchedScope = mScope;
		mScope = nullptr;
		return snatchedScope;
	}

	XmlParseHelperScope::XmlParseHelperScope()
	{

	}

	XmlParseHelperScope::~XmlParseHelperScope()
	{

	}

	bool XmlParseHelperScope::StartElementHandler(XmlParseMaster::SharedData& sharedData,
												  const std::string& elementName,
												  const HashMap<std::string, std::string>& attributes)
	{
		ScopeSharedData* scopeSharedData = nullptr;
		scopeSharedData = sharedData.As<ScopeSharedData>();

		if (scopeSharedData != nullptr)
		{
			if (elementName == sScopeTag)
			{
				HandleScope(*scopeSharedData, attributes);
				return true;
			}
			else if (elementName == sIntegerTag)
			{
				HandleValue(*scopeSharedData, attributes, DatumType::Integer);
				return true;
			}
			else if (elementName == sFloatTag)
			{
				HandleValue(*scopeSharedData, attributes, DatumType::Float);
				return true;
			}
			else if (elementName == sVectorTag)
			{
				HandleValue(*scopeSharedData, attributes, DatumType::Vector);
				return true;
			}
			else if (elementName == sMatrixTag)
			{
				HandleValue(*scopeSharedData, attributes, DatumType::Matrix);
				return true;
			}
			else if (elementName == sStringTag)
			{
				HandleValue(*scopeSharedData, attributes, DatumType::String);
				return true;
			}
		}

		return false;
	}

	bool XmlParseHelperScope::EndElementHandler(XmlParseMaster::SharedData& sharedData,
												const std::string& elementName)
	{
		ScopeSharedData* scopeSharedData = nullptr;
		scopeSharedData = sharedData.As<ScopeSharedData>();

		if (scopeSharedData != nullptr &&
			elementName == sScopeTag)
		{
			if (scopeSharedData->Depth() > 1)
			{
				scopeSharedData->mScope = scopeSharedData->mScope->GetParent();
			}
			return true;
		}

		return false;
	}

	Datum& XmlParseHelperScope::FetchDatum(ScopeSharedData& scopeSharedData,
		const HashMap<std::string, std::string>& attributes)
	{
		if (attributes.Find("name") == attributes.end())
		{
			throw std::exception("Name attribute key missing.");
		}

		if (attributes.Find("value") == attributes.end())
		{
			throw std::exception("Value attribute key missing.");
		}

		 return (*scopeSharedData.mScope)[attributes["name"]];
	}

	void XmlParseHelperScope::HandleScope(ScopeSharedData& scopeSharedData,
										  const HashMap<std::string, std::string>& attributes)
	{

		if (scopeSharedData.Depth() == 1)
		{
			if (scopeSharedData.mScope != nullptr)
			{
				throw std::exception("Scope shared data already has a scope.");
			}

			scopeSharedData.mScope = new Scope();
		}
		else
		{
			if (attributes.Find("name") == attributes.end())
			{
				throw std::exception("Non-root scope has no name attribute.");
			}

			Scope& newScope = scopeSharedData.mScope->AppendScope(attributes["name"]);
			scopeSharedData.mScope = &newScope;
		}
	}

	void XmlParseHelperScope::HandleValue(ScopeSharedData& scopeSharedData,
										  const HashMap<std::string, std::string>& attributes,
										  DatumType type)
	{
		Datum& TargetDatum = FetchDatum(scopeSharedData, attributes);
		TargetDatum.SetType(type);
		if (TargetDatum.IsExternal())
		{
			if (TargetDatum.Size() > 0)
			{
				TargetDatum.SetFromString(attributes["value"]);
			}
		}
		else
		{
			TargetDatum.PushBackFromString(attributes["value"]);
		}
	}

	IXmlParseHelper* XmlParseHelperScope::Clone() const
	{
		return new XmlParseHelperScope();
	}
}
