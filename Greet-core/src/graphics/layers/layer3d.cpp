#include "Layer3D.h"

namespace Greet {

	Layer3D::Layer3D(Renderer3D* renderer)
		: m_renderer(renderer)
	{
	}

	Layer3D::~Layer3D()
	{
		delete m_renderer;
	}

	void Layer3D::add(const EntityModel* renderable)
	{
		m_renderer->submit(renderable);
	}

	void Layer3D::render() const
	{
		setUniforms();
		m_renderer->begin();
		m_renderer->render();
		m_renderer->end();
	}

	void Layer3D::update(float timeElapsed)
	{
		m_renderer->update(timeElapsed);
	}
}
