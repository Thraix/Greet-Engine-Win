#pragma once

#include <math/Maths.h>

namespace Greet {
	class OnClickListener
	{
		virtual void OnClick(Vec2 mousePosition) = 0;
	};
}