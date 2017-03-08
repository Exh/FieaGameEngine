#include <assert.h>
#include <windows.h>

namespace FieaGameEngine
{
    template<typename T>
    SList<T>::SList() :
        mFront(nullptr),
        mBack(nullptr),
        mSize(0)
    {

    }

    template<typename T>
    SList<T>::~SList()
    {
        Clear();
    }

    template<typename T>
    SList<T>::SList(const SList<T>& rhs) :
        mFront(nullptr),
        mBack(nullptr),
        mSize(0)
    {
        DeepCopy(rhs);
    }

	template<typename T>
	SList<T>::SList(SList&& rhs) :
		mFront(rhs.mFront),
		mBack(rhs.mBack),
		mSize(rhs.mSize)
	{
		rhs.mFront = nullptr;
		rhs.mBack = nullptr;
		rhs.mSize = 0U;
	}

	template<typename T>
	SList<T>& SList<T>::operator=(SList<T>&& rhs)
	{
		Clear();

		mFront = rhs.mFront;
		mBack = rhs.mBack;
		mSize = rhs.mSize;

		mFront = nullptr;
		mBack = nullptr;
		mSize = 0U;
	}

    template<typename T>
    typename SList<T>::Iterator SList<T>::PushFront(const T& item)
    {
        Node* newNode = new Node(item, mFront);

        if (IsEmpty())
        {
            mBack = newNode;
        }

        mFront = newNode;
        mSize++;

        return Iterator(*this, mFront);
    }

    template<typename T>
    void SList<T>::PopFront()
    {
        if (!IsEmpty())
        {
            Node* nodeToDelete = mFront;
            mFront = mFront->mNext;

            delete nodeToDelete;
            nodeToDelete = nullptr;

            mSize--;
            
            // If list is empty, then set mBack to nullptr.
            if (mSize == 0)
            {
                assert(mFront == nullptr);
                mBack = nullptr;
            }
        }
    }

    template<typename T>
    typename SList<T>::Iterator SList<T>::PushBack(const T& item)
    {
        if (!IsEmpty())
        {
            // The list is not empty, so make the last node's 
            // next pointer point to the new node, and update the 
            // mBack member to point to the new node.
            mBack->mNext = new Node(item, nullptr);
            mBack = mBack->mNext;
        }
        else
        {
            // The list is empty, so the new node that will be added
            // will be both the front and the back.
            mFront = new Node(item, nullptr);
            mBack = mFront;
        }

        mSize++;

        return Iterator(*this, mBack);
    }

    template<typename T>
    bool SList<T>::IsEmpty() const
    {
#ifdef _DEBUG
        if (mSize == 0)
        {
            assert(mFront == nullptr);
            assert(mBack == nullptr);
        }
        else
        {
            assert(mFront != nullptr);
            assert(mBack != nullptr);
        }
#endif
        return (mSize == 0);
    }

    template<typename T>
    T& SList<T>::Front()
    {
        return const_cast<T&>(const_cast<const SList<T>*>(this)->Front());
    }

    template<typename T>
    const T& SList<T>::Front() const
    {
        if (IsEmpty())
        {
            throw std::exception("Cannot get front of empty list.");
        }
        else
        {
            return mFront->mItem;
        }
    }

    template<typename T>
    T& SList<T>::Back()
    {
        return const_cast<T&>(const_cast<const SList<T>*>(this)->Back());
    }

    template<typename T>
    const T& SList<T>::Back() const
    {
        if (IsEmpty())
        {
            throw std::exception("Cannot get back of empty list.");
        }
        else
        {
            return mBack->mItem;
        }
    }

    template<typename T>
    std::uint32_t SList<T>::Size() const
    {
        return mSize;
    }

    template<typename T>
    SList<T>& SList<T>::operator=(const SList<T>& rhs)
    {
        if (this != &rhs)
        {
            Clear();
            DeepCopy(rhs);
        }

        return *this;
    }

    template<typename T>
    void SList<T>::Clear()
    {
        Node* current = mFront;

        while (current != nullptr)
        {
            current = current->mNext;
            PopFront();
        }

        assert(mSize == 0);
        assert(mFront == nullptr);
        assert(mBack == nullptr);
    }

    template<typename T>
    typename SList<T>::Iterator SList<T>::begin() const
    {
        return Iterator(*this, mFront);
    }

    template<typename T>
    typename SList<T>::Iterator SList<T>::end() const
    {
        return Iterator(*this, nullptr);
    }

    template<typename T>
    typename SList<T>::Iterator SList<T>::InsertAfter(const T& item,
                                                      const Iterator& iterator)
    {
        if (iterator.mOwner != this)
        {
            // This could possibly be ignored instead, but this is 
            // probably something the user would never want to do, so 
            // might as well make it obvious.
            throw std::exception("Attempting to insert item using iterator of a different list.");
        }

        if (iterator == end())
        {
            PushBack(item);
            return Iterator(*this, mBack);
        }
        else
        {
            Node* newNode = new Node();
            newNode->mItem = item;
            newNode->mNext = iterator.mNode->mNext;
            iterator.mNode->mNext = newNode;

            mSize++;

            return Iterator(*this, newNode);
        }
    }

    template<typename T>
    typename SList<T>::Iterator SList<T>::Find(const T& value)
    {
        return const_cast<const SList<T>*>(this)->Find(value);
    }

    template<typename T>
    typename const SList<T>::Iterator SList<T>::Find(const T& value) const
    {
        Node* currentNode = mFront;

        while (currentNode != nullptr)
        {
            if (currentNode->mItem == value)
            {
                break;
            }

            currentNode = currentNode->mNext;
        }

        return (currentNode == nullptr) ? end() : Iterator(*this, currentNode);
    }

    template<typename T>
    bool SList<T>::Remove(const T& value)
    {
        // This remove will remove the first item from the list whose
        // value matches the provided value.
        Node* currentNode = mFront;
        Node* previousNode = nullptr;

        while (currentNode != nullptr)
        {
            if (currentNode->mItem == value)
            {
                RemoveNode(previousNode, currentNode);
                break;
            }

            previousNode = currentNode;
            currentNode = currentNode->mNext;
        }

        return (currentNode != nullptr);
    }

    template<typename T>
    bool SList<T>::RemoveAll(const T& value)
    {
        // One way of implementing this function could be by 
        // calling Remove() with the same value until a false
        // is returned, but this is slow because Remove()
        // is O(n) and it would be called m times where m is the 
        // number of elements equal to value. Thus, remove all
        // would be O(n^2).

        // The following implementation duplicates some code of Remove()
        // but this allows O(n) time for removing all.

        bool found = false;
        Node* currentNode = mFront;
        Node* previousNode = nullptr;
        Node* nextNode = nullptr;

        while (currentNode != nullptr)
        {
            nextNode = currentNode->mNext;

            if (currentNode->mItem == value)
            {
                RemoveNode(previousNode, currentNode);
                found = true;

                // The current node was just removed, so it can't 
                // be used as a previous node.
                currentNode = nextNode;
            }
            else 
            {
                previousNode = currentNode;
                currentNode = currentNode->mNext;
            }
        }

        return found;
    }

    template<typename T>
    void SList<T>::DeepCopy(const SList<T>& rhs)
    {
        for (auto& value : rhs)
        {
            PushBack(value);
        }
    }

    template<typename T>
    void SList<T>::RemoveNode(Node* previous,
                              Node* target)
    {
        assert(target != nullptr);

        if (target == mFront &&
            target == mBack)
        {
            assert(mSize == 1);
            mFront = nullptr;
            mBack = nullptr;
        }
        else if (target == mFront)
        {
            assert(previous == nullptr);
            assert(target != mBack);
            mFront = target->mNext;
        }
        else if (target == mBack)
        {
            assert(target != mFront);
            assert(target->mNext == nullptr);
            previous->mNext = nullptr;
            mBack = previous;
        }
        else 
        {
            assert(mSize > 2);
            previous->mNext = target->mNext;
        }

        mSize--;
        delete target;
        target = nullptr;
    }

    template<typename T>
    SList<T>::Iterator::Iterator() :
        mOwner(nullptr),
        mNode(nullptr)
    {
    
    }

    template<typename T>
    SList<T>::Iterator::Iterator(const SList& owner,
                                 Node* node) :
        mOwner(&owner),
        mNode(node)
    {
    
    }

    template<typename T>
    SList<T>::Iterator::~Iterator()
    {

    }

    template<typename T>
    SList<T>::Iterator::Iterator(const Iterator& rhs) :
        mOwner(rhs.mOwner),
        mNode(rhs.mNode)
    {

    }

    template<typename T>
    bool SList<T>::Iterator::operator==(const Iterator& rhs) const
    {
        return mOwner == rhs.mOwner &&
            mNode == rhs.mNode;
    }

    template<typename T>
    bool SList<T>::Iterator::operator!=(const Iterator& rhs) const
    {
        return !operator==(rhs);
    }

    template<typename T>
    typename SList<T>::Iterator& SList<T>::Iterator::operator=(const Iterator& rhs)
    {
        if (this != &rhs)
        {
            mNode = rhs.mNode;
            mOwner = rhs.mOwner;
        }

        return *this;
    }

    template<typename T>
    typename SList<T>::Iterator& SList<T>::Iterator::operator++()
    {
        if (mNode != nullptr)
        {
            mNode = mNode->mNext;
        }

        return *this;
    }

    template<typename T>
    typename SList<T>::Iterator SList<T>::Iterator::operator++(int post)
    {
        UNREFERENCED_PARAMETER(post);

        Iterator previous = *this;
        operator++();
        return previous;
    }

    template<typename T>
    T& SList<T>::Iterator::operator*()
    {
        return const_cast<T&>(static_cast<const Iterator*>(this)->operator*());
    }

    template<typename T>
    const T& SList<T>::Iterator::operator*() const
    {
        if (mOwner == nullptr)
        {
            throw std::exception("Cannot dereference iterator with no assigned owner list.");
        }

        if (mNode == nullptr)
        {
            throw std::exception("Cannot dereference end iterator.");
        }

        return mNode->mItem;
    }

    template<typename T>
    SList<T>::Node::Node() :
        mItem(),
        mNext(nullptr)
    {

    }

    template<typename T>
    SList<T>::Node::Node(const T&    item,
                         Node*       next) :
        mItem(item),
        mNext(next)
    {

    }
}
