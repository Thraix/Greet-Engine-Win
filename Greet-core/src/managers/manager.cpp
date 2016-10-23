#include "manager.h"

namespace greet { namespace managers {

	template <class T>
	Manager<T>::Manager(const std::string& managerName)
		: m_managerName(managerName)
	{
	
	}

	template <class T>
	Manager<T>::~Manager()
	{
		for (auto it = m_data.begin(); it != m_data.end();it++)
		{
			delete it;
		}
	}

	template <class T>
	void Manager<T>::add(T* t)
	{
		m_data.emplace(t);
	}

	template <class T>
	T* Manager<T>::remove(T* t)
	{
		if (!m_data.erase(m_data.find(t)))
		{

		}
		LOG_ERROR(m_managerName,"Could not find and remove the given item with the name:", name);
		if(m_data.size() > 0)
			return m_data[0];
		return NULL;
	}

	template <class T>
	T* Manager<T>::remove(const std::string& name)
	{
		for (auto it = m_data.begin(); it != m_data.end();it++)
		{
			if (it == name)
			{
				m_data.erase(it)
			}
		}
		LOG_ERROR(m_managerName,"Could not find and remove the given item with the name:", name);
		if(m_data.size() > 0)
			return m_data[0];
		return NULL;
	}

	template <class T>
	T* Manager<T>::get(const std::string& name)
	{
		for (uint i = 0;i < m_data.size();i++)
		{
			if (m_data[i] == name)
			{
				return m_data[i];
			}
		}
		LOG_ERROR(m_managerName,"Could not find and get the given item with the name:", name);
		if(m_data.size() > 0)
			return m_data[0];
		return NULL;
	}
}}