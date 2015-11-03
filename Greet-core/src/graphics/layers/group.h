#pragma once

#include <graphics/renderable2d.h>

namespace greet { namespace graphics{
	class Group : public Renderable
	{
	private:
		std::vector<Renderable*> m_renderables;
		math::mat3 m_transformationMatrix;
	public:
		Group(const math::mat3& transform);
		~Group();
		void push(Renderable* renderable);
		void submit(Renderer2D* renderer) const override;
	};

}}