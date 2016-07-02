#include "layer.h"

namespace greet { namespace graphics{
	Layer::Layer(Renderer2D* renderer, Shader* shader, math::mat3 projectionMatrix)
		: m_renderer(renderer), m_shader(shader), m_projectionMatrix(projectionMatrix)
	{
		GLint texIDs[32];
		for (int i = 0; i < 32; i++)
		{
			texIDs[i] = i;
		}
		m_shader->enable();
		m_shader->setUniformMat3("pr_matrix", m_projectionMatrix);
		m_shader->setUniform1iv("textures", 32, texIDs);
		m_shader->disable();
	}

	Layer::~Layer()
	{
		delete m_shader;
		delete m_renderer;

		for (uint i = 0; i < m_renderables.size(); i++)
			delete m_renderables[i];
	}

	void Layer::add(Renderable* renderable)
	{
		m_renderables.push_back(renderable);
	}

	void Layer::render() const
	{
		m_shader->enable();
		setUniforms();
		m_renderer->begin();
		uint size = m_renderables.size();
		for (uint i = 0; i < size; i++)
			m_renderables[i]->submit(m_renderer);
		m_renderer->end();
		m_renderer->flush();
		m_shader->disable();
	}

	void Layer::update(float timeElapsed)
	{
		uint size = m_renderables.size();
		for (uint i = 0; i < size; i++)
			m_renderables[i]->update(timeElapsed);
	}

	void Layer::setProjectionMatrix(math::mat3 projectionMatrix)
	{
		 m_projectionMatrix = projectionMatrix; 
		 m_shader->enable();
		 m_shader->setUniformMat3("pr_matrix", m_projectionMatrix);
		 m_shader->disable();
	}
}}
