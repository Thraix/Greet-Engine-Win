#pragma once

#include <math\maths.h>
#include "shape.h"
#include <greet_types.h>

namespace greet { namespace physics {
	class Body
	{
	public:
		float m_invMass;
		uint m_collision_index;
		math::vec2 m_velocity;
		math::vec2 m_acceleration;
		Shape* m_shape;

	public:
		Body(float mass, Shape* shape, uint collision_index);

		void step(float timeElapsed);
		void impulse(math::vec2 impulse);
		void force(math::vec2 force);

		inline void setMass(float mass) { m_invMass = 1.0f / mass; }
	private:

	};
}}