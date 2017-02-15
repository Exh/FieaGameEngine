#include "pch.h"
#include "Datum.h"

namespace FieaGameEngine
{
	Scope::Scope(std::uint32_t capacity = 0) :
		mParent(nullptr)
	{
		mVector.Reserve(capacity);
	}

	Scope::~Scope()
	{
		Destroy();
	}

	Scope::Scope(const Scope& rhs)
	{
		DeepCopy(rhs);
	}

	Scope& Scope::operator=(const Scope& rhs)
	{
		if (this != &rhs)
		{
			Destroy();
			DeepCopy();
		}
	}

	void Scope::Destroy()
	{
		// Find all child scopes and destroy them
	}

	void Scope::DeepCopy(const Scope& rhs)
	{

	}

	Datum* Scope::Find(const std::string& name)
	{
		return const_cast<Datum*>(const_cast<const Scope*>(this)->Find(name));
	}

	const Datum* Scope::Find(const std::string& name) const
	{
		Datum* datum = nullptr;
		MapType::Iterator it = mMap.Find(name);

		if (it != mMap.end())
		{
			datum = (*it).first;
		}

		return datum;
	}

	Datum* Scope::Search(const std::string& name, Scope** scope)
	{
		return const_cast<Datum*>(const_cast<const Scope*>(this)->Search(name, scope));
	}

	const Datum* Scope::Search(const std::string& name, Scope** scope = nullptr) const
	{
		Datum* datum = nullptr;

		for (auto value : mVector)
		{
			if (value->first == name)
			{
				datum = &value->second;

				if (scope != nullptr)
				{
					*scope = this;
				}
			}
		}

		if (foundScope == nullptr &&
			mParent != nullptr)
		{
			datum = mParent->Search(name, scope);
		}

		return datum;
	}

	Datum& Scope::Append(const std::string& name)
	{
		bool inserted = false;

		MapType::Iterator it = mMap.Insert(EntryType(name, Datum()), &inserted);

		// Add to the order vector if a new entry was actually inserted in the map.
		if (inserted)
		{
			mVector.PushBack(&(*it));
		}

		return (*it).second;
	}

	Scope& Scope::AppendScope(const std::string& name)
	{
		bool inserted = false;

		Datum& datum = mMap.Insert(EntryType(name, Datum()), &inserted);

		if (datum.Type() == DatumType::Unknown)
		{
			datum.SetType(DatumType::Scope);
		}

		if (datum.Type() != DatumType::Scope)
		{
			throw std::exception("Appended a scope with a key that corresponds to a non-Scope Datum.");
		}

		Scope* scope = new Scope();
		datum.PushBack(scope);
		
		scope->mParent = this;
	}

	void Scope::Adopt(Scope& scope, const std::string& name, std::uint32_t index)
	{
		scope.Orphan();

		mMap.Insert(EntryType(name, index));
	}

	void Scope::Orphan()
	{
		if (mParent != nullptr)
		{
			for (auto entry : mVector)
			{
				if (entry->second.Type() == DatumType::Scope)
				{
					entry->second.Remove(this);
					//for (std::uint32_t i = 0; i < entry->second.Size(); i++)
					//{
					//	if (entry->second.GetScope(i) == this)
					//	{
					//		entry->second.Remove(i);
					//	}
					//}
				}
			}
		}
	}
}
