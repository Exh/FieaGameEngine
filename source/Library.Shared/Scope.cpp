#include "pch.h"
#include "Datum.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Scope)

	Scope::Scope(std::uint32_t capacity) :
		mParent(nullptr)
	{
		mVector.Reserve(capacity);
	}

	Scope::~Scope()
	{
		Destroy();
	}

	Scope::Scope(const Scope& rhs) : 
		mParent(nullptr)
	{
		DeepCopy(rhs);
	}

	Scope& Scope::operator=(const Scope& rhs)
	{
		if (this != &rhs)
		{
			Destroy();
			DeepCopy(rhs);
		}

		return *this;
	}

	Scope::Scope(Scope&& rhs)
	{
		operator=(rhs);
	}

	Scope& Scope::operator=(Scope&& rhs)
	{
		if (this != &rhs)
		{

			Destroy();

			// Firstly, go through the rhs's parent and update all references to
			// rhs with this instead, as all of rhs's data is moving to this.
			if (rhs.mParent != nullptr)
			{
				for (EntryType* entry : rhs.mParent->mVector)
				{
					if (entry->second.Type() == DatumType::Scope)
					{
						Datum& d = entry->second;
						for (std::uint32_t i = 0; i < d.Size(); i++)
						{
							if (&(d[i]) == &rhs)
							{
								d.Set(this, i);
							}
						}
					}
				}
			}

			// Now go through rhs's contained datums. Change parent from rhs to this.
			for (EntryType* entry : rhs.mVector)
			{
				if (entry->second.Type() == DatumType::Scope)
				{
					Datum& d = entry->second;
					for (std::uint32_t i = 0; i < d.Size(); i++)
					{
						if (d[i].mParent == &rhs)
						{
							d[i].mParent = this;
						}
					}
				}
			}

			// Now perform the move
			mVector = std::move(rhs.mVector);
			mMap = std::move(rhs.mMap);
			mParent = rhs.mParent;

			rhs.mParent = nullptr;
		}

		return *this;
	}

	void Scope::Destroy()
	{
		Orphan();

		// Find all child scopes and destroy them
		for (auto entry : mVector)
		{
			Datum& datum = entry->second;

			if (datum.Type() == DatumType::Scope)
			{
				for (std::uint32_t i = 0; i < datum.Size(); i++)
				{
					delete datum.GetScope(i);
					--i;
				}
			}
		}

		mVector.Destroy();
		mMap.Clear();
	}

	void Scope::DeepCopy(const Scope& rhs)
	{
		// This will copy the datums between the vector/maps of each scope
		for (auto& entry : rhs.mVector)
		{
			MapType::Iterator it = mMap.Insert(EntryType(entry->first, entry->second));
			mVector.PushBack(&(*it));
			Datum& datum = (*it).second;

			// Need to recursively copy scopes
			if (datum.Type() == DatumType::Scope)
			{
				for (std::uint32_t i = 0; i < datum.Size(); i++)
				{
					Scope*& scope = datum.GetScope(i);
					Scope*& rhsScope = entry->second.GetScope(i);
					
					scope = new Scope();
					scope->DeepCopy(*rhsScope);
					datum.GetScope(i)->mParent = this;
				}
			}
		}

		// Parent should always be nullptr
		mParent = nullptr;
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
			datum = &((*it).second);
		}

		return datum;
	}

	Datum* Scope::Search(const std::string& name, Scope** scope)
	{
		return const_cast<Datum*>(const_cast<const Scope*>(this)->Search(name, scope));
	}

	const Datum* Scope::Search(const std::string& name, Scope** scope) const
	{
		Datum* datum = nullptr;
		bool found = false;

		if (scope != nullptr)
		{
			*scope = nullptr;
		}

		for (auto value : mVector)
		{
			if (value->first == name)
			{
				datum = &value->second;
				found = true;

				if (scope != nullptr)
				{
					*scope = const_cast<Scope*>(this);
				}
			}
		}

		if (!found &&
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
		Datum& datum = Append(name);

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

		return *scope;
	}

	void Scope::Adopt(Scope& scope, const std::string& name)
	{
		if(this != &scope)
		{
			Datum& datum = Append(name);

			if (datum.Type() == DatumType::Unknown)
			{
				datum.SetType(DatumType::Scope);
			}

			if (datum.Type() != DatumType::Scope)
			{
				throw std::exception("Adopting a scope at a key that corresponds to a non-Scope Datum.");
			}

			scope.Orphan();
			scope.mParent = this;

			datum.PushBack(&scope);
		}
	}

	Datum& Scope::operator[](const std::string& name)
	{
		return Append(name);
	}

	Datum& Scope::operator[](std::uint32_t index)
	{
		return const_cast<Datum&>(const_cast<const Scope*>(this)->operator[](index));
	}

	const Datum& Scope::operator[](std::uint32_t index) const
	{
		if (index >= mVector.Size())
		{
			throw std::exception("Index out of bounds.");
		}

		return mVector[index]->second;
	}

	bool Scope::operator==(const Scope& rhs) const
	{
		if (this != &rhs)
		{
			if (mVector.Size() != rhs.mVector.Size())
			{
				return false;
			}

			if (mVector.Size() == rhs.mVector.Size())
			{
				for (std::uint32_t i = 0; i < mVector.Size(); i++)
				{
					if (mVector[i]->first != rhs.mVector[i]->first ||
						mVector[i]->second != rhs.mVector[i]->second)
					{
						return false;
					}
				}
			}
		}

		return true;
	}

	bool Scope::Equals(const RTTI* rhs) const
	{
		Scope* rhsScope = rhs->As<Scope>();

		if (rhsScope != nullptr)
		{
			return operator==(*rhsScope);
		}

		return false;
	}

	std::string Scope::ToString() const
	{
		return std::to_string(mVector.Size());
	}

	bool Scope::operator!=(const Scope& rhs) const
	{
		return !operator==(rhs);
	}

	Scope* Scope::GetParent()
	{
		return mParent;
	}

	const Scope* Scope::GetParent() const
	{
		return mParent;
	}

	void Scope::Orphan()
	{
		if (mParent != nullptr)
		{
			for (auto entry : mParent->mVector)
			{
				if (entry->second.Type() == DatumType::Scope)
				{
					entry->second.Remove(this);
				}
			}

			mParent = nullptr;
		}
	}
}
