#pragma once

#include <graphics/shaders/shader.h>
#include <graphics/renderable.h>
#include <graphics/renderers/renderer2d.h>
#include <logging/logger.h>

namespace greet { namespace graphics{
	class Layer
	{
	protected:
		Renderer2D* m_renderer;
		std::vector<Renderable*> m_renderables;
		Shader* m_shader;

		math::mat3 m_projectionMatrix;
	public:
		Layer(Renderer2D* renderer, Shader* shader, math::mat3 projectionMatrix);
		virtual ~Layer();
		void add(Renderable* renderable);
		virtual void render() const;
		virtual void update(float timeElapsed);
		virtual void viewportResize(float x, float y, float width, float height) {}
		virtual void windowResize(int width, int height) {}
		void setProjectionMatrix(math::mat3 projectionMatrix);
		math::mat3 getProjectionMatrix() const { return m_projectionMatrix; };
		inline Shader* getShader() const { return m_shader; }
		inline uint size() const { return m_renderables.size(); }

		
	protected:
		virtual void setUniforms() const {}
	};
}}
