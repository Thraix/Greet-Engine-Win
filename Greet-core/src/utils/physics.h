#pragma once

#include <math\maths.h>
#include <utils\log.h>

namespace greet { namespace Physics {
	static bool Collision(math::vec2 pos1, math::vec2 size1, math::vec2 pos2, math::vec2 size2)
	{
		return pos1.x < pos2.x + size2.x && pos1.x + size1.x > pos2.x && pos1.y< pos2.y + size2.y && pos1.y + size1.y> pos2.y;
	}

	static bool Collision(math::vec2 pos1, float radius1, math::vec2 pos2, float radius2)
	{
		return (pos1 - pos2).length() < radius1 + radius2;
	}
}}