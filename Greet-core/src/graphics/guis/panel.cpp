#include "panel.h"

namespace greet{ namespace graphics{
	Panel::Panel(Renderer2D* renderer, Shader* shader, math::mat3 projectionMatrix ,math::vec2 pos, math::vec2 size)
		:m_renderer(renderer), m_shader(shader), GUI(pos,size)
	{
		GLint texIDs[32];
		for (int i = 0; i < 32; i++)
		{
			texIDs[i] = i;
		}
		m_shader->enable();
		m_shader->setUniformMat3("pr_matrix", projectionMatrix);
		m_shader->setUniform1iv("textures", 32, texIDs);
		m_shader->disable();
		m_panel = this;
		m_invProjectionMatrix = projectionMatrix.cpy().inverse();
	}


	Panel::~Panel()
	{
		delete m_shader;
		delete m_renderer;
	}

	void Panel::render() const
	{
		m_shader->enable();
		setUniforms();
		m_renderer->begin();
		submit(m_renderer);
		m_renderer->end();
		m_renderer->flush();
		m_shader->disable();
	}
}}