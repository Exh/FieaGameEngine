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

		explicit HashMap(std::uint32_t capacity = 13);

		~HashMap();

		HashMap(const HashMap& rhs) = default;

		HashMap& operator=(const HashMap& rhs) = default;

		Iterator Find(const TKey& key) const;

		Iterator Insert(const PairType& pair);

		TValue& operator[](const TKey& key);

		const TValue& operator[](const TKey& key) const;

		TValue& At(const TKey& key);

		const TValue& At(const TKey& key) const;

		void Remove(const TKey& key);

		void Clear();

		std::uint32_t Size() const;

		std::uint32_t Capacity() const;

		bool ContainsKey(const TKey& key) const;

		Iterator begin() const;

		Iterator end() const;

		class Iterator
		{
			friend class HashMap;

		public:

			Iterator();

			Iterator(const Iterator& rhs) = default;

			~Iterator() = default;

			Iterator& operator=(const Iterator& rhs) = default;

			Iterator& operator++();

			Iterator operator++(int);

			PairType& operator*();

			const PairType& operator*() const;

			bool operator==(const Iterator& rhs) const;

			bool operator!=(const Iterator& rhs) const;

		private:

			Iterator(const HashMap* owner, std::uint32_t bucket, typename ChainType::Iterator chainIterator);

			const HashMap* mOwner;
			std::uint32_t mBucket;
			typename ChainType::Iterator mChainIterator;
		};

	private:

		std::uint32_t GetNextNonEmptySListIndex(std::uint32_t currentIndex);

		void FillArray();

		ArrayType mArray;

		std::uint32_t mSize;

		std::uint32_t mCapacity;

		THash mHash;
	};
}

#include "HashMap.inl"
