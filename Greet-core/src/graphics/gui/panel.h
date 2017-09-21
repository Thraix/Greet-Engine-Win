#pragma once

#include "border.h"
#include "gui.h"

namespace Greet {
	
	class Panel : public GUI
	{
		public:
			Panel(const vec2& position, const vec2& size);
	};

}
