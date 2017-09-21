#pragma once

#include <internal/Greet_types.h>

namespace Greet {

	class JoystickStateListener
	{
	public:
		virtual void joystickState(uint joystickIndex, bool state) = 0;
	};
}
