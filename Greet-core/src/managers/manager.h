#pragma once

#include <set>

namespace greet { namespace managers {

	template <class T>
	class Manager
	{
	protected:
		std::set<T*> m_data;
		const std::string& m_managerName;
	public:
		Manager(const std::string& managerName);
		virtual ~Manager();
		void add(T* t);
		T* remove(T* t);
		T* remove(const std::string& name);
		T* get(const std::string& name);
	};

}}