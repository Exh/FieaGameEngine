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
    void SList<T>::PushFront(const T& item)
    {
        mFront = new Node(item, mFront);

        mSize++;
    }

    template<typename T>
    void SList<T>::PopFront()
    {
        if (mFront != nullptr)
        {
            assert(mBack != nullptr);
            assert(mSize != 0);

            nodeToDelete = mFront;
            mFront = mFront->mNext;

            delete nodeToDelete;
            nodeToDelete = nullptr;
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
    SList<T>::Node::Node() :
        mItem(),
        mNext(nullptr)
    {

    }

    template<typename T>
    SList<T>::Node::Node(const T&    item,
                         const Node* next) :
        mItem(item),
        mNext(next)
    {

    }
}
