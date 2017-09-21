#pragma once
#if 0
#include "particle.h"
#include <list>

namespace Greet {
	class ParticlePool : public Renderable2D 
	{
	private:
		std::list<Particle*> m_free;
		std::list<Particle*> m_used;
		uint m_usedParticles;
		unsigned const int m_particles;
	public:
		ParticlePool(int particles);
		~ParticlePool();
		bool create(vec2 pos, vec2 size, vec2 vel, vec2 acc, uint color, float minspeed, float maxspeed, float frameTime, Sprite* sprite);
		bool update(float elapsedTime);
		void submit(Renderer2D* renderer) const override;
		uint usedParticles() const;
		uint freeParticles() const;
	};
}

#endif