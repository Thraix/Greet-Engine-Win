#pragma once

namespace greet {
	namespace listener {
		class WindowFocusListener
		{
		public:
			virtual void windowFocus(bool focus) = 0;
		};
	}
}