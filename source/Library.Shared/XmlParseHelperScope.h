#pragma once

#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"
#include <functional>

namespace FieaGameEngine
{

	class ScopeSharedData : public XmlParseMaster::SharedData
	{
		RTTI_DECLARATIONS(ScopeSharedData, XmlParseMaster::SharedData)

	public:

		/** Contructor that initializes the scope pointer member to null.*/
		ScopeSharedData();

		/** Destructor that will destroy its associated scope. To retrieve the scope
		from the ScopeShareData object, use SnatchScope() to ensure that ScopeSharedData's
		scope pointer is set to null.*/
		virtual ~ScopeSharedData();

		/** Makes a clone of this data. If the scope pointer is not null, a new scope 
		will be allocated and thus the returned SharedData will contain a deep copy of this
		ScopeSharedData's associated scope.
		@return The cloned ScopeSharedData object.*/
		virtual SharedData* Clone() const override;

		/** Initializes the object's data to be in a parse-ready state. Specifically, this will
		delete mScope and null out its value.*/
		virtual void Initialize() override;

		/** Returns the currently held scope pointer and nulls out mScope. This method will put
		the responsibility of deleting the scope to the caller.
		@return The currently held scope.*/
		Scope* SnatchScope();

	public:

		/** The scope created after parsing am xml file with a scope tag. */
		Scope* mScope;
	};

	class XmlParseHelperScope : public IXmlParseHelper
	{
	public:

		/** Constructor. Currently does nothing. */
		XmlParseHelperScope();

		/** Destructor. Currently does nothing. */
		virtual ~XmlParseHelperScope();

		/** Override of IXmlParseHelper interface's StartElementHandler method. This method will
		handle Scope tags as well as tags relating to DatumTypes like Integer and Float.
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
		handle Scope tags as well as tags relating to DatumTypes like Integer and Float.
		@param sharedData A reference to the currently used shared data by the parse master.
		@param elementName A string containing the name of the current element being processed.
		@return true if the element was handled by this method. */
		virtual bool EndElementHandler(XmlParseMaster::SharedData& sharedData,
									   const std::string& elementName) override;

		/** Makes a clone of this parse helper in its current state.
		@return A pointer to the newly allocated parse helper.*/
		virtual IXmlParseHelper* Clone() const override;

	private:

		Datum& FetchDatum(ScopeSharedData& scopeSharedData,
						  const HashMap<std::string, std::string>& attributes);

		void HandleScope(ScopeSharedData& scopeSharedData,
						 const HashMap<std::string, std::string>& attributes);

		void HandleInteger(ScopeSharedData& scopeSharedData,
						   const HashMap<std::string, std::string>& attributes);

		void HandleFloat(ScopeSharedData& scopeSharedData,
						 const HashMap<std::string, std::string>& attributes);

		void HandleVector(ScopeSharedData& scopeSharedData,
						  const HashMap<std::string, std::string>& attributes);

		void HandleMatrix(ScopeSharedData& scopeSharedData,
						  const HashMap<std::string, std::string>& attributes);

		void HandleString(ScopeSharedData& scopeSharedData,
						  const HashMap<std::string, std::string>& attributes);

	private:

		static std::string sScopeTag;
		static std::string sIntegerTag;
		static std::string sFloatTag;
		static std::string sVectorTag;
		static std::string sMatrixTag;
		static std::string sStringTag;
	};
}