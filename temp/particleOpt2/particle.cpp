#include "Particle.h"

namespace greet { namespace graphics {

	Particle::Particle()
	{
	}

	Particle::~Particle()
	{

	}

	void Particle::define(math::vec2 pos, math::vec2 size, math::vec2 vel, math::vec2 acc, unsigned int color, float minspeed, float maxspeed, double frameTime, Texture* texture, math::vec2 texPos, math::vec2 texSize)
	{
		m_isUsed = true;
		m_startPos = pos;
		m_pos = pos;
		m_size = size;
		m_color = color;
		m_velocity = vel;
		m_acceleration = acc;
		m_minspeed = fabsf(minspeed);
		m_maxspeed = fabsf(maxspeed);
		m_frameTime = frameTime;
		m_texture = texture;
		m_texPos = texPos;
		m_texSize = texSize;
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
		m_isUsed = m_frameTime > 0;
		return !m_isUsed;
	}

	void Particle::setParent(Particle* parent)
	{
		m_parent = parent;
	}
}}