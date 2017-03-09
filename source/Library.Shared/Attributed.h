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

		/** Default constructor. Creates an attributed with a this pointer.*/
		Attributed();

		/** Destructor. Frees all heap allocated memory.*/
		virtual ~Attributed();

		/** Populates the prescribed attributes of Attributed, which contains only the
		this pointer. A similar function must be implemented in all child Attribute's 
		to ensure their prescribed attributes are registered.*/
		void Populate();

		/** Copy constructor. Will make "this" a deep copy of rhs.
			@param rhs Attribute to copy from.*/
		Attributed(const Attributed& rhs);

		/** Copy assignment operator. Will make "this" a deep copy of rhs.
			Will first delete any heap allocated data currently owned by "this".
			@param rhs Attributed to copy from.
			@return a reference to this.*/
		Attributed& operator=(const Attributed& rhs);

		/** Move constructor. Will move rhs to "this". Rhs will no longer
			be usable after the operation.
			@param rhs Reference of object to move.*/
		Attributed(Attributed&& rhs);

		/** Move assignment operator. Will move rhs to "this".
			Will first delete any heap allocated data currently owned by "this".
			@param rhs Attributed to move.
			@return a reference to this.*/
		Attributed& operator=(Attributed&& rhs);

		/** Will check if the provided string matches the key of any prescribed attributes.
			@param key String with which to search prescribed attribute cache.
			@return true is the key matches a prescribed attribute. false otherwise.*/
		bool IsPrescribedAttribute(const std::string& key) const;

		/** Will check if the provided string matches the key of any auxiliary attributes.
			@param key String with which to search prescribed attribute cache.
			@return true is the key matches an auxiliary attribute. false otherwise.*/
		bool IsAuxiliaryAttribute(const std::string& key) const;

		/** Will check if the provided string matches the key of any attributes.
			@param key String with which to search attributes.
			@return true is the key matches an attribute. false otherwise.*/
		bool IsAttribute(const std::string& key) const;

		/** Appends an auxiliary attribute to this Attributed. An auxiliary attribute
			can exist on a per-instance basis.
			@param key The key at which a new datum will be assigned.
			@throw exception If the key matches a prescribed attribute.
			@return A reference to the newly created datum.*/
		Datum& AddAuxiliaryAttribute(const std::string& key);

		/** Will clear the prescribed attribute cache, prescribed attribute keys from
			a Attributed inheriting classes.*/
		static void ClearPrescribedAttributeCache();

		/** Equals returns true if rhs is equivalent to this scope.
			@param rhs RTTI object to compare against.
			@return True if equivalent. */
		virtual bool Equals(const RTTI* rhs) const override;

		/** Translates this scope into a string.
			@return The string version of this scope. */
		virtual std::string ToString() const override;

		/** Compares this attribute with another.
			@param rhs Other attributes to compare against.
			@return true if they are logically equivalent. false otherwise. */
		bool operator==(const Attributed& rhs) const;

		/** Compares this attribute with another.
			@param rhs Other attributes to compare against.
			@return false if they are logically equivalent. true otherwise. */
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

		void FixNativePointers();

	private:

		Datum& AppendPrescribedAttribute(const std::string& key);

		void RegisterNativeOffset(const std::string& key, std::int64_t bytes);

		static HashMap<std::uint64_t, Vector<std::string>> sPrescribedAttributeCache;
		static HashMap<std::uint64_t, Vector<std::uint32_t>> sNativeMemberOffsets;
	};
}
