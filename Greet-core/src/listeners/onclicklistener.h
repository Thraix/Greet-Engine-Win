#pragma once

#include <math/maths.h>

namespace greet { namespace listener {
	class OnClickListener
	{
		virtual void onClick(math::vec2 mousePosition) = 0;
	}
} }