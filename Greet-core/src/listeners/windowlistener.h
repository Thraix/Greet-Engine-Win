#pragma once

#include "windowfocus.h"
#include "windowresize.h"

namespace Greet {
	class WindowListener : public WindowFocusListener, public WindowResizeListener
	{

	};
}