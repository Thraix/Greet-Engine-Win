#pragma once

#include <internal/GreetTypes.h>

namespace Greet {

	class JoystickStateListener
	{
	public:
		virtual void joystickState(uint joystickIndex, bool state) = 0;
	};
}
