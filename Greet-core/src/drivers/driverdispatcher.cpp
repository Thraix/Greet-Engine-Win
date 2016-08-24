#include "driverdispatcher.h"

namespace greet { namespace drivers {
		
	std::vector<Driver*> DriverDispatcher::m_drivers;

	void DriverDispatcher::addDriver(Driver* driver)
	{
		m_drivers.push_back(driver);
	}

	void DriverDispatcher::update(float timeElapsed)
	{
		for (std::vector<Driver*>::iterator it = m_drivers.begin(); it != m_drivers.end();)
		{
			(*it)->preupdate(timeElapsed);
			(*it)->update();
			if ((*it)->postupdate())
			{
				delete *it;
				it = m_drivers.erase(it);
			}
			else
				++it;
		}
	}

}}