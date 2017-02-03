#pragma once

#include <cstdint>
#include <assert.h>
#include <string>

namespace FieaGameEngine
{

#pragma region DefaultHashFunctorMethods

	template<typename TKey>
	std::uint32_t DefaultHashFunctor<TKey>::operator()(const TKey& key) const
	{
		return AdditiveHash(reinterpret_cast<const std::uint8_t*>(&key), sizeof(TKey));
	}

	template<typename TKey>
	std::uint32_t DefaultHashFunctor<TKey>::operator()(const TKey* key) const
	{
		return AdditiveHash(reinterpret_cast<const std::uint8_t*>(key), sizeof(TKey));
	}

	template<>
	inline std::uint32_t DefaultHashFunctor<std::string>::operator()(const std::string& key) const
	{
		return AdditiveHash(reinterpret_cast<const std::uint8_t*>(key.c_str()),  key.length());
	}

	template<typename TKey>
	std::uint32_t DefaultHashFunctor<TKey>::AdditiveHash(const std::uint8_t* data, std::uint32_t size) const
	{
		static const std::uint8_t C = 13;
		std::uint32_t hash = 0;

		for (std::uint32_t i = 0; i < size; i++)
		{
			hash += C + data[i];
		}

		return hash;
	}

#pragma endregion

#pragma region HashMapMethods

	template<typename TKey, typename TValue, typename THash>
	HashMap<TKey, TValue, THash>::HashMap(std::uint32_t capacity) : 
		mSize(0),
		mCapacity(capacity)
	{
		FillArray();
	}

	template<typename TKey, typename TValue, typename THash>
	HashMap<TKey, TValue, THash>::~HashMap()
	{
		mSize = 0;
		mCapacity = 0;
	}

	template<typename TKey, typename TValue, typename THash>
	typename HashMap<TKey, TValue, THash>::Iterator HashMap<TKey, TValue, THash>::Find(const TKey& key) const
	{
		std::uint32_t index = mHash(key) % mCapacity;

		for (auto it = mArray[index].begin(); it != mArray[index].end(); ++it)
		{
			if ((*it).first == key)
			{
				return Iterator(this, index, it);
			}
		}

		return end();
	}

	template<typename TKey, typename TValue, typename THash>
	typename HashMap<TKey, TValue, THash>::Iterator HashMap<TKey, TValue, THash>::Insert(const PairType& pair)
	{
		std::uint32_t index = mHash(pair.first) % mCapacity;

		for (auto it = mArray[index].begin(); it != mArray[index].end(); ++it)
		{
			if ((*it).first == pair.first)
			{
				return Iterator(this, index, it);
			}
		}

		// If the same key was not found, then we can add a new key.
		mSize++;
		return Iterator(this, index, mArray[index].PushBack(pair));
	}

	template<typename TKey, typename TValue, typename THash>
	TValue& HashMap<TKey, TValue, THash>::operator[](const TKey& key)
	{
		Iterator it = Find(key);

		if (it == end())
		{
			it = Insert(std::pair<TKey, TValue>(key, TValue()));
		}

		return (*it).second;
	}

	template<typename TKey, typename TValue, typename THash>
	const TValue& HashMap<TKey, TValue, THash>::operator[](const TKey& key) const
	{
		Iterator it = Find(key);

		if (it == end())
		{
			throw std::exception("Key not found in HashMap.");
		}
		return (*it).second;
	}

	template<typename TKey, typename TValue, typename THash>
	TValue& HashMap<TKey, TValue, THash>::At(const TKey& key)
	{
		return const_cast<TValue&>(const_cast<const HashMap*>(this)->operator[](key));
	}

	template<typename TKey, typename TValue, typename THash>
	const TValue& HashMap<TKey, TValue, THash>::At(const TKey& key) const
	{
		return operator[](key);
	}

	template<typename TKey, typename TValue, typename THash>
	void HashMap<TKey, TValue, THash>::Remove(const TKey& key)
	{
		std::uint32_t index = mHash(key) % mCapacity;
		ChainType& chain = mArray[index];
		ChainType::Iterator it = chain.begin();

		for (auto& pair : chain)
		{
			if (pair.first == key)
			{
				chain.Remove(pair);
				--mSize;
				break;
			}
		}
	}

	template<typename TKey, typename TValue, typename THash>
	void HashMap<TKey, TValue, THash>::Clear()
	{
		mArray.Clear();
		mSize = 0;
		FillArray();
	}

	template<typename TKey, typename TValue, typename THash>
	std::uint32_t HashMap<TKey, TValue, THash>::Size() const
	{
		return mSize;
	}

	template<typename TKey, typename TValue, typename THash>
	std::uint32_t HashMap<TKey, TValue, THash>::Capacity() const
	{
		return mCapacity;
	}

	template<typename TKey, typename TValue, typename THash>
	bool HashMap<TKey, TValue, THash>::ContainsKey(const TKey& key) const
	{
		return Find(key) != end();
	}

	template<typename TKey, typename TValue, typename THash>
	typename HashMap<TKey, TValue, THash>::Iterator HashMap<TKey, TValue, THash>::begin() const
	{
		if (mSize != 0)
		{
			//for (auto& chain : mArray)
			for (std::uint32_t i = 0; i < mCapacity; i++)
			{
				if (!mArray[i].IsEmpty())
				{
					return Iterator(this, i, mArray[i].begin());
				}
			}
		}

		return end();
	}

	template<typename TKey, typename TValue, typename THash>
	typename HashMap<TKey, TValue, THash>::Iterator HashMap<TKey, TValue, THash>::end() const
	{
		return Iterator(this, mCapacity, ChainType::Iterator());
	}

	template<typename TKey, typename TValue, typename THash>
	void HashMap<TKey, TValue, THash>::FillArray()
	{
		if (mArray.IsEmpty())
		{
			mArray.Reserve(mCapacity);

			for (std::uint32_t i = 0; i < mCapacity; i++)
			{
				mArray.PushBack(ChainType());
			}
		}
	}

	template<typename TKey, typename TValue, typename THash>
	std::uint32_t HashMap<TKey, TValue, THash>::GetNextNonEmptySListIndex(std::uint32_t currentIndex) const
	{
		assert(currentIndex >= 0);
		assert(currentIndex <= mCapacity);

		currentIndex++;
		if (currentIndex > mCapacity)
		{
			currentIndex = mCapacity;
		}

		while (currentIndex != mCapacity)
		{
			if (!mArray[currentIndex].IsEmpty())
			{
				break;
			}

			currentIndex++;
		}

		return currentIndex;
	}

#pragma endregion

#pragma region IteratorMethods

	template<typename TKey, typename TValue, typename THash>
	HashMap<TKey, TValue, THash>::Iterator::Iterator() :
		mOwner(nullptr),
		mBucket(0)
	{
		
	}

	template<typename TKey, typename TValue, typename THash>
	HashMap<TKey, TValue, THash>::Iterator::Iterator(const HashMap* owner, std::uint32_t bucket, typename ChainType::Iterator chainIterator) :
		mOwner(owner),
		mBucket(bucket),
		mChainIterator(chainIterator)
	{
	
	}

	template<typename TKey, typename TValue, typename THash>
	typename HashMap<TKey, TValue, THash>::Iterator& HashMap<TKey, TValue, THash>::Iterator::operator++()
	{
		if (mOwner == nullptr)
		{
			throw std::exception("Cannot increment an iterator that is not associated with a HashMap.");
		}

		if (mBucket < mOwner->mCapacity)
		{
			if (mChainIterator != ChainType::Iterator())
			{
				mChainIterator++;

				if (mChainIterator == mOwner->mArray[mBucket].end())
				{
					mBucket = mOwner->GetNextNonEmptySListIndex(mBucket);

					if (mBucket != mOwner->mCapacity)
					{
						//mChainIterator = (*mOwner)[mBucket].begin();
						mChainIterator = mOwner->mArray[mBucket].begin();
					}
					else 
					{
						mChainIterator = ChainType::Iterator();
					}
				}
			}
		}

		return *this;
	}

	template<typename TKey, typename TValue, typename THash>
	typename HashMap<TKey, TValue, THash>::Iterator HashMap<TKey, TValue, THash>::Iterator::operator++(int)
	{
		Iterator previous = *this;
		operator++();
		return previous;
	}

	template<typename TKey, typename TValue, typename THash>
	typename HashMap<TKey, TValue, THash>::PairType& HashMap<TKey, TValue, THash>::Iterator::operator*()
	{
		return const_cast<PairType&>(const_cast<const Iterator*>(this)->operator*());
	}

	template<typename TKey, typename TValue, typename THash>
	const typename HashMap<TKey, TValue, THash>::PairType& HashMap<TKey, TValue, THash>::Iterator::operator*() const
	{
		if (mOwner == nullptr)
		{
			throw std::exception("Cannot dereference unassigned iterator.");
		}
		if (mBucket == mOwner->mCapacity)
		{
			assert(mChainIterator == ChainType::Iterator());
			throw std::exception("Cannot dereference end iterator.");
		}

		return *mChainIterator;
	}

	template<typename TKey, typename TValue, typename THash>
	bool HashMap<TKey, TValue, THash>::Iterator::operator==(const Iterator& rhs) const
	{
		return mOwner == rhs.mOwner &&
			mBucket == rhs.mBucket &&
			mChainIterator == rhs.mChainIterator;
	}

	template<typename TKey, typename TValue, typename THash>
	bool HashMap<TKey, TValue, THash>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !operator==(rhs);
	}

#pragma endregion

}
