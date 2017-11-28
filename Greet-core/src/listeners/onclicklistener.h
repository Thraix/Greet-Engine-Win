#pragma once

#include <math/Maths.h>

namespace Greet {
	class OnClickListener
	{
		virtual void onClick(vec2 mousePosition) = 0;
	};
}