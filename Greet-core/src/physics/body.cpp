#include "body.h"

namespace greet { namespace physics {

	Body::Body(float mass, Shape* shape, uint collision_index)
		: m_invMass(1.0f/mass), m_shape(shape), m_collision_index(collision_index)
	{
		
	}

	void Body::step(float timeElapsed)
	{
		m_velocity += m_acceleration * timeElapsed;
		m_shape->move(m_velocity * timeElapsed);
	}
	
	void Body::impulse(math::vec2 impulse)
	{
		m_velocity += impulse*m_invMass;
	}

	void Body::force(math::vec2 force)
	{
		m_acceleration += force*m_invMass;
	}
}}