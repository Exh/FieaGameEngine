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
        Iterator PushFront(const T& item);

        /************************************************************************/
        /** Removes the first item in the list.                                 */
        /************************************************************************/
        void PopFront();

        /************************************************************************/
        /** Appends an item to the end of the list.                             */
        /** @param item The item that will be added by value to the back of the */
        /** list by value.                                                      */
        /************************************************************************/
        Iterator PushBack(const T& item);

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

        /************************************************************************/
        /** Returns an iterator that points to the first element in the list.   */
        /** Will return the same value as end() if the list is empty.           */
        /** @return iterator at the first element in the list.                  */
        /************************************************************************/
        Iterator begin() const;

        /************************************************************************/
        /** Returns an iterator past the end of the list. This iterator should  */
        /** not be dereferenced.                                                */
        /** @return iterator past the last element in the list.                 */
        /************************************************************************/
        Iterator end() const;

        /************************************************************************/
        /** Places an element into the list at the position one past the given  */
        /** iterator. If an iterator equivalent to SList::end() is passed, the  */
        /** element will be added to the back of the list.                      */
        /** @param item element to place into the list.                         */
        /** @param iterator position in list to insert new element after        */
        /** @return iterator that points to the newly inserted item             */
        /************************************************************************/
        Iterator InsertAfter(const T& item,
                             const Iterator& iterator);

        /************************************************************************/
        /** Returns an iterator that references the first element found in the  */
        /** list that is equivalent to the given value. Returns SList::end() if */
        /** there is no element that is equivalent to the given value.          */
        /** @param value element to match                                       */
        /************************************************************************/
        Iterator Find(const T& value);

        /************************************************************************/
        /** Returns an iterator that references the first element found in the  */
        /** list that is equivalent to the given value. Returns SList::end() if */
        /** there is no element that is equivalent to the given value.          */
        /** @param value element to match                                       */
        /************************************************************************/
        const Iterator Find(const T& value) const;

        /************************************************************************/
        /** Removes the first element from the list that is equivalent to the   */
        /** given value.                                                        */
        /** @param value data to match.                                         */
        /** @return true if an element was removed. false otherwise.            */
        /************************************************************************/
        bool Remove(const T& value);

        /************************************************************************/
        /** Removes all elements from the list that are equivalent to the       */
        /** provided value.                                                     */
        /** @param value data to match.                                         */
        /** @return true if at least one element was removed. false otherwise.  */
        /************************************************************************/
        bool RemoveAll(const T& value);

        class Iterator
        {
        public:

            friend SList;

            /************************************************************************/
            /** Constructs an iterator that belongs to no SList and references no   */
            /** data.                                                               */
            /************************************************************************/
            Iterator();

            /************************************************************************/
            /** Essentially the default destructor.                                 */
            /************************************************************************/
            ~Iterator();

            /************************************************************************/
            /** Constructs an iterator given another iterator. Basically the        */
            /** default copy constructor.                                           */
            /************************************************************************/
            Iterator(const Iterator& rhs);

            /************************************************************************/
            /** Compares two iterators for equivalence.                             */
            /** @return true if both iterators point to the same data contained by  */
            /** the same list.                                                      */
            /************************************************************************/
            bool operator==(const Iterator& rhs) const;

            /************************************************************************/
            /** Compares two iterators for inequivalence.                           */
            /** @return false if both iterators point to the same data contained by */
            /** the same list. true otherwise.                                      */
            /************************************************************************/
            bool operator!=(const Iterator& rhs) const;

            /************************************************************************/
            /** Assigns this iterator to a given different iterator. The two        */
            /** iterators will point to the same data and be equivalent after this. */
            /************************************************************************/
            Iterator& operator=(const Iterator& rhs);

            /************************************************************************/
            /** Increments this iterator to point to the next element in the list.  */
            /** @return a reference to the newly adjusted iterator.                 */
            /************************************************************************/
            Iterator& operator++();

            /************************************************************************/
            /** Increments this iterator to point to the next element in the list   */
            /** and returns a copy of the iterator as it was before incrementing    */
            /** it.                                                                 */
            /** @return a reference to the newly adjusted iterator.                 */
            /************************************************************************/
            Iterator operator++(int post);

            /************************************************************************/
            /** Dereferences the iterator, returning a reference to the data which  */
            /** the iterator is currently pointing at.                              */
            /** @return reference to current data                                   */
            /************************************************************************/
            T& operator*();

            /************************************************************************/
            /** Dereferences the iterator, returning a reference to the data which  */
            /** the iterator is currently pointing at.                              */
            /** @return reference to current data                                   */
            /************************************************************************/
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
