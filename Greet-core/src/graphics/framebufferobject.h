#pragma once

#include <internal/greet_types.h>
#include <internal/greetgl.h>
#include <graphics/textures/texture2d.h>
#include <graphics/window.h>

namespace greet { namespace graphics {

	class FrameBufferObject
	{
	private:
		uint m_fbo;
		uint m_width;
		uint m_height;
		Texture2D* m_colorTexture;
		uint m_depthBuffer;
	public:
		FrameBufferObject(uint width, uint height);
		virtual ~FrameBufferObject();
		void bind();
		void unbind();
		inline Texture2D* getColorTexture() const { return m_colorTexture; }
	};
}}