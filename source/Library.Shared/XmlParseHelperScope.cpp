#include "pch.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ScopeSharedData)

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
			if (elementName == "Scope")
			{
				HandleScope(*scopeSharedData, attributes);
				return true;
			}
			else if (elementName == "Integer")
			{
				HandleInteger(*scopeSharedData, attributes);
				return true;
			}
			else if (elementName == "Float")
			{
				HandleFloat(*scopeSharedData, attributes);
				return true;
			}
			else if (elementName == "Vector")
			{
				HandleVector(*scopeSharedData, attributes);
				return true;
			}
			else if (elementName == "Matrix")
			{
				HandleMatrix(*scopeSharedData, attributes);
				return true;
			}
			else if (elementName == "String")
			{
				HandleString(*scopeSharedData, attributes);
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
			elementName == "Scope")
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

	void XmlParseHelperScope::HandleInteger(ScopeSharedData& scopeSharedData,
		const HashMap<std::string, std::string>& attributes)
	{
		Datum& TargetDatum = FetchDatum(scopeSharedData, attributes);
		TargetDatum.SetType(DatumType::Integer);
		TargetDatum.PushBackFromString(attributes["value"]);
	}

	void XmlParseHelperScope::HandleFloat(ScopeSharedData& scopeSharedData,
		const HashMap<std::string, std::string>& attributes)
	{
		Datum& TargetDatum = FetchDatum(scopeSharedData, attributes);
		TargetDatum.SetType(DatumType::Float);
		TargetDatum.PushBackFromString(attributes["value"]);
	}

	void XmlParseHelperScope::HandleVector(ScopeSharedData& scopeSharedData,
		const HashMap<std::string, std::string>& attributes)
	{
		Datum& TargetDatum = FetchDatum(scopeSharedData, attributes);
		TargetDatum.SetType(DatumType::Vector);
		TargetDatum.PushBackFromString(attributes["value"]);
	}

	void XmlParseHelperScope::HandleMatrix(ScopeSharedData& scopeSharedData,
		const HashMap<std::string, std::string>& attributes)
	{
		Datum& TargetDatum = FetchDatum(scopeSharedData, attributes);
		TargetDatum.SetType(DatumType::Matrix);
		TargetDatum.PushBackFromString(attributes["value"]);
	}

	void XmlParseHelperScope::HandleString(ScopeSharedData& scopeSharedData,
		const HashMap<std::string, std::string>& attributes)
	{
		Datum& TargetDatum = FetchDatum(scopeSharedData, attributes);
		TargetDatum.SetType(DatumType::String);
		TargetDatum.PushBackFromString(attributes["value"]);
	}

	IXmlParseHelper* XmlParseHelperScope::Clone() const
	{
		return new XmlParseHelperScope();
	}
}
