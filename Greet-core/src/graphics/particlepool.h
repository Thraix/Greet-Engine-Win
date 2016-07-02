#pragma once
#if 0
#include "particle.h"
#include <list>

namespace greet { namespace graphics{
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
		bool create(math::vec2 pos, math::vec2 size, math::vec2 vel, math::vec2 acc, uint color, float minspeed, float maxspeed, float frameTime, Sprite* sprite);
		bool update(float elapsedTime);
		void submit(Renderer2D* renderer) const override;
		uint usedParticles() const;
		uint freeParticles() const;
	};
}}

#endif