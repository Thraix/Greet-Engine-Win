#include "particle.h"

namespace greet { namespace graphics {

	Particle::Particle()
	{
	}

	Particle::~Particle()
	{
		delete m_sprite;
	}

	void Particle::define(math::vec2 pos, math::vec2 size, math::vec2 vel, math::vec2 acc, uint color, float minspeed, float maxspeed, float frameTime, Sprite* sprite)
	{
		m_startPos = pos;
		m_pos = pos;
		m_size = size;
		m_color = color;
		m_velocity = vel;
		m_acceleration = acc;
		m_minspeed = fabsf(minspeed);
		m_maxspeed = fabsf(maxspeed);
		m_frameTime = frameTime;
		m_sprite = sprite;
	}

	bool Particle::update(float elapsedTime)
	{
		m_frameTime -= elapsedTime;

		m_velocity *= m_acceleration;
		if (m_velocity.length() > m_maxspeed)
		{
			m_velocity.normalize() *= m_maxspeed;
		}
		else if (m_velocity.length() < m_minspeed)
		{
			m_velocity.normalize() *= m_minspeed;
		}
		m_pos += m_velocity;
		return m_frameTime<=0;
	}
}}
