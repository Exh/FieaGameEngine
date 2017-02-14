#pragma once

#include <string>
#include <glm/glm.hpp>

namespace FieaGameEngine
{
	class RTTI;

	enum class DatumType
	{
		Unknown = 0,
		Integer,
		Float,
		Vector,
		Matrix,
		Table,
		String,
		Pointer
	};

	class Datum final
	{
	public:

		Datum();
		~Datum();
		Datum(const Datum& rhs);
		Datum& operator=(const Datum& rhs);

		Datum& operator=(std::int32_t rhs);
		Datum& operator=(float rhs);
		Datum& operator=(const glm::vec4& rhs);
		Datum& operator=(const glm::mat4& rhs);
		Datum& operator=(const std::string& rhs);
		Datum& operator=(RTTI* rhs);

		DatumType Type() const;
		void SetType(DatumType type);

		std::uint32_t Size() const;
		void SetSize(std::uint32_t size);

		void Clear();

		void SetStorage(std::int32_t* data, std::uint32_t size);
		void SetStorage(float* data, std::uint32_t size);
		void SetStorage(glm::vec4* data, std::uint32_t size);
		void SetStorage(glm::mat4* data, std::uint32_t size);
		void SetStorage(std::string* data, std::uint32_t size);
		void SetStorage(RTTI** data, std::uint32_t size);

		bool operator==(const Datum& rhs) const;
		bool operator==(const std::int32_t& rhs) const;
		bool operator==(const float& rhs) const;
		bool operator==(const glm::vec4& rhs) const;
		bool operator==(const glm::mat4& rhs) const;
		bool operator==(const std::string& rhs) const;
		bool operator==(const RTTI* const& rhs) const;

		bool operator!=(const Datum& rhs) const;
		bool operator!=(const std::int32_t& rhs) const;
		bool operator!=(const float& rhs) const;
		bool operator!=(const glm::vec4& rhs) const;
		bool operator!=(const glm::mat4& rhs) const;
		bool operator!=(const std::string& rhs) const;
		bool operator!=(const RTTI* const& rhs) const;

		void Set(std::int32_t value, std::uint32_t index = 0);
		void Set(float value, std::uint32_t index = 0);
		void Set(const glm::vec4& value, std::uint32_t index = 0);
		void Set(const glm::mat4& value, std::uint32_t index = 0);
		void Set(const std::string& value, std::uint32_t index = 0);
		void Set(RTTI* value, std::uint32_t index = 0);

		std::int32_t& GetInteger(std::uint32_t index = 0);
		float& GetFloat(std::uint32_t index = 0);
		glm::vec4& GetVector(std::uint32_t index = 0);
		glm::mat4& GetMatrix(std::uint32_t index = 0);
		std::string& GetString(std::uint32_t index = 0);
		RTTI*& GetPointer(std::uint32_t index = 0);

		const std::int32_t& GetInteger(std::uint32_t index = 0) const;
		const float& GetFloat(std::uint32_t index = 0) const;
		const glm::vec4& GetVector(std::uint32_t index = 0) const;
		const glm::mat4& GetMatrix(std::uint32_t index = 0) const;
		const std::string& GetString(std::uint32_t index = 0) const;
		const RTTI* const& GetPointer(std::uint32_t index = 0) const;

		void SetFromString(const std::string& text, std::uint32_t index = 0);

		std::string ToString(std::uint32_t index = 0) const;

		void PushBack(std::int32_t value);
		void PushBack(float value);
		void PushBack(glm::vec4& value);
		void PushBack(glm::mat4& value);
		void PushBack(std::string& value);
		void PushBack(RTTI* value);

	private:

		void PreAssignment(DatumType type);

		void PreGet(std::uint32_t index, DatumType type) const;

		void PreSetStorage();

		void PostSetStorage(DatumType type, std::uint32_t size);

		void PreSet(std::uint32_t index, DatumType type);

		void Reserve(std::uint32_t capacity);

		void DeepCopy(const Datum& rhs);

		void ExpandInternalStorage();

		void Destroy();

		std::uint32_t GetDatumTypeSize() const;

		DatumType mType;

		bool mExternal;

		std::uint32_t mSize;

		std::uint32_t mCapacity;

		union
		{
			std::int32_t* i;
			float* f;
			glm::vec4* v;
			glm::mat4* m;
			std::string* s;
			RTTI** p;
			void* vp;
		} mData;
	};
}
