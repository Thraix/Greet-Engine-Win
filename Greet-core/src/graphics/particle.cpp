#include "particle.h"

namespace Greet {

	Particle::Particle()
		: Renderable2D(Vec2(0, 0), Vec2(1, 1),0xffffffff)
	{

	}

	Particle::~Particle()
	{

	}

	void Particle::Define(Vec2 pos, Vec2 size, Vec2 vel, Vec2 acc, uint color, float minspeed, float maxspeed, float frameTime, Sprite* sprite)
	{
		this->m_startPos = pos;
		this->m_pos = pos;
		this->m_size = size;
		this->color = color;
		this->m_velocity = vel;
		this->m_acceleration = acc;
		this->m_minspeed = fabsf(minspeed);
		this->m_maxspeed = fabsf(maxspeed);
		this->m_frameTime = frameTime;
		this->sprite = sprite;
	}

	bool Particle::Update(float elapsedTime)
	{
		m_frameTime -= elapsedTime;

		m_velocity *= m_acceleration;
		if (m_velocity.Length() > m_maxspeed)
		{
			m_velocity.Normalize() *= m_maxspeed;
		}
		else if (m_velocity.Length() < m_minspeed)
		{
			m_velocity.Normalize() *= m_minspeed;
		}
		m_pos += m_velocity;
		return m_frameTime<=0;
	}
}
