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
    [X] Refactor tests to use variables instead of literals.
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

	Copy constructor should call reserve?
	The place to write malloc is in reserve.
	Don't rewrite malloc multiple times.

    [X] Rewrite code to use malloc almost exclusively in reserve.
	[X] Make sure to add a ShrinkToFit() or Destroy() because Clear() does not reduce the capacity.
	[X] Make Remove(begin, end) to take an iterator, not a an unsigned int.
    [ ] Replace iterations in Vector with range-based for loops.

	Mutable to allow const objects to modify the member.
*/

//***************
// Assignment 05
//***************
/*
	public inheritance:

	protected inheritance:
	any members that 

	private inheritance:
	outside the derived class, there is not a is-a

	Use composition instead of private inheritance for your stack.
	Probably use SList because you get constant time inserts, and dont care about linear lookups.
	You just need to get the back, which you have.
*/

//***************
// Assignment 06
//***************
/*
	open addressing
	chaining

	Move semantics, New in C++11

	RVO, return value optimization
	Compiler would rearrange code, and before 

	an l-value is any variable that you can take an address of.
	and expression that lasts more than one line of code.
	Can't take an address of an r-value.
	All variables are l-values, because you can take the address of them.

	Iterator&& rhs   <----- R-Value reference

	So if you want to move

	no default move constructor.
	You get move semantics if you don't create a constructor/copy constructor/ or assignment operator
*/

SList<T>::Iterator::Iterator(Iterator&& rhs) : 
	Iterator(rhs.mOwner, rhs.mNode)
{

}

/* 
	Hash table is not distinctly ordered. No pushback/pushfront. There is only an insert.

	Desirable properties: fast, produces uniform distribution of values from keys.

	class should have two type arguments, TKey, TValue

	key and element stored in each bin of the array

	std::pair used for storing pairs

	Vector<SList<std::pair<TKey, TValue> > >

	give the user an option to resize the array, but never resize automatically.
	you have to make a new hash table, reinsert the elements from the old hash map, 
	and then delete the previous hash map.

	Type cast constructor.
	if you have a constructor that takes a single parameter, then it can be invoked like
	Vector<int> v = 10; (setting the capacity to 10).
	If you mark the constructor as explicit, then this implicit conversion

	you can use newLvalue = move(lValue)) to do a move instead of a copy.

	begin() would return an iterator to the first non empty sList's first node.
	Maybe use a Vector index and an SList iterator.
	begin and end don't have to be in constant time (as the standard would suggest).

	additive hash: hash += C + key[i]


	specialiaztion for T*,
	char*, 
	Foo,
	std::string is okay to use.
	so use a custom Foo 

	template<typename T>
	class DefaultHash
	{
		std::uint
	}

	operator[] should always call Insert().

	At() vs operator[]...
	At(): will throw an exception if there is no value inserted at a key.
	operator[]: will add a new element.

	operator[] will call Insert with a default constructor if there is a new key being added.

	could possibly move instead of copying after operator[]?? or something. we dont have to though
	look up emplace_back()?

	Do the hash functor thing as a Template, not as an assignable callback.

	Specialization for:
	char* - required 
	String - required 
	Foo - would be smart to do this
	int - would be good too
	int* - yea this too
	T* - possibility? Up to us
	Paul doesn't care about the TValue when testing. it can all be the same

	Make the HashMap constructor explicit.
	Default the capacity to a prime number if not specified.
	You CAN use a literal in the HashMap constructor

	For the hash functor object, make a member variable because it will probably 
	need to be used in multiple places.

	Copy constructor could just use vector's copy constructor
	and maybe assignment operator would also be very simple because 

	No need to explicitly call default constructor in initialization list.

	For template specialization

	Hash function should take the value of 

	If you have a hashmap of TKey = int*, then the hashing should be using the integer value,
	not the int* pointer value;
*/

/* 
	Compile Time Polymorphism: like template classes
	Also macros are like compile time polymorphism

	Virtual Table stores function pointers.
	Virtual table is shared across all instances of a class.
	If a class has at least one virtual method.
	All derived class gets VTable of there own even if no virtual methods
	were overridden from the parent class.

	Every class that has a VTable has a pointer to the VTable
	When you dereference the VTable, it might produce a cache miss.

	You cannot call derived class methods from a base class Constructor().
	The derived class has not been constructed yet. The vtable pointer is 
	pointing to the base class while in the base class constructor. And then
	when it moves to the derived1 class, the vtable changes.

	Pure virtual functions can have implementations.
	called from child with BaseClass::Function();

	Virtual constructor... C++ does not provide a virtual constructor.
	Factory pattern basically allows this with a Factory base class and 
	different derived classes. If you have an array of Factory*s, then you
	call factories[i]->Create().

	RTTI can only be globally turned on when using C++'s RTTI.

	DatumType should be a strong enum. (or an enum class)
*/

enum class DatumType
{
	Integer,
	Float,
	String
};

/*
	Datums are basically vectors. Not templated. Runtime polymorphism.

*/

union DatumValues
{
	std::int32_t* i;
	std::string* s;
	float* f;
	glm::vec4* v;
	glm::mat4* m;
	RTTI** r;
};

DatumValues mData;
std::uint32_t mSize;
std::uint32_t mCapacity;

/*
	Only allow user to set type of datum once. Throw an exception if they try to change the type.
	If they call SetType() with the same type, then that's okay, don't throw an excpetion.

	When you call Clear(), you dont have to free memory. You could implement a ShrinkToFit() method.
	Don't change the type when Clear() is invoked.

	You should use the assignment operator as a scalar assignment. Which should set the value's type,
	set its size to 1. and then push the value that was assigned in the 0th element.

	Get() could be templated, or you could use GetInteger();
*/

Datum d = 50;
d = 60; // overwrites the element at 0th index with 60.

/* 
	Also consider adding PushBack()

	Comparison Operators: Overload all of the operators for string, int, float etc.
	Only compare the first element if the datum holds a non-scalar. 
	Datum to Datum oeprator==()

	glm::vec4 and glm::mat4 has glm::To_String for converting to string.
	Corresponding stuff to parse out from string.

	The SetFromString() and ToString() formats should match!!

	You could possibly serialize the string formats to include type.

	It's okay if SetFromString() requires that SetType has already been called.

	External storage is used to reference C++ variables from the Datum scripting framework.

	Just copy the values of pointer for RTTI*s.

	If you push back on an external storage datum, you would throw an exception.

	SetStorage() params: pointer to storage + size. Should not be a void*. Overload for each type.

	Even for internal storage, you should not delete the RTTI object data, just the pointer RTTI*

	Do not provide the user with the template for like Get or something? Don't put the general template nor
	specializations in the header.

	Set for an RTTI pointer should be a pointer. Could possibly be nullptr. (RTTI*)

	Set Storage for an RTTI pointer should be an RTTI**

	Set() for integer should take an int. (could possibly do a const int& but doesnt matter.
	Possibly do a move semantics call for Set(), but glm might not support move semantics? You could add it yourself.

	Make Foo an RTTI, and then you can stick foo pointers inside of datums

	Set from string will probably need a datum to have its type set before getting called, unless you
	were to add a tag format.

	Hard things about this assignment:
	Copying
	Deleting
	Instantiating

	Can't call reserve before SetType().

	You can include a void* member inside the Buffer union.

	If you choose to never have a different size from capacity, then you wouldn't need to use placement new.

	You can use an unnamed union because you wont be reusing the type.

	USE THESE COMMENT TAGS:
	@param
	@return 
	@brief
	@exception

	Get<RTTI*>() should return a RTTI*&

	If you Get<string>() of a vector, it should 

	ToString for pointers, can return null string or something.

	If you call SetStorage on something that already has a type assigned... exception?

	Does Set() auto expand? design decision. i wouldn't

	external/internal storage would not matter when comparing two datums

	just show that you can store an RTTI*.
*/

noexcept // Says that this function will not throw an exception

//***************
// Assignment 08
//***************
/* 

Scopes that are contained by other scopes, then they have a pointer to their parent.
If the scope is a top-level scope then it's owner pointer is null.

Only one parent ever. Multiple scopes can't use the same child. unless you use RTTI*.

HashMap of string, Datum pairs.
^ make strings const?

Prototype pattern splits up class definition and instance.

Chain of Responsibility pattern??

The vector would contain type Pair<string, Datum>*

You will own the data of Scopes contained in the Datum

Should never be able to change the key of string,Datum pair.

Search will be recursive and look up the tree.

Most complicated part of assignment:
When you have datums of type Table, all the pointers in there... you own them.
Makse sure that two scopes dont think that they have the same child
Scope** element in the Datum union

When comparing two RTTI pointers, first you need to check to make sure that they are 
non-null, and then you can dereference and use their comparison operators.

Paul's scope pointer array in datum cannot contain any nullptrs.
When calling SetSize()...?? Maybe don't allow set size on scope

When destroying scopes, scopes must delete their child scopes
scopes need to be able to be deep copied.

*/

typedef void(Datum::*DeleteFunction)();
static const DeleteFunction DeleteFunctions[static_cast<int>(DatumType::End)];

/*
	Is RAII always best option? Allocating graphics memory in constructor?

	std::make_unique
	std::make_shared 
	Hides the "new" keyword.
*/

/** 
	Scope TODOs:
	[ ] Ensure Scope pointers cannot be nullptr in a Datum.
	[X] Is my deep copy correct? Does deep copy need to copy entire tree. What about the mParent pointer?
	[X] Test RTTI methods for code coverage.
	[X] ToString for a scope can be a dummy method.
	[X] If a scope adopts itself, do nothing or throw exception.
*/



/* 
	Attributed:

	Keep an array of strings that are prescribed attributes?
	
	make a hash map of int, strings in static memory.
	the int would be the RTTI class id, string is attribute name.

*/


/*
	Single dispatch: implemented through the virtual table.
*/

class A
{
	int mInt;
};

class B
{
	float mFloat;
};

/* Replication is when class A and class B both derive from class Base

"Write this down":
Describe each of these four things:
L-Value
R-Value
L-Value Reference
R-Value Reference

Also going to ask you about casting in C++.
Four different types of casting.


AddInternalSignature() - does datum creation when called.
^ in the attributed class?
Also make AddExternalAttribute()

AddInternalAttribute

^ 
DO THIS METHOD INSTEAD. no signatures.
Use protected helper methods for AddExternalAttribute and Add InternalAttribute.

You can use a static hashmap in Attributed of unsigned int, Vector<std::string> that stores all prescribed attribute names

Add a static function to clear the prescribed attribute cache hashmap.

Cross cutting? Interdependency between software modules.

Don't have a public interface for adding signatures to the Attributed class.

Create a this pointer in Attributed class.

Do move semantics last, least important.

So apparently all of your classes need Move semantics. 
Start with move semantics for SList, and test it first.
And go one by one testing each move semantics.
You should add an internal prescribed member to AttributedFoo.

*/

/* 
	HandlerInterface should have to pure virtual functions.
	StartElementHandler
	EndElementHandler

	and a non-pure virtual method 
	CharDataHandler

	SharedData is intended to be derived.
	SharedData keeps a Depth value and has functions:
	IncrementDepth() and
	DecrementDepth()
	
	increment depth at StartElement.

	SharedData is an RTTI managing depth of descent.
	Share
*/

/* 
Assignment14
	World and Section should be marked final.
*/

<World name="PaulzWorld">
	<Sector name="AwesomeTown">
		<Entity class="MonsterEntity" name="Paul">
			<Integer value="10"/>
			<STRING value="Beep"/>
		</Entity>
	</Sector>
</World>

/* 
	Worlds are just a scope

	If you are at any other besides depth besides 1 when you get a World tag... Error!

	World has name, list of sectors, and this pointer as prescribed attributes.

	Make a separate macro for CreateEntityFactory()
	and CreateActionFactory()

	You can change your Scope parse helpers

	Update methods for World, Sector, and Entity will take WorldState references.
	World will set the WorldState.mCurrent

	Composite, Command, State(?) patterns

	Possibly add a Scope::Sort() function that takes a lambda expression for the comparer.
	Use this to optimize finding a Sector in the Sectors array, or Entities in the Entities array.

	Game class should have a Run() and Initialize().
	World state at least has pointers to world, sector, entity and a gametime.
	Do not assume that the owner of the action is an entity. You can always ask what type of scope

	Do not unit test paul's gameclock/gametime class

	Safe to assume that Entity's parent is a sector (well make sure you assert).

	Test typeidinstace(), is(), queryinterface(), as()? etc etc 

	Infix notation
	Postfix notation 
	Reverse Polish Notation
	Shunting Yard

	Have an actions prescribed attribute inside your actionlist class. 
	Actionlist also has a name 
	CreateAction is similar to AppendScope(). What its job really is, is to invoke the Factory<Action>::Create() function
	the action create
	Actionlist has no function itself besides going through the list of actions and invoking them.
	Entity has pointers to actions, not action lists (but they are probably lists. treated the same as an action)
	Actions are stored as prescribed attributes whose name is "actions" and type is table. 
	CreateAction and DestroyAction are required to implement.

	Should DestroyAction be able to destroy itself? yes? Create a queue of actions to delete and then
	after all of the updates. Delete them all.

	Maybe start by making an ActionAdd first to understand. Or ActionArithmetic "type" = "Add").

	Make ActionList::Update virtual.
	ActionIf will have to override Update to handle the execution differently.

	<Action class="IncrementAction" name="IncreaseX" target="x">
		<Integer name="x" value="10"/>
	</Action>
	^ BUT X COULD BE IN PARENT SCOPE INSTEAD
*/


/*

	Don't need to make World pointer prescribed because EventMessage is only used in C++, not script.
	ActionEvent's subtype needs to be prescribed. ActionReaction subtype needs to be prescribed. Possibly
	make EventMessage a scope instead of Attributed.

*/