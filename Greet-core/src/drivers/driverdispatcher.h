#pragma once

#include <vector>
#include <drivers/Driver.h>

namespace Greet {
	class App;
}

namespace Greet {

	class DriverDispatcher
	{

	friend class App;

	public:
		static void addDriver(Driver* driver);

	private:
		static std::vector<Driver*> m_drivers;
		static void update(float timeElapsed);

		
	};

}