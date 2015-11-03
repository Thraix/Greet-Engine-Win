#include "particlepool.h"

namespace greet { namespace graphics{
	ParticlePool::ParticlePool(int particles)
		:m_particles(particles), m_usedParticles(0)
	{
		for (int i = 0; i < particles; i++)
		{
			m_alloc.push_back(new Particle());
		}
		for (int i = 0; i < particles-1; i++)
		{
			m_alloc[i]->m_parent = m_alloc[i + 1];
		}
		m_first = m_alloc[0];
		m_next = m_alloc[0];
		m_last = m_alloc[particles-1];
	}

	ParticlePool::~ParticlePool()
	{
		m_alloc.erase(m_alloc.begin());
	}
	
	void ParticlePool::update(float elapsedTime)
	{
		Particle* particle = m_first;
		Particle* lastParticle = nullptr;
		while (particle->m_isUsed)
		{
			if (particle->update(elapsedTime))
			{
				m_last->m_parent = particle;
				m_last = particle;
				if (lastParticle != nullptr)
				{
					lastParticle->m_parent = particle;
				}
				particle = particle->m_parent;
			}
			else
			{
				lastParticle = particle;
				particle = particle->m_parent;
			}
		}
	}

	void ParticlePool::submit(Renderer2D* renderer) const
	{

		Particle* particle = m_first;
		//while (particle->m_isUsed)
		{
			//particle->submit(renderer);
			//particle = particle->m_parent;
		}
	}

	bool ParticlePool::create(math::vec2 pos, math::vec2 size, math::vec2 vel, math::vec2 acc, unsigned int color, float minspeed, float maxspeed, double frameTime, Texture* texture, math::vec2 texPos, math::vec2 texSize)
	{
		if (m_next != m_last){
			m_next->define(pos, size, vel, acc, color, minspeed, maxspeed, frameTime, texture, texPos, texSize);
			m_next = m_next->m_parent;
			m_usedParticles++;
			return true;
		}
		GREET_WARN("Could not find an unused particle");
		return false;

		/*Particle* particle = m_particles.back();
		if (particle->isUsed())
			return false;
		m_particles.pop_back();
		m_particles.insert(m_particles.begin(),particle);*/
	}

	unsigned int ParticlePool::usedParticles() const
	{
		return m_usedParticles;
	}

	unsigned int ParticlePool::freeParticles() const
	{
		return m_particles-m_usedParticles;
	}
}}