#pragma once

#include "windowfocus.h"
#include "windowresize.h"

namespace greet { namespace listener {
	class WindowListener : public WindowFocusListener, public WindowResizeListener
	{

	};
}}