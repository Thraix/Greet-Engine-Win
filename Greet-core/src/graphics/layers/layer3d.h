#pragma once

#include <graphics/shaders/shader.h>
#include <graphics/renderable.h>
#include <graphics/renderers/renderer3d.h>
#include <logging/log.h>

namespace greet { namespace graphics{
	class Layer3D
	{
	protected:
		Renderer3D* m_renderer;
	public:
		Layer3D(Renderer3D* renderer);
		virtual ~Layer3D();
		void add(const model::EntityModel* renderable);
		virtual void render() const;
		virtual void update(float timeElapsed);
		virtual void viewportResize(float x, float y, float width, float height) {}
		virtual void windowResize(int width, int height) {}

		
	protected:
		virtual void setUniforms() const {}
	};
}}
