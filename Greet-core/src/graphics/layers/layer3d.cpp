#include "layer3d.h"

namespace greet { namespace graphics{
	Layer3D::Layer3D(Renderer3D* renderer, Shader* shader, math::mat3 projectionMatrix)
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

	Layer3D::~Layer3D()
	{
		delete m_shader;
		delete m_renderer;

		for (uint i = 0; i < m_renderables.size(); i++)
			delete m_renderables[i];
	}

	void Layer3D::add(Renderable* renderable)
	{
		m_renderables.push_back(renderable);
	}

	void Layer3D::render() const
	{
		m_shader->enable();
		setUniforms();
		//m_renderer->begin();
		uint size = m_renderables.size();
		//for (uint i = 0; i < size; i++)
		//	m_renderables[i]->submit(m_renderer);
		//m_renderer->end();
		//m_renderer->flush();
		m_shader->disable();
	}

	void Layer3D::update(float timeElapsed)
	{
		uint size = m_renderables.size();
		for (uint i = 0; i < size; i++)
			m_renderables[i]->update(timeElapsed);
	}

	void Layer3D::setProjectionMatrix(math::mat3 projectionMatrix)
	{
		 m_projectionMatrix = projectionMatrix; 
		 m_shader->enable();
		 m_shader->setUniformMat3("pr_matrix", m_projectionMatrix);
		 m_shader->disable();
	}
}}
