#include "group.h"

namespace greet { namespace graphics{
	
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

	void Group::push(Renderable* renderable)
	{
		m_renderables.push_back(renderable);
	}

	void Group::submit(Renderer2D* renderer) const
	{
		if (render)
		{
			renderer->pushMatrix(m_transformationMatrix);
			uint size = m_renderables.size();
			for (uint i = 0; i < size; i++)
				m_renderables[i]->submit(renderer);
			renderer->popMatrix();
		}
	}

}}