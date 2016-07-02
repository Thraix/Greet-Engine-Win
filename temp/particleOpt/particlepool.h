#pragma once

#include "particle.h"
#include <list>

namespace greet { namespace graphics{
	class ParticlePool : public Renderable2D 
	{
	private:
		std::list<Particle*> m_free;
		std::list<Particle*> m_used;
		unsigned int m_usedParticles;
		unsigned const int m_particles;
	public:
		ParticlePool(int particles);
		~ParticlePool();
		bool create(math::vec2 pos, math::vec2 size, math::vec2 vel, math::vec2 acc, unsigned int color, float minspeed, float maxspeed, double frameTime, Texture* texture, math::vec2 texPos, math::vec2 texSize);
		void update(float elapsedTime);
		void submit(Renderer2D* renderer) const override;
		unsigned int usedParticles() const;
		unsigned int freeParticles() const;
	};
}}