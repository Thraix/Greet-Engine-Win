#pragma once

#include "windowfocus.h"
#include "WindowResize.h"

namespace Greet {
	class WindowListener : public WindowFocusListener, public WindowResizeListener
	{

	};
}