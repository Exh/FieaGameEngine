#pragma once

#include <cstdint>

namespace FieaGameEngine
{
    template <typename T>
    class SList
    {
        public:

        class Iterator;
        struct Node;

        /************************************************************************/
        /** Initializes an empty list.                                          */
        /************************************************************************/
        SList();

        /************************************************************************/
        /** Destructor that ensures all heap data allocated by this object is   */
        /** deleted.                                                            */
        /************************************************************************/
        ~SList();

        /************************************************************************/
        /** Copy constructor that performs a deep copy of the list.             */
        /** @param rhs The SList that this will be copied from.                 */
        /************************************************************************/
        SList(const SList& rhs);

        /************************************************************************/
        /** Inserts the given item before the front of the list.                */
        /** @param item The new item that will be added to the list by value.   */
        /************************************************************************/
        void PushFront(const T& item);

        /************************************************************************/
        /** Removes the first item in the list.                                 */
        /************************************************************************/
        void PopFront();

        /************************************************************************/
        /** Appends an item to the end of the list.                             */
        /** @param item The item that will be added by value to the back of the */
        /** list by value.                                                      */
        /************************************************************************/
        void PushBack(const T& item);

        /************************************************************************/
        /** Returns true if the list contains no items.                         */
        /** @return true if the list is empty. false otherwise.                 */
        /************************************************************************/
        bool IsEmpty() const;

        /************************************************************************/
        /** Returns the item at the front of the list. Will throw an exception  */
        /** if the list is empty.                                               */
        /** @return A reference to the first item in the list.                  */
        /************************************************************************/
        T& Front();

        /************************************************************************/
        /** Returns the item at the front of the list. Will throw an exception  */
        /** if the list is empty.                                               */
        /** @return A reference to the first item in the list.                  */
        /************************************************************************/
        const T& Front() const;

        /************************************************************************/
        /** Returns the last item in the list. Will throw an exception if the   */
        /** list is empty.                                                      */
        /** @return A reference to the last item in the list.                   */
        /************************************************************************/
        T& Back();

        /************************************************************************/
        /** Returns the last item in the list. Will throw an exception if the   */
        /** list is empty.                                                      */
        /** @return A reference to the last item in the list.                   */
        /************************************************************************/
        const T& Back() const;

        /************************************************************************/
        /** Returns the number of items in the list.                            */
        /** @return The current size of the list.                               */
        /************************************************************************/
        std::uint32_t Size() const;

        /************************************************************************/
        /** Assignment operator implemented as a deep copy.                     */
        /** @param rhs The list to copy from.                                   */
        /** @return A reference to the this newly assigned list.                */
        /************************************************************************/
        SList& operator=(const SList& rhs); 

        /************************************************************************/
        /** Removes all items in the list.                                      */
        /************************************************************************/
        void Clear();

        Iterator begin();

        const Iterator begin() const;

        Iterator end();

        const Iterator end() const;

        void InsertAfter(const T& item,
                         const Iterator& iterator);

        Iterator Find(const T& value);

        const Iterator Find(const T& value) const;

        bool Remove(const T& value);

        bool RemoveAll(const T& value);

        class Iterator
        {
        public:

            friend SList;

            Iterator();

            ~Iterator();
            Iterator(const Iterator& rhs);

            bool operator==(const Iterator& rhs) const;
            bool operator!=(const Iterator& rhs) const;

            Iterator& operator=(const Iterator& rhs);

            Iterator& operator++();
            Iterator operator++(int post);

            T& operator*();
            const T& operator*() const;

        private:
            Iterator(const SList& owner,
                     Node* node);

            const SList* mOwner;
            Node* mNode;
        };

    private:

        void DeepCopy(const SList<T>& rhs);

        void RemoveNode(Node* previous,
                        Node* target);

        struct Node
        {
            Node();
            Node(const T&    item, 
                 Node*       next);

            T mItem;
            Node* mNext;
        };

        Node* mFront;
        Node* mBack;
        std::uint32_t mSize;
    };
}

#include "SList.inl"
