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