#pragma once

#include <math/maths.h>

namespace Greet {
	class OnClickListener
	{
		virtual void onClick(vec2 mousePosition) = 0;
	};
}