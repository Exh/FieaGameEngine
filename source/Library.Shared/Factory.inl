#pragma once

#include <string>

namespace FieaGameEngine
{
	template<class T>
	HashMap<std::string, Factory<T>*> Factory<T>::sFactoryMap;

	template<class T>
	Factory<T>* Factory<T>::Find(const std::string& name)
	{
		HashMap<std::string, Factory<T>*>::Iterator it = sFactoryMap.Find(name);

		if (it == sFactoryMap.end())
		{
			return nullptr;
		}

		return (*it).second;
	}

	template<class T>
	T* Factory<T>::Create(const std::string& className)
	{
		if (sFactoryMap.ContainsKey(className))
		{
			return sFactoryMap[className].Create();
		}

		return nullptr;
	}

	template<class T>
	typename HashMap<std::string, Factory<T>*>::Iterator Factory<T>::begin()
	{
		return sFactoryMap.begin();
	}

	template<class T>
	typename HashMap<std::string, Factory<T>*>::Iterator Factory<T>::end()
	{
		return sFactoryMap.end();
	}

	template<class T>
	void Factory<T>::Add(Factory& factory)
	{
		if (!sFactoryMap.ContainsKey(factory.ClassName()))
		{
			sFactoryMap[factory.ClassName()] = &factory;
		}
	}

	template<class T>
	void Factory<T>::Remove(Factory& factory)
	{
		if (sFactoryMap.ContainsKey(factory.ClassName()))
		{
			sFactoryMap.Remove(factory.ClassName());
		}
	}
}
