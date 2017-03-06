#pragma once

#include "RTTI.h"
#include "HashMap.h"
#include <string>
#include "Datum.h"

namespace FieaGameEngine
{
	class Scope : public RTTI
	{
		RTTI_DECLARATIONS(Scope, RTTI)

		typedef std::pair<std::string, Datum> EntryType;
		typedef HashMap<std::string, Datum> MapType;

	public:

		/** Constructor that takes a default starting capacity for the number
			of elements that the user expects the scope to contain. This initial
			capacity can reduce the number of memory allocations to increase 
			performance. Note: The preferred way of creating Scopes is by calling
			AppendScope() on it's parent scope. Non-top-level scopes should never be
			allocated on the stack.
			@param capacity Starting capacity of the scope. */
		Scope(std::uint32_t capacity = 0);

		/** Scope's destructor that destroys all of its heap allocated memory and
			recursively destroys child scopes as well. */
		virtual ~Scope();

		/** Copy constructor. Will make this new scope a deep copy of the provided scope.
			Child scopes will also be copied recursively (thus, deep copy).
			@param rhs The scope to copy from. */
		Scope(const Scope& rhs);

		/** Assignment operator for deep copying another scope to this scope.
			Child scopes will also be copied recursively (thus, deep copy).
			@param rhs Scope to copy from.
			@return reference to this scope. */
		Scope& operator=(const Scope& rhs);

		/** Looks for a scope entry with the same name as the one passed in.
			@param name Name of the entry to find.
			@return Pointer to the datum corresponding to name if found,
				nullptr otherwise. */
		Datum* Find(const std::string& name);

		/** Looks for a scope entry with the same name as the one passed in.
			@param name Name of the entry to find.
			@return Pointer to the datum corresponding to name if found,
				nullptr otherwise. */
		const Datum* Find(const std::string& name) const;

		/** Looks for a datum entry corresponding to the provided name. If an 
			entry matching the provided name string is not found, the parent
			scope's search method will be called in a recursive manner.
			@param name Name of datum entry to find.
			@param scope Output parameter to store a pointer of scope where the
				entry was found. 
			@return Pointer to the found datum. */
		Datum* Search(const std::string& name, Scope** scope = nullptr);

		/** Looks for a datum entry corresponding to the provided name. If an 
			entry matching the provided name string is not found, the parent
			scope's search method will be called in a recursive manner.
			@param name Name of datum entry to find.
			@param scope Output parameter to store a pointer of scope where the
				entry was found. 
			@return Pointer to the found datum. */
		const Datum* Search(const std::string& name, Scope** scope = nullptr) const;

		/** Creates a new datum entry at the given key. If a datum already exists
			at name's key, then a reference to that preexisting datum will be 
			returned instead.
			@param name The entry key to append a new datum at.
			@return Reference to the appended datum (or previously existing datum). */
		Datum& Append(const std::string& name);

		/** Creates a new scope at the datum entry matching the name parameter.
			If a datum already exists at name, a new scope pointer will be added to 
			that Scope's values array.
			@throw exception If a datum already exists at name's key and it is not 
				of type Unknown or Scope.
			@param name Entry key to append new scope at.
			@return Reference to the newly created scope. */
		Scope& AppendScope(const std::string& name);

		/** Takes a provided scope, and makes it a child of this scope at 
			the given key (name). This function will unparent the passed in 
			scope from its previous parent if it had one.
			@throw exception If the datum at key "name" already exists and is not
				of type Scope or Unknown.
			@param name Entry to add the new child.*/
		void Adopt(Scope& scope, const std::string& name);

		/** Returns this scope's parent.
			@return Pointer to parent. nullptr indicates no parent.*/
		Scope* GetParent();

		/** Returns this scope's parent.
			@return Pointer to parent. nullptr indicates no parent.*/
		const Scope* GetParent() const;

		/** Returns datum reference at the given key.
			@param name Key to check.
			@return Datum reference. */
		Datum& operator[](const std::string& name);

		/** Returns datum reference at the given order index.
			@throw exception If index is out of scope's bounds.
			@param index Index to check.
			@return Datum reference. */
		Datum& operator[](std::uint32_t index);

		/** Returns datum reference at the given order index.
			@throw exception If index is out of scope's bounds.
			@param index Index to check.
			@return Datum reference. */
		const Datum& operator[](std::uint32_t index) const;

		/** Equality operator between two scopes.
			@param rhs Other scope to compare against. 
			@return True if equivalent.*/
		bool operator==(const Scope& rhs) const;

		/** Inequality operator between two scopes.
			@param rhs Other scope to compare against. 
			@return True if not equivalent.*/
		bool operator!=(const Scope& rhs) const;

		/** Equals returns true if rhs is equivalent to this scope.
			@param rhs RTTI object to compare against.
			@return True if equivalent.
		*/
		virtual bool Scope::Equals(const RTTI* rhs) const override;

		/** Translates this scope into a string.
			@return The string version of this scope. */
		virtual std::string ToString() const;

	protected:

		HashMap<std::string, Datum> mMap;

	private:

		void Orphan();

		void Destroy();

		void DeepCopy(const Scope& rhs);

		Vector<EntryType*> mVector;
		Scope* mParent;
	};
}
