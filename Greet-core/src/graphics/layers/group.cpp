#include "group.h"

namespace greet { namespace graphics{
	
	Group::Group(const math::vec2& position)
	{
		m_transformationMatrix = math::mat3::translate(position);
	}
	
	Group::Group(const math::mat3& transform)
		:m_transformationMatrix(transform)
	{

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

	bool Group::update(float timeElapsed)
	{
		bool update = false;
		if (enable)
			for (uint i = 0; i < m_renderables.size(); i++)
				update = m_renderables[i]->update(timeElapsed) || update;
		return update;
	}
	
	void Group::submit(Renderer2D* renderer) const
	{
		if (render)
		{
			renderer->pushMatrix(m_transformationMatrix);
			for (uint i = 0; i < m_renderables.size(); i++)
				m_renderables[i]->submit(renderer);
			renderer->popMatrix();
		}
	}

}}
