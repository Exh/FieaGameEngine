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

		Scope(std::uint32_t capacity = 0) explicit;

		virtual ~Scope();

		Scope(const Scope& rhs);

		Scope& operator=(const Scope& rhs);

		Datum* Find(const std::string& name);

		const Datum* Find(const std::string& name) const;

		Datum* Search(const std::string& name, Scope** scope = nullptr);

		const Datum* Search(const std::string& name, Scope** scope = nullptr) const;

		Datum& Append(const std::string& name);

		Scope& AppendScope(const std::string& name);

		void Adopt(Scope& scope, const std::string& name);

		Scope* GetParent();

		Datum& operator[](const std::string& name);

		Datum& operator[](std::uint32_t index);

		const Datum& operator[](std::uin32_t index);

		bool operator==(const Scope& rhs);

		bool operator!=(const Scope& rhs);

		//std::string FindName(const Scope* scope);

	private:

		void Orphan();

		void Destroy();

		void DeepCopy(const Scope& rhs);

		HashMap<std::string, Datum> mMap;
		Vector<EntryType*> mVector;
		Scope* mParent;
	};
}