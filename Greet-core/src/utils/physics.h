#pragma once

#include <math\maths.h>
#include <utils\log.h>

namespace greet { namespace Physics {

	static math::vec2 minMax(float left, float right)
	{
		return math::vec2(left < right ? left : right, left > right ? left : right);
	}

	static math::vec2 minMax(math::vec2 vec, float comp)
	{
		return math::vec2(vec.x < comp ? vec.x : comp, vec.y > comp ? vec.y : comp);
	}

	static bool Collision(math::vec2 pos1, math::vec2 size1, math::vec2 pos2, math::vec2 size2)
	{
		return pos1.x < pos2.x + size2.x && pos1.x + size1.x > pos2.x && pos1.y< pos2.y + size2.y && pos1.y + size1.y> pos2.y;
	}

	static bool Collision(math::vec2 pos1, float radius1, math::vec2 pos2, float radius2)
	{
		return (pos1 - pos2).length() < radius1 + radius2;
	}

	static bool BoxVsBox(math::vec2 ul1, math::vec2 ur1, math::vec2 dr1, math::vec2 dl1, math::vec2 ul2, math::vec2 ur2, math::vec2 dr2, math::vec2 dl2)
	{
		math::vec2* axes = new math::vec2[4];
		axes[0] = ur1 - ul1;
		axes[1] = ul1 - dl1;
		axes[2] = ur2 - ul2;
		axes[3] = ul2 - dl2;
		
		math::vec2 minMaxA;
		math::vec2 minMaxB;

		minMaxA = minMax(axes[0].dot(ul1), axes[0].dot(ur1));
		minMaxB = minMax(minMax(minMax(axes[0].dot(ul2), axes[0].dot(ur2)), axes[0].dot(dr2)), axes[0].dot(dl2));
		if (minMaxA.y < minMaxB.x || minMaxA.x > minMaxB.y)
			return false;

		minMaxA = minMax(axes[1].dot(ul1), axes[1].dot(dl1));
		minMaxB = minMax(minMax(minMax(axes[1].dot(ul2), axes[1].dot(ur2)), axes[1].dot(dr2)), axes[1].dot(dl2));
		if (minMaxA.y < minMaxB.x || minMaxA.x > minMaxB.y)
			return false;

		minMaxA = minMax(minMax(minMax(axes[2].dot(ul1), axes[2].dot(ur1)), axes[2].dot(dr1)), axes[2].dot(dl1));
		minMaxB = minMax(axes[2].dot(ul2), axes[2].dot(ur2));
		if (minMaxA.y < minMaxB.x || minMaxA.x > minMaxB.y)
			return false;

		minMaxA = minMax(minMax(minMax(axes[3].dot(ul1), axes[3].dot(ur1)), axes[3].dot(dr1)), axes[3].dot(dl1));
		minMaxB = minMax(axes[3].dot(ul2), axes[3].dot(dl2));
		if (minMaxA.y < minMaxB.x || minMaxA.x > minMaxB.y)
			return false;

		delete[] axes;
		return true;

	}
}}