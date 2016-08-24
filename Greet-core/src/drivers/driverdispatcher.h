#pragma once

#include <vector>
#include <drivers/driver.h>

namespace greet { namespace internal {
	class App;
}}

namespace greet { namespace drivers {

	class DriverDispatcher
	{

	friend class internal::App;

	public:
		static void addDriver(Driver* driver);

	private:
		static std::vector<Driver*> m_drivers;
		static void update(float timeElapsed);

		
	};

}}