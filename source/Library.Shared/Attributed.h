#pragma once

#include "Scope.h"
#include "HashMap.h"
#include <string>

namespace FieaGameEngine
{
	class Attributed : public Scope 
	{
		RTTI_DECLARATIONS(Attributed, Scope)

	public:

		Attributed();

		virtual ~Attributed();

		Attributed(const Attributed& rhs);

		Attributed& operator=(const Attributed& rhs);

		virtual void Populate();

		bool IsPrescribedAttribute(const std::string& key) const;

		bool IsAuxilaryAttribute(const std::string& key) const;

		bool IsAttribute(const std::string& key) const;

		Datum& AddAuxilaryAttribute(const std::string& key);

		static void ClearPrescribedAttributeCache();

	protected:

		void AddInternalAttribute(const std::string& key, std::int32_t value);
		void AddInternalAttribute(const std::string& key, float value);
		void AddInternalAttribute(const std::string& key, glm::vec4 value);
		void AddInternalAttribute(const std::string& key, glm::mat4 value);
		void AddInternalAttribute(const std::string& key, std::string value);
		void AddInternalAttribute(const std::string& key, RTTI* value);

		void AddExternalAttribute(const std::string& key, std::int32_t* data, std::uint32_t size);
		void AddExternalAttribute(const std::string& key, float* data, std::uint32_t size);
		void AddExternalAttribute(const std::string& key, glm::vec4* data, std::uint32_t size);
		void AddExternalAttribute(const std::string& key, glm::mat4* data, std::uint32_t size);
		void AddExternalAttribute(const std::string& key, std::string* data, std::uint32_t size);
		void AddExternalAttribute(const std::string& key, RTTI** data, std::uint32_t size);

	private:

		Datum& AppendPrescribedAttribute(const std::string& key);

		static HashMap<std::uint64_t, Vector<std::string>> sPrescribedAttributeCache;
	};
}
