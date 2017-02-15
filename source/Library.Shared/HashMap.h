#pragma once

#include <utility>

#include "SList.h"
#include "Vector.h"

namespace FieaGameEngine
{
	template<typename TKey>
	class DefaultHashFunctor
	{
	public:
		DefaultHashFunctor() = default;
		virtual ~DefaultHashFunctor() = default;

		std::uint32_t operator()(const TKey& key) const;

		std::uint32_t operator()(const TKey* key) const;

	protected:

		std::uint32_t AdditiveHash(const std::uint8_t* data, std::uint32_t size) const;
	};

	template<typename TKey, typename TValue, typename THash = DefaultHashFunctor<TKey> >
	class HashMap
	{
		typedef std::pair<TKey, TValue> PairType;
		typedef SList<PairType> ChainType;
		typedef Vector<ChainType> ArrayType;

	public:

		class Iterator;

		/** Initializes a default hash map with an initial capacity if not specified.
			@param capacity The capacity of the hash map, (how many "buckets") */
		explicit HashMap(std::uint32_t capacity = 13);

		/** Deallocates all heap data and zeroizes members. */
		~HashMap();

		/** Default copy constructor.
			@param rhs Reference of HashMap to copy from.*/
		HashMap(const HashMap& rhs) = default;

		/** Default assignment operator.
			@param rhs Other HashMap to copy.
			@return reference to new hashmap.*/
		HashMap& operator=(const HashMap& rhs) = default;

		/** Searches the HashMap for an element with the same key that is provided.
			@param key Key to search for. 
			@return Iterator that points to the element with this same key.*/
		Iterator Find(const TKey& key) const;

		/** Places a Key,Value pair into the hash map. If an element with the 
			same key is already in the HashMap, its value will not be changed and no 
			new pair is inserted.
			@param pair Pair of values where first is a TKey value and second is
				a TValue value.
			@param inserted Output parameter that will be true if the pair was actually
				inserted. False otherwise (same key already exists.)
			@return an iterator that points to the newly inserted element, or the 
				already existing pair with the same key. 
		*/
		Iterator Insert(const PairType& pair, bool* inserted = nullptr);

		/** Returns a reference to the value associated with the provided key.
			If there is no key matching the provided key already in the hash map, 
			then a new pair element will be added to the HashMap with a default 
			constructed value.
			@param key Key to look up in hash map.
			@return Value associated with the provided key.*/
		TValue& operator[](const TKey& key);

		/** Returns a reference to the value associated with the provided key.
			If there is no key matching, an exception will be thrown.
			@param key Key to look up in hash map.
			@return Value associated with the provided key.*/
		const TValue& operator[](const TKey& key) const;

		/** Returns a reference to the value associated with the provided key.
			If there is no key matching, an exception will be thrown.
			@param key Key to look up in hash map.
			@return Value associated with the provided key.*/
		TValue& At(const TKey& key);

		/** Returns a reference to the value associated with the provided key.
			If there is no key matching, an exception will be thrown.
			@param key Key to look up in hash map.
			@return Value associated with the provided key.*/
		const TValue& At(const TKey& key) const;

		/** Removes an element from the hash map whose key matches the 
			provided key. If there is no matching key in the hash map, then
			nothing will happen.
			@param key Key of pair to remove.*/
		void Remove(const TKey& key);

		/** Removes all contained elements from the hash map. */
		void Clear();

		/** Returns the number of elements contained in the hash map. 
			@return Number of elements contained in the hash map. */
		std::uint32_t Size() const;

		/** Returns capacity of the hash map: how many buckets. 
			@return Capacity of hash map. */
		std::uint32_t Capacity() const;

		/** Returns true if the hash map already contains an element with the same 
			key as the key provided.
			@param key Key to match.
			@return true if key is contained in the list. Otherwise false. */
		bool ContainsKey(const TKey& key) const;

		/** Returns an iterator to the first element in the HashMap. If 
			no elements are in the HashMap, HashMap::end() will be returned.
			@return Iterator that references first element in the HashMap.
		*/
		Iterator begin() const;

		/** Returns an iterator to the end of the HashMap... or more specifically,
			returns an iterator that references an element that is not in the list.
		*/
		Iterator end() const;

		class Iterator
		{
			friend class HashMap;

		public:

			/** Default constructor for creating an iterator that does not reference
				a specific HashMap. */
			Iterator();

			/** Default copy constructor. */
			Iterator(const Iterator& rhs) = default;

			/** Default destructor. */
			~Iterator() = default;

			/** Default assignment operator. */
			Iterator& operator=(const Iterator& rhs) = default;

			/** Preincrement operator.
				@return reference to the newly altered iterator.*/
			Iterator& operator++();

			/** Postincrement operator.
				@return copy of the previous state of the Iterator.*/
			Iterator operator++(int);

			/** Dereferences the element that this iterator is referencing. 
				Will throw an exception if this iterator has not been assigned 
				or if is pointing to HashMap::end().
				@return Reference to Key/Value pair that iterator is pointing to.*/
			PairType& operator*();

			/** Dereferences the element that this iterator is referencing. 
				Will throw an exception if this iterator has not been assigned 
				or if is pointing to HashMap::end().
				@return Reference to Key/Value pair that iterator is pointing to. */
			const PairType& operator*() const;

			/** Equality operator for comparing two iterators.
				@param rhs Other Iterator to compare against.
				@return true is the iterators are referencing the same element. */
			bool operator==(const Iterator& rhs) const;

			/** Inequality operator for comparing two iterators.
				@param rhs Other Iterator to compare against.
				@return true is the iterators are referencing different elements. */
			bool operator!=(const Iterator& rhs) const;

		private:

			Iterator(const HashMap* owner, std::uint32_t bucket, typename ChainType::Iterator chainIterator);

			const HashMap* mOwner;
			std::uint32_t mBucket;
			typename ChainType::Iterator mChainIterator;
		};

	private:

		std::uint32_t GetNextNonEmptySListIndex(std::uint32_t currentIndex) const;

		void FillArray();

		ArrayType mArray;

		std::uint32_t mSize;

		std::uint32_t mCapacity;

		THash mHash;
	};
}

#include "HashMap.inl"
