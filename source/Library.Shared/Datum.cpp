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

	DatumType Datum::Type() const
	{
		return mType;
	}

	void Datum::SetType(DatumType type)
	{
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

			/*mData.vp = malloc()*/
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

			for (std::uint32_t i = 0; i < mSize; i++)
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
}