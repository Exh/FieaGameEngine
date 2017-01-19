#pragma once

//***************
// Assignment 01
//***************
//When passing pointers into list. do not "delete" the node data of type T

// Use std::uint32 for size

// operator=
// Make sure that this != &rhs, first line
// last statement should be a return *this;

// Copy contructor 
// Initialize in constructor list, the data members.
// Walk through the rhs nodes and push back them onto the lhs list.

// Maybe make a node constructor that can take a Data and nextpointer.

// Destructor should go through the list and delete all of the of the nodes.

// Make helper code that shares the same code between copy constructor and operator=

// operator= should delete the nodes it already has before copying the new nodes.
// you should check in the unit tests to make sure that the copies are exactly equivalent.
// you can use the destructive popfront/popback for testing in this case because the current SList is crappy.

// Write unit test for each method.

// Front() should throw an exception if there is nothing in the list.

// Paul is okay with PopFront() returning void. Using Front() to get the data before using PopFront().

// #include <excpetion> for exceptions

// Assert::ExpectException for testing exceptions like on Front();

// auto expression = [&intList] {intList.Front(); };
// ^ use expression as a function pointer?

// Do a unit test for each method, but you dont have to test methods thoroughly that 
// you have already tested in another method.

// Only required doxygen comments on public interface / members.
// Don't document unit tests.

// Front() and Back() should have const and nonconst versions 

// Test with at least 3 data types.
// primitive
// pointer
// Foo (custom class)
// Divide each test into 3 sections (ie int/int*/Foo)


// Rule of 3
// If you should provide a constructor, then you should supply destructor, copy constructor, and operator=

//***************
// Assignment 01
//***************

// foreach loops expect a lowercase begin() and end().
// 
// for (SList<int>::Iterator it = list.begin(); it != list.end(); it++)
//
// Composition: my class is composed of other data. It owns this other data.
//  has-a relationship.

// Aggregation: form of composition where container does not own contained data.


/**
class Iterator
{

    Iterator();

    Iterator(const SList& owner, Node* node);

    // when the iterator is equivalent to end() and this is called again, then 
    // either (1) an exception can be thrown or (2) do nothing.
    operator++();

    // These operators will need to check if the iterators are made from the same SList
    // so like this.mOwner == rhs.mOwner.
    operator==();
    operator!=();

    Iterator(&Iterator rhs);
    operator=();
    operator*();

    // You could have a destructor that just nulls out the data members
    ~Iterator();

private:
    Node* mNode;
    SList* mOwner;
};
*/

// InsertAfter should be O(1) but Find() should be O(n)
// Could you envision a way of letting the user offer their own equality function if 
// there is no operator== for the class that they are working with.

// operator* should have const and const*
// dont have to do decrement or pointer arithmetic.

// Remove could possibly return a bool
// Find should not fire an exception, but rather it should return an iterator to end().

// do not use the keyword default.

// Unit test 
// increment()
// decrement()
// insert()
// after()

