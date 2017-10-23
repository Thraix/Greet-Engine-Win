#include "group.h"

namespace Greet {
	

	Group::Group(const vec2& position)
		: m_transformationMatrix(mat3::translate(position))
	{
		enable = true;
	}
	
	Group::Group(const mat3& transform)
		:m_transformationMatrix(transform)
	{
		enable = true;
	}

	Group::~Group()
	{
		uint size = m_renderables.size();
		for (uint i = 0; i < size; i++)
			delete m_renderables[i];
	}

	void Group::add(Renderable* renderable)
	{
		m_renderables.push_back(renderable);
	}

	void Group::remove(Renderable* renderable)
	{
		for (auto it = m_renderables.begin();it != m_renderables.end();it++)
		{
			if (*it == renderable)
			{
				m_renderables.erase(it);
				return;
			}
		}
	}

	bool Group::update(float timeElapsed)
	{
		bool update = false;
		if (enable)
			for (uint i = 0; i < m_renderables.size(); i++)
				update |= m_renderables[i]->update(timeElapsed);
		return update;
	}

	void Group::begin(Renderer2D* renderer) const
	{
		if (render)
			renderer->pushMatrix(m_transformationMatrix);
	}
	
	void Group::submit(Renderer2D* renderer) const
	{
		if (render)
			for (uint i = 0; i < m_renderables.size(); i++)
			{
				m_renderables[i]->begin(renderer);
				m_renderables[i]->submit(renderer);
				m_renderables[i]->end(renderer);
			}
	}

	void Group::end(Renderer2D* renderer) const
	{
		if (render)
			renderer->popMatrix();
	}

}
