#include "particlepool.h"

namespace greet { namespace graphics{
	ParticlePool::ParticlePool(int particles)
		:m_particles(particles), m_usedParticles(0)
	{
		for (int i = 0; i < particles; i++)
		{
			m_free.push_back(new Particle());
		}
	}

	ParticlePool::~ParticlePool()
	{
		m_free.erase(m_free.begin());
		m_used.erase(m_used.begin());
	}
	
	void ParticlePool::update(float elapsedTime)
	{
		std::list<Particle*>::const_iterator it = m_used.begin();
		std::list<Particle*>::const_iterator end = m_used.end();
		while (it != end)
		{
			if ((*it)->update(elapsedTime))
			{
				m_free.splice(m_free.begin(), m_used, it++);
				m_usedParticles--;
			}
			else
			{
				++it;
			}
		}
	}

	void ParticlePool::submit(Renderer2D* renderer) const
	{
		std::list<Particle*>::const_iterator it = m_used.begin();
		std::list<Particle*>::const_iterator end = m_used.end();

		for (; it != m_used.end(); ++it)
		{
			(*it)->submit(renderer);
		}
	}

	bool ParticlePool::create(math::vec2 pos, math::vec2 size, math::vec2 vel, math::vec2 acc, unsigned int color, float minspeed, float maxspeed, double frameTime, Texture* texture, math::vec2 texPos, math::vec2 texSize)
	{
		if (m_free.begin() != m_free.end()){
			(*m_free.begin())->define(pos, size, vel, acc, color, minspeed, maxspeed, frameTime, texture, texPos, texSize);
			m_used.splice(m_used.end(), m_free, m_free.begin());
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