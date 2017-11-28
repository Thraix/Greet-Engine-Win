#pragma once

#include <math/Vec2.h>
#include "Renderable2D.h"

namespace Greet{
	class Particle : public Renderable2D {
		friend class ParticlePool;
	private:
		vec2 m_startPos;
		float m_minspeed;
		float m_maxspeed;
		float m_frameTime;
		vec2 m_velocity;
		vec2 m_acceleration;
		vec2 m_pos;
		vec2 m_size;
	private:
		Particle();
		bool update(float timeElapsed);
		void define(vec2 pos, vec2 size, vec2 vel, vec2 acc, uint color, float minspeed, float maxspeed, float frameTime, Sprite* sprite);

	public:
		inline vec2 getVelocity() const { return m_velocity; }
		inline vec2 getAcceleration() const { return m_acceleration; }
		inline float getMaxSpeed() const { return m_maxspeed; }
		inline float getMinSpeed() const { return m_minspeed; }
		inline double getFrameTime() const { return m_frameTime; }
		virtual ~Particle();
	};

}
