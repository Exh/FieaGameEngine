#include "pch.h"

namespace FieaGameEngine
{
	Datum::Datum() :
		mType(DatumType::Unknown),
		mExternal(false),
		mSize(0),
		mCapacity(0)
	{
		mData.vp = nullptr;
	}

	Datum::~Datum()
	{
		Destroy();

		mType = DatumType::Unknown;
		mExternal = false;
	}

	Datum::Datum(const Datum& rhs) :
		mType(DatumType::Unknown),
		mExternal(false),
		mSize(0),
		mCapacity(0)
	{
		mData.vp = nullptr;

		DeepCopy(rhs);
	}

	Datum& Datum::operator=(const Datum& rhs)
	{
		if (this != &rhs)
		{
			Destroy();
			DeepCopy(rhs);
		}

		return *this;
	}

	void Datum::PreAssignment(DatumType type)
	{
		if (mType == DatumType::Unknown)
		{
			mType = type;
		}

		if (mType != type)
		{
			throw std::exception("Invalid type assignment.");
		}

		if (mSize == 0)
		{
			Reserve(1);
			
			switch (type)
			{
			case DatumType::Vector:
				new (mData.v) glm::vec4();
				break;
			case DatumType::Matrix:
				new (mData.m) glm::mat4();
				break;
			case DatumType::String:
				new (mData.s) std::string();
				break;
			}
			mSize = 1;
		}
	}

	Datum& Datum::operator=(std::int32_t rhs)
	{
		PreAssignment(DatumType::Integer);
		mData.i[0] = rhs;
		return *this;
	}

	Datum& Datum::operator=(float rhs)
	{
		PreAssignment(DatumType::Float);
		mData.f[0] = rhs;
		return *this;
	}

	Datum& Datum::operator=(const glm::vec4& rhs)
	{
		PreAssignment(DatumType::Vector);
		mData.v[0] = rhs;
		return *this;
	}

	Datum& Datum::operator=(const glm::mat4& rhs)
	{
		PreAssignment(DatumType::Matrix);
		mData.m[0] = rhs;
		return *this;
	}

	Datum& Datum::operator=(const std::string& rhs)
	{
		PreAssignment(DatumType::String);
		mData.s[0] = rhs;
		return *this;
	}

	Datum& Datum::operator=(RTTI* rhs)
	{
		PreAssignment(DatumType::Pointer);
		mData.p[0] = rhs;
		return *this;
	}

	DatumType Datum::Type() const
	{
		return mType;
	}

	void Datum::SetType(DatumType type)
	{
		if (type == DatumType::Unknown)
		{
			throw std::exception("Cannot set datum type to Unknown");
		}

		if (mType == DatumType::Unknown ||
			mType == type)
		{
			mType = type;
		}
		else
		{
			throw std::exception("Datum type has already been set and cannot be changed with SetType().");
		}
	}

	std::uint32_t Datum::Size() const
	{
		return mSize;
	}

	void Datum::SetSize(std::uint32_t size)
	{
		if (mExternal)
		{
			throw std::exception("Cannot set size on Datum with external storage.");
		}

		if (mType == DatumType::Unknown)
		{
			throw std::exception("Cannot set size on a datum with no type associated with it.");
		}

		if (size > mCapacity)
		{
			Reserve(size);
		}

		if (size < mSize)
		{
			assert(mData.vp != nullptr);

			for (std::uint32_t i = size; i < mSize; i++)
			{
				switch (mType)
				{
				case DatumType::Vector:
					mData.v[i].glm::vec4::~vec4();
					break;
				case DatumType::Matrix:
					mData.m[i].glm::mat4::~mat4();
					break;
				case DatumType::String:
					mData.s[i].std::string::~string();
					break;
				}
			}
		}

		if (size > mSize)
		{
			assert(mData.vp != nullptr);

			for (std::uint32_t i = mSize; i < size; i++)
			{
				switch (mType)
				{
				case DatumType::Integer:
					mData.i[i] = 0;
					break;
				case DatumType::Float:
					mData.f[i] = 0.0f;
					break;
				case DatumType::Vector:
					new (mData.v + i) glm::vec4();
					break;
				case DatumType::Matrix:
					new (mData.m + i) glm::mat4();
					break;
				case DatumType::String:
					new (mData.s + i) std::string();
					break;
				case DatumType::Pointer:
					mData.p[i] = nullptr;
					break;
				}
			}
		}

		mSize = size;
	}

	void Datum::Clear()
	{
		if (!mExternal)
		{
			for (std::uint32_t i = 0; i < mSize; i++)
			{
				switch (mType)
				{
				case DatumType::String:
					mData.s[i].std::string::~string();
					break;
				}
			}
		}

		mSize = 0;
		mExternal = false;
	}

	void Datum::SetStorage(std::int32_t* data, std::uint32_t size)
	{
		PreSetStorage();
		mData.i = data;
		mSize = size;
		mCapacity = size;
	}

	void Datum::SetStorage(float* data, std::uint32_t size)
	{
		PreSetStorage();
		mData.f = data;
		mSize = size;
		mCapacity = size;
	}

	void Datum::SetStorage(glm::vec4* data, std::uint32_t size)
	{
		PreSetStorage();
		mData.v = data;
		mSize = size;
		mCapacity = size;
	}

	void Datum::SetStorage(glm::mat4* data, std::uint32_t size)
	{
		PreSetStorage();
		mData.m = data;
		mSize = size;
		mCapacity = size;
	}

	void Datum::SetStorage(std::string* data, std::uint32_t size)
	{
		PreSetStorage();
		mData.s = data;
		mSize = size;
		mCapacity = size;
	}

	void Datum::SetStorage(RTTI** data, std::uint32_t size)
	{
		PreSetStorage();
		mData.p = data;
		mSize = size;
		mCapacity = size;
	}

	void Datum::PreSetStorage()
	{
		if (mType != DatumType::Unknown)
		{
			throw std::exception("Invalid datum type.");
		}

		assert(mSize == 0);
		assert(mCapacity == 0);
		assert(mData.vp == nullptr);
		assert(mExternal == false);
	}

	void Datum::Set(std::int32_t value, std::uint32_t index)
	{
		PreSet(index, DatumType::Integer);
		mData.i[index] = value;
	}

	void Datum::Set(float value, std::uint32_t index)
	{
		PreSet(index, DatumType::Float);
		mData.f[index] = value;
	}

	void Datum::Set(const glm::vec4& value, std::uint32_t index)
	{
		PreSet(index, DatumType::Vector);
		mData.v[index] = value;
	}

	void Datum::Set(const glm::mat4& value, std::uint32_t index)
	{
		PreSet(index, DatumType::Matrix);
		mData.m[index] = value;
	}

	void Datum::Set(const std::string& value, std::uint32_t index)
	{
		PreSet(index, DatumType::String);
		mData.s[index] = value;
	}

	void Datum::Set(RTTI* value, std::uint32_t index)
	{
		PreSet(index, DatumType::Pointer);
		mData.p[index] = value;
	}

	void Datum::PreSet(std::uint32_t index, DatumType type)
	{
		if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}

		if (mType != type)
		{
			throw std::exception("Invalid type on Set().");
		}
	}

	std::int32_t& Datum::GetInteger(std::uint32_t index)
	{
		PreGet(index, DatumType::Integer);
		return mData.i[index];
	}

	float& Datum::GetFloat(std::uint32_t index)
	{
		PreGet(index, DatumType::Float);
		return mData.f[index];
	}

	glm::vec4& Datum::GetVector(std::uint32_t index)
	{
		PreGet(index, DatumType::Vector);
		return mData.v[index];
	}
	glm::mat4& Datum::GetMatrix(std::uint32_t index)
	{
		PreGet(index, DatumType::Matrix);
		return mData.m[index];
	}

	std::string& Datum::GetString(std::uint32_t index)
	{
		PreGet(index, DatumType::String);
		return mData.s[index];
	}

	RTTI*& Datum::GetPointer(std::uint32_t index)
	{
		PreGet(index, DatumType::Pointer);
		return mData.p[index];
	}

	const std::int32_t& Datum::GetInteger(std::uint32_t index) const
	{
		PreGet(index, DatumType::Integer);
		return mData.i[index];
	}

	const float& Datum::GetFloat(std::uint32_t index) const
	{
		PreGet(index, DatumType::Float);
		return mData.f[index];
	}

	const glm::vec4& Datum::GetVector(std::uint32_t index) const
	{
		PreGet(index, DatumType::Vector);
		return mData.v[index];
	}

	const glm::mat4& Datum::GetMatrix(std::uint32_t index) const
	{
		PreGet(index, DatumType::Matrix);
		return mData.m[index];
	}

	const std::string& Datum::GetString(std::uint32_t index) const
	{
		PreGet(index, DatumType::String);
		return mData.s[index];
	}

	const RTTI* const& Datum::GetPointer(std::uint32_t index) const
	{
		PreGet(index, DatumType::Pointer);
		return mData.p[index];
	}

	void Datum::PreGet(std::uint32_t index, DatumType type) const
	{
		if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}

		if (mType != type)
		{
			throw std::exception("Invalid type.");
		}
	}

	void Datum::PushBack(std::int32_t value)
	{
		if (mExternal)
		{
			throw std::exception("Cannot PushBack on Datum with external storage.");
		}

		if (mType == DatumType::Unknown)
		{
			SetType(DatumType::Integer);
		}

		if (mType != DatumType::Integer)
		{
			throw std::exception("Invalid Datum type.");
		}

		if (mSize == mCapacity)
		{
			ExpandInternalStorage();
		}

		new (mData.i + mSize) std::int32_t(value);
		mSize++;
	}

	void Datum::PushBack(float value)
	{
		if (mExternal)
		{
			throw std::exception("Cannot PushBack on Datum with external storage.");
		}

		if (mType == DatumType::Unknown)
		{
			SetType(DatumType::Float);
		}

		if (mType != DatumType::Float)
		{
			throw std::exception("Invalid Datum type.");
		}

		if (mSize == mCapacity)
		{
			ExpandInternalStorage();
		}

		new (mData.f + mSize) float(value);
		mSize++;
	}

	void Datum::PushBack(glm::vec4& value)
	{
		if (mExternal)
		{
			throw std::exception("Cannot PushBack on Datum with external storage.");
		}

		if (mType == DatumType::Unknown)
		{
			SetType(DatumType::Vector);
		}

		if (mType != DatumType::Vector)
		{
			throw std::exception("Invalid Datum type.");
		}

		if (mSize == mCapacity)
		{
			ExpandInternalStorage();
		}

		new (mData.v + mSize) glm::vec4(value);
		mSize++;
	}

	void Datum::PushBack(glm::mat4& value)
	{
		if (mExternal)
		{
			throw std::exception("Cannot PushBack on Datum with external storage.");
		}

		if (mType == DatumType::Unknown)
		{
			SetType(DatumType::Matrix);
		}

		if (mType != DatumType::Matrix)
		{
			throw std::exception("Invalid Datum type.");
		}

		if (mSize == mCapacity)
		{
			ExpandInternalStorage();
		}

		new (mData.m + mSize) glm::mat4(value);
		mSize++;
	}

	void Datum::PushBack(std::string& value)
	{
		if (mExternal)
		{
			throw std::exception("Cannot PushBack on Datum with external storage.");
		}

		if (mType == DatumType::Unknown)
		{
			SetType(DatumType::String);
		}

		if (mType != DatumType::String)
		{
			throw std::exception("Invalid Datum type.");
		}

		if (mSize == mCapacity)
		{
			ExpandInternalStorage();
		}

		new (mData.s + mSize) std::string(value);
		mSize++;
	}

	void Datum::PushBack(RTTI* value)
	{
		if (mExternal)
		{
			throw std::exception("Cannot PushBack on Datum with external storage.");
		}

		if (mType == DatumType::Unknown)
		{
			SetType(DatumType::Pointer);
		}

		if (mType != DatumType::Pointer)
		{
			throw std::exception("Invalid Datum type.");
		}

		if (mSize == mCapacity)
		{
			ExpandInternalStorage();
		}

		new (mData.p + mSize) RTTI*(value);
		mSize++;
	}

	void Datum::Reserve(std::uint32_t capacity)
	{
		if (mExternal)
		{
			throw std::exception("Cannot reserve internal memory for an external Datum.");
		}

		if (mType == DatumType::Unknown)
		{
			throw std::exception("Cannot reserve internal memory for a typeless Datum.");
		}

		if (capacity > mCapacity)
		{
			void* previousBuffer = mData.vp;

			mCapacity = capacity;
			std::int32_t typeSize = GetDatumTypeSize();
			mData.vp = malloc(mCapacity * typeSize);

			if (previousBuffer != nullptr)
			{
				memcpy(mData.vp, previousBuffer, typeSize * mSize);

				free(previousBuffer);
				previousBuffer = nullptr;
			}
		}
	}

	void Datum::DeepCopy(const Datum& rhs)
	{
		mType = rhs.mType;
		mExternal = rhs.mExternal;

		if (mExternal)
		{
			mData.vp = rhs.mData.vp;
			mSize = rhs.mSize;
			mCapacity = rhs.mCapacity;
		}
		else
		{
			Reserve(rhs.mCapacity);

			for (std::uint32_t i = 0; i < rhs.mSize; i++)
			{
				switch (mType)
				{
				case DatumType::Integer:
					PushBack(*(rhs.mData.i + i));
					break;
				case DatumType::Float:
					PushBack(*(rhs.mData.f + i));
					break;
				case DatumType::Vector:
					PushBack(*(rhs.mData.v + i));
					break;
				case DatumType::Matrix:
					PushBack(*(rhs.mData.m + i));
					break;
				case DatumType::String:
					PushBack(*(rhs.mData.s + i));
					break;
				case DatumType::Pointer:
					PushBack(*(rhs.mData.p + i));
					break;
				default:
					break;
				}
			}
		}

		mSize = rhs.mSize;
		mCapacity = rhs.mCapacity;
	}

	void Datum::ExpandInternalStorage()
	{
		assert(!mExternal);
		Reserve(mCapacity + 1);
	}

	void Datum::Destroy()
	{
		if (mData.vp != nullptr)
		{
			assert(!mExternal);
			assert(mType != DatumType::Unknown);

			for (std::uint32_t i = 0; i < mSize; i++)
			{
				switch (mType)
				{
				case DatumType::Vector:
					mData.v[i].glm::vec4::~vec4();
					break;
				case DatumType::Matrix:
					mData.m[i].glm::mat4::~mat4();
					break;
				case DatumType::String:
					mData.s[i].std::string::~string();
					break;
				}
			}

			free(mData.vp);
			mData.vp = nullptr;

			mSize = 0;
			mCapacity = 0;
		}
	}

	std::uint32_t Datum::GetDatumTypeSize()
	{
		std::uint32_t size = 0;

		switch (mType)
		{
		case DatumType::Integer:
			size = sizeof(std::int32_t);
			break;
		case DatumType::Float:
			size = sizeof(float);
			break;
		case DatumType::Vector:
			size = sizeof(glm::vec4);
			break;
		case DatumType::Matrix:
			size = sizeof(glm::mat4);
			break;
		case DatumType::String:
			size = sizeof(std::string);
			break;
		case DatumType::Pointer:
			size = sizeof(RTTI*);
			break;
		}

		return size;
	}
}