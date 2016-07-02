#pragma once

#include "border.h"
#include "gui.h"

namespace greet {namespace graphics {
	
	class Panel : public GUI
	{
		public:
			Panel(const math::vec2& position, const math::vec2& size);
	};

}}
