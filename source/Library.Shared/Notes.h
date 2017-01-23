#pragma once

//***************
// Assignment 02
//***************

/*
When passing pointers into list. do not "delete" the node data of type T

Use std::uint32 for size

operator=
Make sure that this != &rhs, first line
last statement should be a return *this;

Copy contructor
Initialize in constructor list, the data members.
Walk through the rhs nodes and push back them onto the lhs list.

Maybe make a node constructor that can take a Data and nextpointer.

Destructor should go through the list and delete all of the of the nodes.

Make helper code that shares the same code between copy constructor and operator=

operator= should delete the nodes it already has before copying the new nodes.
you should check in the unit tests to make sure that the copies are exactly equivalent.
you can use the destructive popfront / popback for testing in this case because the current SList is crappy.

Write unit test for each method.

Front() should throw an exception if there is nothing in the list.

Paul is okay with PopFront() returning void.Using Front() to get the data before using PopFront().

#include <excpetion> for exceptions

Assert::ExpectException for testing exceptions like on Front();

auto expression = [&intList] {intList.Front(); };
^ use expression as a function pointer ?

Do a unit test for each method, but you dont have to test methods thoroughly that
you have already tested in another method.

Only required doxygen comments on public interface / members.
Don't document unit tests.

Front() and Back() should have const and nonconst versions

Test with at least 3 data types.
primitive
pointer
Foo(custom class)
Divide each test into 3 sections(ie int / int* / Foo)


Rule of 3
If you should provide a constructor, then you should supply destructor, copy constructor, and operator=

*/

//***************
// Assignment 03
//***************

/*
foreach loops expect a lowercase begin() and end().

for (SList<int>::Iterator it = list.begin(); it != list.end(); it++)

Composition: my class is composed of other data.It owns this other data.
    has - a relationship.

    Aggregation : form of composition where container does not own contained data.
*/

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

/*
InsertAfter should be O(1) but Find() should be O(n)
Could you envision a way of letting the user offer their own equality function if
there is no operator== for the class that they are working with.

operator* should have const and const*
don't have to do decrement or pointer arithmetic.

Remove could possibly return a bool
Find should not fire an exception, but rather it should return an iterator to end().

do not use the keyword default.

Unit test
increment()
decrement()
insert()
after()

refactor the copy constructor to use iterator

QUESTIONS:
(1) Can we make SList a friend of iterator. [YES]
(2) Do iterators return by end() and begin() return by value? [YES]
(3) do begin() end() Find() need const and nonconst versions? [YES?]
(4) Remove looks for first item in list? [YES]
(5) What is the reasoning behind writing "typename" before dependent types in templated methods
(6) Should InsertAfter throw an exception when inserting after the end iterator or
    should it place it after the last element in the list? [PUSHBACK]
(7) Can we have one iterator test instead of tests for each iterator method? [NO]

    [X] Refactor pushfront and pushback should return iterators!!!
    [X] InsertAfter should return an iterator to the newly inserted item.
    [X] REFACTOR operator= and similar to use range based for loops
    [ ] Use <random> std::_randomDevice _randomEngine for random number generation.
    [ ] Refactor tests to use variables instead of literals.
    [X] Check the iterator being passed into InsertAfter to make sure that it is owned by the list.
*/

    for (const Iterator it = begin(); it != end(); i++)
    {
        PushBack(*it)
    }

    // is equivalent to :

    for (auto& value : rhs)
    {
        PushBack(value);
    }


//***************
// Assignment 04
//***************

/*
    Vector, could implement end() as an index one past the last element of the list. so size of the list.
    Don't use -1 to represent end()

    Best fit and first fit - algorithms for allocating heap data. 
    Size member for tracking count of items currently in the list.
    Capacity for tracking the current amount of items the list can hold before a realloc is necessary.

    When removing items from a vector, there is no need to clear the values at the last index.
*/

    // Vector should behave in the same way that SList does in the fact that:
    int a = 10;
    vector<int> v; 
    v.PushBack(a);
    a = 20; 
    // v's data should not change

/*
    Placement new: constructs an object on a pre-allocated buffer.
    Can work against heap + stack allocated memory.
*/

    const int MaxPixels = 100;
    Pixel* buffer = malloc(MaxPixels * sizeof(Pixel));

    Pixel* pixel = new (buffer) Pixel();
    // new in this case, does not call malloc. It just calls the constructor 
    // any constructor can be invoked with placement new
/*
    You cannot call the constructor explicitly outside of new, but you can call the 
    destructor explicitly, and you will have to. Why default construct an object that will only be 
    replaced anyway? It is a waste of time. Expensive.

    Resize() or Reserve()
    C++ Standard:
    Reserve() does one big alloc. Assigned capacity but not size. (so just malloc)
    Resize() does both a regular new? Assigns capacity AND size.


    Shrink() reduces size. ShrinkToFit() would shrink capacity to size.

    When calling Remove()...

    When resizing vectors capacity and you need to move all of the Foos into another contiguous memory array,
    Then loop through the original array and invoke the destructor on it.
    Q: Why can't we memcpy the data into new array when reserving?

    Throw an exception when accessing an out of bounds index. (best idea. C++  standard lets you access out of bounds stuff).

    For operator== on vector, it doesn't really matter if the capacity is different if they are logically the same.
    This is a design decision... do vectors need to have the same capacity to be considered equivalent.

    operator[] for copying.

    functors are objects that contain an operator() and be called like a function.
    can use std::function 

    CASTING:

    const_cast works on pointers, references, and values.

    static_cast is not a c style cast.
    You can down-cast with static cast. Only works with references, pointers, and objects.
    Compile time checking.
    Upcasting is always acceptable.
    The opposite is not always true. The compiler will make sure that the casted types are
    in the same heirarchy. cast primitives using static cast.

    dynamic cast only works with references and pointers. Does both compile time and run
    time checking. if you dynamic cast a pointer and it is not a valid type conversion, it will
    return a nullptr. If you dynamic cast a reference and it is invalid, it will throw an exception.

    reinterpret_cast, only works on pointers and references. Does not run time and no compile time checking.

    Look up slicing. Upcasting will remove data from derived class.
*/

    // Cascading constructors is a C++ 11 feature.
    SList<T>::Slist(const SList& rhs) :
      SList()
      {
        operator=(rhs);
      }

/*
    C++ allows you to write  = delete() to delete functions.

    friend class SList;
    SList can access private member of this class / method. You can friend a single method too apparently.

    If you are not reducing the capacity when doing a Clear(), then you should implement a Destroy() 
    function that also reduces capacity to 0 (and size). 

    The functor invocation for expanding memory should be called whenever PushBack()ing. 
    Also the functor should return an unsigned int of the number of elements to increase capacity by.
    Check to make sure that it doesn't return 0 because then a new item can't be pushbacked.
*/
