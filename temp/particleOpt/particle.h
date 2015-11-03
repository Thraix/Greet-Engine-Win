#pragma once

#include <math\vec2.h>
#include "renderable2d.h"

namespace greet{ namespace graphics{
	class Particle : public Renderable2D{
		friend class ParticlePool;
	private:
		math::vec2 m_startPos;
		float m_minspeed;
		float m_maxspeed;
		float m_frameTime;
		math::vec2 m_velocity;
		math::vec2 m_acceleration;
	private:
		Particle();
		bool update(float elapsedTime);
		void define(math::vec2 pos, math::vec2 size, math::vec2 vel, math::vec2 acc, unsigned int color, float minspeed, float maxspeed, double frameTime,Texture* texture, math::vec2 texPos, math::vec2 texSize);

	public:
		inline math::vec2 getVelocity() const { return m_velocity; }
		inline math::vec2 getAcceleration() const { return m_acceleration; }
		inline float getMaxSpeed() const { return m_maxspeed; }
		inline float getMinSpeed() const { return m_minspeed; }
		inline double getFrameTime() const { return m_frameTime; }
		~Particle();
	};

}}