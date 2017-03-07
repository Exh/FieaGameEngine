#pragma once

#include <string>
#include <glm/glm.hpp>

namespace FieaGameEngine
{
	class Scope;
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
		Pointer,
		Scope
	};

	class Datum final
	{
	public:

		/** Default constructor for datum. Initializes the datum with 
		unknown type and zero size.*/
		Datum();

		/** Destructor. Deallocates any memory that is owned by this datum. */
		~Datum();

		/** Copy Constructor that deep copies the given Datum.
		@param rhs Datumt to copy from */
		Datum(const Datum& rhs);

		/** Assignment Operator for deep copying from another datum. 
		This assignment will change the Type of the datum and will 
		also change its storage type to match the other Datum.
		@param rhs The Datum to copy from.*/
		Datum& operator=(const Datum& rhs);

		/** Assignment Operator for deep copying a single element. If the 
		Datum's size is 0, this will increase its size to 1.
		@except exception If the function parameter type does not match this Datum's type.
		@param rhs Scalar value to assign at index 0*/
		Datum& operator=(std::int32_t rhs);

		/** Assignment Operator for deep copying a single element. If the 
		Datum's size is 0, this will increase its size to 1.
		@except exception If the function parameter type does not match this Datum's type.
		@param rhs Scalar value to assign at index 0*/
		Datum& operator=(float rhs);

		/** Assignment Operator for deep copying a single element. If the 
		Datum's size is 0, this will increase its size to 1.
		@except exception If the function parameter type does not match this Datum's type.
		@param rhs Scalar value to assign at index 0*/
		Datum& operator=(const glm::vec4& rhs);

		/** Assignment Operator for deep copying a single element. If the 
		Datum's size is 0, this will increase its size to 1.
		@except exception If the function parameter type does not match this Datum's type.
		@param rhs Scalar value to assign at index 0*/
		Datum& operator=(const glm::mat4& rhs);

		/** Assignment Operator for deep copying a single element. If the 
		Datum's size is 0, this will increase its size to 1.
		@except exception If the function parameter type does not match this Datum's type.
		@param rhs Scalar value to assign at index 0*/
		Datum& operator=(const std::string& rhs);

		/** Assignment Operator for deep copying a single element. If the 
		Datum's size is 0, this will increase its size to 1.
		@except exception If the function parameter type does not match this Datum's type.
		@param rhs Scalar value to assign at index 0*/
		Datum& operator=(RTTI* rhs);

		/** Assignment Operator for deep copying a single element. If the 
		Datum's size is 0, this will increase its size to 1.
		@except exception If the function parameter type does not match this Datum's type.
		@param rhs Scalar value to assign at index 0*/
		Datum& operator=(Scope* rhs);

		/** Gets the type that is associated with this Datum. 
		@return This Datum's type. */
		DatumType Type() const;

		/** Sets this Datum's type if it has not already been assigned.
		@except exception If this Datum has already been assigned a different type.
		@param type DatumType to set this Datum's type to*/
		void SetType(DatumType type);

		/** Gets the size, or number of elements, that the Datum currently contains.
		@return Size of the Datum*/
		std::uint32_t Size() const;

		/** Sets the datum's size.
		@param size The new Datum size.
		@except exception If no type has been assigned to this Datum
		@except exception If this datum is using external storage.*/
		void SetSize(std::uint32_t size);

		/* Clears the Datum, thus setting its Size to 0.
		@except exception If this Datum is using external storage.*/
		void Clear();

		/** Sets this Datum's value to an external location, unowned by
		this Datum. 
		@param data Pointer to the external data.
		@param size The size (number of elements) stored at the external location.
		@except exception If the Datum's type has already been set.
		*/
		void SetStorage(std::int32_t* data, std::uint32_t size);

		/** Sets this Datum's value to an external location, unowned by
		this Datum. 
		@param data Pointer to the external data.
		@param size The size (number of elements) stored at the external location.
		@except exception If the Datum's type has already been set.
		*/
		void SetStorage(float* data, std::uint32_t size);

		/** Sets this Datum's value to an external location, unowned by
		this Datum. 
		@param data Pointer to the external data.
		@param size The size (number of elements) stored at the external location.
		@except exception If the Datum's type has already been set.
		*/
		void SetStorage(glm::vec4* data, std::uint32_t size);

		/** Sets this Datum's value to an external location, unowned by
		this Datum. 
		@param data Pointer to the external data.
		@param size The size (number of elements) stored at the external location.
		@except exception If the Datum's type has already been set.
		*/
		void SetStorage(glm::mat4* data, std::uint32_t size);

		/** Sets this Datum's value to an external location, unowned by
		this Datum. 
		@param data Pointer to the external data.
		@param size The size (number of elements) stored at the external location.
		@except exception If the Datum's type has already been set.
		*/
		void SetStorage(std::string* data, std::uint32_t size);

		/** Sets this Datum's value to an external location, unowned by
		this Datum. 
		@param data Pointer to the external data.
		@param size The size (number of elements) stored at the external location.
		@except exception If the Datum's type has already been set.
		*/
		void SetStorage(RTTI** data, std::uint32_t size);

		/** Equality operator between two Datums.
		@param rhs The other datum to compare against.
		@return True if they are equivalent.*/
		bool operator==(const Datum& rhs) const;

		/** Scalar equality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is equivalent to rhs*/
		bool operator==(const std::int32_t& rhs) const;

		/** Scalar equality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is equivalent to rhs*/
		bool operator==(const float& rhs) const;

		/** Scalar equality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is equivalent to rhs*/
		bool operator==(const glm::vec4& rhs) const;

		/** Scalar equality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is equivalent to rhs*/
		bool operator==(const glm::mat4& rhs) const;

		/** Scalar equality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is equivalent to rhs*/
		bool operator==(const std::string& rhs) const;

		/** Scalar equality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is equivalent to rhs*/
		bool operator==(const RTTI* const& rhs) const;

		/** Scalar equality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is equivalent to rhs*/
		bool operator==(const Scope* const& rhs) const;

		/** Scalar inequality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is not equivalent to rhs*/
		bool operator!=(const Datum& rhs) const;

		/** Scalar inequality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is not equivalent to rhs*/
		bool operator!=(const std::int32_t& rhs) const;

		/** Scalar inequality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is not equivalent to rhs*/
		bool operator!=(const float& rhs) const;

		/** Scalar inequality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is not equivalent to rhs*/
		bool operator!=(const glm::vec4& rhs) const;

		/** Scalar inequality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is not equivalent to rhs*/
		bool operator!=(const glm::mat4& rhs) const;

		/** Scalar inequality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is not equivalent to rhs*/
		bool operator!=(const std::string& rhs) const;

		/** Scalar inequality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is not equivalent to rhs*/
		bool operator!=(const RTTI* const& rhs) const;

		/** Scalar inequality operator used to compare the first element 
		stored by this Datum.
		@param rhs Scalar value to compare against
		@return True if first element is not equivalent to rhs*/
		bool operator!=(const Scope* const& rhs) const;

		/** Sets the value at a given index.
		@param value Scalar value to assign
		@param index The index to assign
		@except exception If the index is out of the Datum's bounds.
		@except exception If there is a type mismatch*/
		void Set(std::int32_t value, std::uint32_t index = 0);

		/** Sets the value at a given index.
		@param value Scalar value to assign
		@param index The index to assign
		@except exception If the index is out of the Datum's bounds.
		@except exception If there is a type mismatch*/
		void Set(float value, std::uint32_t index = 0);

		/** Sets the value at a given index.
		@param value Scalar value to assign
		@param index The index to assign
		@except exception If the index is out of the Datum's bounds.
		@except exception If there is a type mismatch*/
		void Set(const glm::vec4& value, std::uint32_t index = 0);

		/** Sets the value at a given index.
		@param value Scalar value to assign
		@param index The index to assign
		@except exception If the index is out of the Datum's bounds.
		@except exception If there is a type mismatch*/
		void Set(const glm::mat4& value, std::uint32_t index = 0);

		/** Sets the value at a given index.
		@param value Scalar value to assign
		@param index The index to assign
		@except exception If the index is out of the Datum's bounds.
		@except exception If there is a type mismatch*/
		void Set(const std::string& value, std::uint32_t index = 0);

		/** Sets the value at a given index.
		@param value Scalar value to assign
		@param index The index to assign
		@except exception If the index is out of the Datum's bounds.
		@except exception If there is a type mismatch*/
		void Set(RTTI* value, std::uint32_t index = 0);

		/** Sets the value at a given index.
		@param value Scalar value to assign
		@param index The index to assign
		@except exception If the index is out of the Datum's bounds.
		@except exception If there is a type mismatch*/
		void Set(Scope* value, std::uint32_t index = 0);

		/** Scalar getters */
		std::int32_t& GetInteger(std::uint32_t index = 0);
		float& GetFloat(std::uint32_t index = 0);
		glm::vec4& GetVector(std::uint32_t index = 0);
		glm::mat4& GetMatrix(std::uint32_t index = 0);
		std::string& GetString(std::uint32_t index = 0);
		RTTI*& GetPointer(std::uint32_t index = 0);
		Scope*& GetScope(std::uint32_t index = 0);

		/** Const scalar getters */
		const std::int32_t& GetInteger(std::uint32_t index = 0) const;
		const float& GetFloat(std::uint32_t index = 0) const;
		const glm::vec4& GetVector(std::uint32_t index = 0) const;
		const glm::mat4& GetMatrix(std::uint32_t index = 0) const;
		const std::string& GetString(std::uint32_t index = 0) const;
		const RTTI* const& GetPointer(std::uint32_t index = 0) const;
		const Scope* const& GetScope(std::uint32_t index = 0) const;

		void SetFromString(const std::string& text, std::uint32_t index = 0);

		std::string ToString(std::uint32_t index = 0) const;

		void PushBack(std::int32_t value);
		void PushBack(float value);
		void PushBack(const glm::vec4& value);
		void PushBack(const glm::mat4& value);
		void PushBack(const std::string& value);
		void PushBack(RTTI* value);
		void PushBack(Scope* value); 

		bool Remove(std::uint32_t index);
		std::uint32_t Remove(Scope* value);

		Scope& operator[](std::uint32_t index);
		const Scope& operator[](std::uint32_t index) const;

	private:

		void PreAssignment(DatumType type);

		void PreGet(std::uint32_t index, DatumType type) const;

		void PreSetStorage();

		void PostSetStorage(DatumType type, std::uint32_t size);

		void PreSet(std::uint32_t index, DatumType type);

		void PrePushBack(DatumType type);

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
			Scope** sc;
			void* vp;
		} mData;
	};
}
