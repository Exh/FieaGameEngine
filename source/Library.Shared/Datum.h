#pragma once

#include <string>
#include <glm/glm.hpp>

class RTTI;

namespace FieaGameEngine
{
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
		bool operator==(const RTTI*& rhs) const;


		bool operator!=(const Datum& rhs) const;
		bool operator!=(const std::int32_t& rhs) const;
		bool operator!=(const float& rhs) const;
		bool operator!=(const glm::vec4& rhs) const;
		bool operator!=(const glm::mat4& rhs) const;
		bool operator!=(const std::string& rhs) const;
		bool operator!=(const RTTI*& rhs) const;

		void Set(std::int32_t& value, std::uint32_t index = 0);
		void Set(float& value, std::uint32_t index = 0);
		void Set(glm::vec4& value, std::uint32_t index = 0);
		void Set(glm::mat4& value, std::uint32_t index = 0);
		void Set(std::string& value, std::uint32_t index = 0);
		void Set(RTTI* value, std::uint32_t index = 0);

		template<typename T>
		T& Get(std::uint32_t index = 0);

		template<typename T>
		const T& Get(std::uint32_t index = 0) const;
		
		void SetFromString(std::string& text, std::uint32_t index = 0);

		std::string ToString() const;

		void PushBack(std::int32_t value);
		void PushBack(float value);
		void PushBack(glm::vec4& value);
		void PushBack(glm::mat4& value);
		void PushBack(std::string& value);
		void PushBack(RTTI* value);

	private:

		void Reserve(std::uint32_t capacity);

		void DeepCopy(const Datum& rhs);

		void ExpandInternalStorage();

		void Destroy();

		std::uint32_t GetDatumTypeSize();

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
