#pragma once

#include "particle.h"
#include <vector>

namespace greet { namespace graphics{
	class ParticlePool : public Renderable2D 
	{
	private:
		std::vector<Particle*> m_alloc;
		Particle* m_first;
		Particle* m_next;
		Particle* m_last;
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