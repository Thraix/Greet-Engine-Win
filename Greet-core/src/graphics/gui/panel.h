#pragma once

#include "border.h"
#include "GUI.h"

namespace Greet {
	
	class Panel : public GUI
	{
		public:
			Panel(const Vec2& position, const Vec2& size);
	};

}
