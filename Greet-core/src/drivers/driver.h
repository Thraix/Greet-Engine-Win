#pragma once

#include "driverlistener.h"
#include <internal/greet_types.h>

namespace greet { namespace drivers {

	class Driver
	{
		friend class DriverDispatcher;
	protected:
		float m_time;
		float m_elapsed;
		float m_elapsedSinceStart;
		DriverListener* m_listener;
	protected:

		Driver(float time, DriverListener* listener);

		~Driver();

		void preupdate(float timeElapsed);
		virtual void update() = 0;
		bool postupdate();
		void onFinished();
	};

}}