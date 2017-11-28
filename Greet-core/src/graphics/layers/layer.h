#pragma once

#include <graphics/shaders/Shader.h>
#include <graphics/Renderable.h>
#include <graphics/renderers/Renderer2D.h>
#include <logging/Log.h>

namespace Greet {

	class Layer
	{
	protected:
		Renderer2D* m_renderer;
		std::vector<Renderable*> m_renderables;
		Shader* m_shader;

		mat3 m_projectionMatrix;
	public:
		Layer(Renderer2D* renderer, Shader* shader, mat3 projectionMatrix)
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

		virtual ~Layer()
		{
			delete m_shader;
			delete m_renderer;

			for (uint i = 0; i < m_renderables.size(); i++)
				delete m_renderables[i];
		}

		virtual void add(Renderable* renderable)
		{
			m_renderables.push_back(renderable);
		}

		virtual void render() const
		{
			m_shader->enable();
			setUniforms();
			m_renderer->begin();
			uint size = m_renderables.size();
			for (uint i = 0; i < size; i++)
			{
				m_renderables[i]->begin(m_renderer);
				m_renderables[i]->submit(m_renderer);
				m_renderables[i]->end(m_renderer);
			}
			m_renderer->end();
			m_renderer->flush();
			m_shader->disable();
		}

		virtual void update(float timeElapsed)
		{
			uint size = m_renderables.size();
			for (uint i = 0; i < size; i++)
				m_renderables[i]->update(timeElapsed);
		}

		void setProjectionMatrix(mat3 projectionMatrix)
		{
			m_projectionMatrix = projectionMatrix;
			m_shader->enable();
			m_shader->setUniformMat3("pr_matrix", m_projectionMatrix);
			m_shader->disable();
		}

		virtual void viewportResize(float x, float y, float width, float height) {}
		virtual void windowResize(int width, int height) {}
		mat3 getProjectionMatrix() const { return m_projectionMatrix; };
		inline Shader* getShader() const { return m_shader; }
		inline uint size() const { return m_renderables.size(); }

		
	protected:
		virtual void setUniforms() const {}
	};
}
