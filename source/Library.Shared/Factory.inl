#pragma once

#include <string>

namespace FieaGameEngine
{
	template<typename T>
	HashMap<std::string, Factory<T>*> Factory<T>::sFactoryMap;

	template<typename T>
	Factory<T>* Factory<T>::Find(const std::string& name)
	{
		HashMap<std::string, Factory<T>*>::Iterator it = sFactoryMap.Find(name);

		if (it == sFactoryMap.end())
		{
			return nullptr;
		}

		return (*it).second;
	}

	template<typename T>
	T* Factory<T>::Create(const std::string& className)
	{
		if (sFactoryMap.ContainsKey(className))
		{
			return sFactoryMap[className]->Create();
		}

		return nullptr;
	}

	template<typename T>
	const HashMap<std::string, Factory<T>*>& Factory<T>::Factories()
	{
		return sFactoryMap;
	}

	template<typename T>
	typename HashMap<std::string, Factory<T>*>::Iterator Factory<T>::begin()
	{
		return sFactoryMap.begin();
	}

	template<typename T>
	typename HashMap<std::string, Factory<T>*>::Iterator Factory<T>::end()
	{
		return sFactoryMap.end();
	}

	template<typename T>
	void Factory<T>::Add(Factory& factory)
	{
		if (!sFactoryMap.ContainsKey(factory.ClassName()))
		{
			sFactoryMap[factory.ClassName()] = &factory;
		}
	}

	template<typename T>
	void Factory<T>::Remove(Factory& factory)
	{
		if (sFactoryMap.ContainsKey(factory.ClassName()))
		{
			sFactoryMap.Remove(factory.ClassName());
		}
	}
}
