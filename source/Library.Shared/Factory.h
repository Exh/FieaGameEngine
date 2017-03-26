#pragma once

#include "HashMap.h"
#include <string.h>

namespace FieaGameEngine
{
	template <class T>
	class Factory
	{

	public:

		Factory() = default;
		~Factory() = default;

		static Factory* Find(const std::string& name);

		static T* Create(const std::string& className);

		static typename HashMap<std::string, Factory<T>*>::Iterator begin();

		static typename HashMap<std::string, Factory<T>*>::Iterator end();

		virtual T* Create() const = 0;

		virtual std::string ClassName() const = 0;

	protected:

		static void Add(Factory& factory);

		static void Remove(Factory& factory);

	private:

		static HashMap<std::string, Factory<T>*> sFactoryMap;
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
