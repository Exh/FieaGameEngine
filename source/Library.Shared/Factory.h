#pragma once

#include "HashMap.h"
#include <string.h>

namespace FieaGameEngine
{
	template <typename T>
	class Factory
	{

	public:

		/** Default Constructor. Does nothing. */
		Factory() = default;

		/** Default Destructor. Does nothing. */
		virtual ~Factory() = default;

		/** Searches for a factory in this class's static collection of
		Factories for factory whose class name matches the provided name.
		@param name Class name type to search for. 
		@return The pointer to the registered factory. nullptr if a 
			Factory is not found with the provided class name.*/
		static Factory* Find(const std::string& name);

		/** Instantiates an instance of the template type and returns
		a pointer to the newly created object. The caller is responsible
		for deleting the data. The type of object spawned depends on the 
		className string that is passed in. If no factory can create the
		type passed in, then nothing will be instantiated and a nullptr will
		be returned instead.
		@param className The name of the class to instantiate. The class should
			be a subclass of type T. And a proper factory should be added first.
		@return Pointer to the newly instantiated object. nullptr if no factory
			could produce the given className.*/
		static T* Create(const std::string& className);

		/** Returns the static collection of Factories that are registered for
		this type.
		@return Factories Hashmap that contains className, Factory pairs. */
		static const HashMap<std::string, Factory*>& Factories();

		/** Returns a HashMap iterator to the first factory in the static 
		Factories HashMap.
		@return Iterator pointing to the first Factory in the HashMap.*/
		static typename HashMap<std::string, Factory*>::Iterator begin();

		/** Returns a HashMap iterator that represents the end of the 
		Factories HashMap.
		@return Iterator pointing to the first Factory in the HashMap.*/
		static typename HashMap<std::string, Factory*>::Iterator end();

		/** The instance-level Create implementation that must be overriden by
		all factories. This method will be called by the static Create method when 
		the passed in string is equivalent to this Factory's className.
		@return Pointer to the newly created T type object who is actually of 
			the Factory instance's concrete type.*/
		virtual T* Create() const = 0;

		/** Returns a string that represents the type that this factory will manufacture.
		@return The class name string.*/
		virtual std::string ClassName() const = 0;

	protected:

		static void Add(Factory& factory);

		static void Remove(Factory& factory);

	private:

		static HashMap<std::string, Factory*> sFactoryMap;
	};
}

#define ConcreteFactory(AbstractProductType, ConcreteProductType) \
	class ConcreteProductType ## Factory : public FieaGameEngine::Factory<AbstractProductType> \
	{ \
		public: \
			ConcreteProductType ## Factory() { FieaGameEngine::Factory<AbstractProductType>::Add(*this); } \
			~ConcreteProductType ## Factory() { FieaGameEngine::Factory<AbstractProductType>::Remove(*this); } \
			virtual std::string ClassName() const override { return #ConcreteProductType; } \
			virtual AbstractProductType* Create() const override \
			{ \
				AbstractProductType* product = new ConcreteProductType(); \
				assert(product != nullptr); \
				return product; \
			} \
	}; \

#include "Factory.inl"
