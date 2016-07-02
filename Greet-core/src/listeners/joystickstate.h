#pragma once

#include <internal/greet_types.h>

namespace greet {
	namespace listener {
		class JoystickStateListener
		{
		public:
			virtual void joystickState(uint joystickIndex, bool state) = 0;
		};
	}
}
