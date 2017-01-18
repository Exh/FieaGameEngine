#pragma once

#include <cstdint>

namespace FieaGameEngine
{
    template <typename T>
    class SList
    {
    public:

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
        SList(const SList<T>& rhs);

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
        SList<T>& operator=(const SList<T>& rhs); 

        /************************************************************************/
        /** Removes all items in the list.                                      */
        /************************************************************************/
        void Clear();

    private:

        void DeepCopy(const SList<T>& rhs);

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
