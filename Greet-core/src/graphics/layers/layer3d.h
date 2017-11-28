#pragma once

#include <graphics/shaders/Shader.h>
#include <graphics/Renderable.h>
#include <graphics/renderers/Renderer3D.h>
#include <logging/Log.h>

namespace Greet {
	class Layer3D
	{
	protected:
		Renderer3D* m_renderer;
	public:
		Layer3D(Renderer3D* renderer);
		virtual ~Layer3D();
		void add(const EntityModel* renderable);
		virtual void render() const;
		virtual void update(float timeElapsed);
		virtual void viewportResize(float x, float y, float width, float height) {}
		virtual void windowResize(int width, int height) {}

		
	protected:
		virtual void setUniforms() const {}
	};
}
