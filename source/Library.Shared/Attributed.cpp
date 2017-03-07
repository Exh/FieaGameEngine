#include "pch.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Attributed)

	HashMap<std::uint64_t, Vector<std::string>> Attributed::sPrescribedAttributeCache;

	Attributed::Attributed()
	{

	}

	Attributed::~Attributed()
	{
	
	}

	Attributed::Attributed(const Attributed& rhs)
	{
		rhs;
	}

	Attributed& Attributed::operator=(const Attributed& rhs)
	{
		rhs;
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

	Datum& Attributed::AppendPrescribedAttribute(const std::string& key)
	{
		Vector<std::string>& prescribedVector = sPrescribedAttributeCache[TypeIdInstance()];

		if (prescribedVector.Find(key) == prescribedVector.end())
		{
			prescribedVector.PushBack(key);
		}

		return Append(key);
	}
}