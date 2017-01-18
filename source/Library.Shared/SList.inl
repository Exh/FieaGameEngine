#include <assert.h>

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
    void SList<T>::PushFront(const T& item)
    {
        mFront = new Node(item, mFront);

        mSize++;
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
    void SList<T>::PushBack(const T& item)
    {
        if (IsEmpty())
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
        return const_cast<T&>(static_cast<const SList<T>*>(this)->Front());
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
        return const_cast<T&>(static_cast<const SList<T>*>(this)->Back());
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
    void SList<T>::DeepCopy(const SList<T>& rhs)
    {
        Node* current = rhs.mFront;

        while (current != nullptr)
        {
            PushBack(current->mItem);
            current = current->mNext;
        }
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
