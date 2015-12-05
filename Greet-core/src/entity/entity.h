#pragma once

#include <math\maths.h>
#include <Box2D\Box2D.h>
namespace greet { namespace entity{
	class Entity : public b2Body
	{
	public:
		Entity(math::vec2 position, math::vec2 size);
	};
}}