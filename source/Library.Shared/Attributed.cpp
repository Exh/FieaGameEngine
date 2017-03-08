#include "pch.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Attributed)

	HashMap<std::uint64_t, Vector<std::string>> Attributed::sPrescribedAttributeCache;

	Attributed::Attributed()
	{
		Populate();
	}

	Attributed::~Attributed()
	{
	
	}

	void Attributed::Populate()
	{
		(*this)["this"] = static_cast<RTTI*>(this);
	}

	Attributed::Attributed(const Attributed& rhs)
	{
		DeepCopy(rhs);

		(*this)["this"] = static_cast<RTTI*>(this);
	}

	Attributed& Attributed::operator=(const Attributed& rhs)
	{
		Scope::operator=(rhs);

		(*this)["this"] = static_cast<RTTI*>(this);

		return *this;
	}

	bool Attributed::IsPrescribedAttribute(const std::string& key) const
	{
		auto it = sPrescribedAttributeCache.Find(TypeIdInstance());

		if (it != sPrescribedAttributeCache.end())
		{
			return ((*it).second.Find(key) != (*it).second.end());
		}

		return false;
	}

	bool Attributed::IsAuxiliaryAttribute(const std::string& key) const
	{
		return IsAttribute(key) && !IsPrescribedAttribute(key);
	}

	bool Attributed::IsAttribute(const std::string& key) const
	{
		return (mMap.Find(key) != mMap.end());
	}

	Datum& Attributed::AddAuxiliaryAttribute(const std::string& key)
	{
		if (IsPrescribedAttribute(key))
		{
			throw std::exception("Prescribed attribute with same key already exists.");
		}

		return Append(key);
	}

	void Attributed::ClearPrescribedAttributeCache()
	{
		sPrescribedAttributeCache.Clear();
	}

	void Attributed::AddInternalAttribute(const std::string& key, std::int32_t value)
	{
		AppendPrescribedAttribute(key).PushBack(value);
	}

	void Attributed::AddInternalAttribute(const std::string& key, float value)
	{
		AppendPrescribedAttribute(key).PushBack(value);
	}

	void Attributed::AddInternalAttribute(const std::string& key, const glm::vec4& value)
	{
		AppendPrescribedAttribute(key).PushBack(value);
	}

	void Attributed::AddInternalAttribute(const std::string& key, const glm::mat4& value)
	{
		AppendPrescribedAttribute(key).PushBack(value);
	}

	void Attributed::AddInternalAttribute(const std::string& key, const std::string& value)
	{
		AppendPrescribedAttribute(key).PushBack(value);
	}

	void Attributed::AddInternalAttribute(const std::string& key, RTTI* value)
	{
		AppendPrescribedAttribute(key).PushBack(value);
	}

	void Attributed::AddExternalAttribute(const std::string& key,  std::int32_t* data, std::uint32_t size)
	{
		AppendPrescribedAttribute(key).SetStorage(data, size);
	}

	void Attributed::AddExternalAttribute(const std::string& key, float* data, std::uint32_t size)
	{
		AppendPrescribedAttribute(key).SetStorage(data, size);
	}

	void Attributed::AddExternalAttribute(const std::string& key, glm::vec4* data, std::uint32_t size)
	{
		AppendPrescribedAttribute(key).SetStorage(data, size);
	}

	void Attributed::AddExternalAttribute(const std::string& key, glm::mat4* data, std::uint32_t size)
	{
		AppendPrescribedAttribute(key).SetStorage(data, size);
	}

	void Attributed::AddExternalAttribute(const std::string& key, std::string* data, std::uint32_t size)
	{
		AppendPrescribedAttribute(key).SetStorage(data, size);
	}

	void Attributed::AddExternalAttribute(const std::string& key, RTTI** data, std::uint32_t size)
	{
		AppendPrescribedAttribute(key).SetStorage(data, size);
	}

	Scope& Attributed::AddNestedScopeAttribute(const std::string& key)
	{
		RegisterPrescribedAttribute(key);
		return AppendScope(key);
	}

	void Attributed::AddNestedScopeAttribute(const std::string& key, Scope& scope)
	{
		RegisterPrescribedAttribute(key);
		Adopt(scope, key);
	}

	Datum& Attributed::AppendPrescribedAttribute(const std::string& key)
	{
		RegisterPrescribedAttribute(key);
		return Append(key);
	}

	void Attributed::RegisterPrescribedAttribute(const std::string& key)
	{
		if (!IsPrescribedAttribute(key))
		{
			sPrescribedAttributeCache[TypeIdInstance()].PushBack(key);
		}
	}

	bool Attributed::Equals(const RTTI* rhs) const
	{
		Attributed* rhsScope = rhs->As<Attributed>();

		if (rhsScope != nullptr)
		{
			return operator==(*rhsScope);
		}

		return false;
	}

	std::string Attributed::ToString() const
	{
		return std::to_string(mVector.Size());
	}

	bool Attributed::operator==(const Attributed& rhs) const
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
					if (mVector[i]->first != rhs.mVector[i]->first)
					{
						return false;
					}

					if (mVector[i]->first != "this" &&
						mVector[i]->second != rhs.mVector[i]->second)
					{
						return false;
					}
				}
			}
		}

		return true;
	}

	bool Attributed::operator!=(const Attributed& rhs) const
	{
		return !operator==(rhs);
	}
}