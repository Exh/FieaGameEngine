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

		void Populate();

		Attributed(const Attributed& rhs);

		Attributed& operator=(const Attributed& rhs);

		bool IsPrescribedAttribute(const std::string& key) const;

		bool IsAuxiliaryAttribute(const std::string& key) const;

		bool IsAttribute(const std::string& key) const;

		Datum& AddAuxiliaryAttribute(const std::string& key);

		static void ClearPrescribedAttributeCache();

		/** Equals returns true if rhs is equivalent to this scope.
			@param rhs RTTI object to compare against.
			@return True if equivalent. */
		virtual bool Equals(const RTTI* rhs) const override;

		/** Translates this scope into a string.
			@return The string version of this scope. */
		virtual std::string ToString() const override;

		bool operator==(const Attributed& rhs) const;

		bool operator!=(const Attributed& rhs) const;

	protected:

		void AddInternalAttribute(const std::string& key, std::int32_t value);
		void AddInternalAttribute(const std::string& key, float value);
		void AddInternalAttribute(const std::string& key, const glm::vec4& value);
		void AddInternalAttribute(const std::string& key, const glm::mat4& value);
		void AddInternalAttribute(const std::string& key, const std::string& value);
		void AddInternalAttribute(const std::string& key, RTTI* value);

		void AddExternalAttribute(const std::string& key, std::int32_t* data, std::uint32_t size);
		void AddExternalAttribute(const std::string& key, float* data, std::uint32_t size);
		void AddExternalAttribute(const std::string& key, glm::vec4* data, std::uint32_t size);
		void AddExternalAttribute(const std::string& key, glm::mat4* data, std::uint32_t size);
		void AddExternalAttribute(const std::string& key, std::string* data, std::uint32_t size);
		void AddExternalAttribute(const std::string& key, RTTI** data, std::uint32_t size);

		Scope& AddNestedScopeAttribute(const std::string& key);
		void AddNestedScopeAttribute(const std::string& key, Scope& scope);

	private:

		Datum& AppendPrescribedAttribute(const std::string& key);

		void RegisterPrescribedAttribute(const std::string& key);

		//void DeepCopy(const Attributed& rhs);

		static HashMap<std::uint64_t, Vector<std::string>> sPrescribedAttributeCache;
	};
}
