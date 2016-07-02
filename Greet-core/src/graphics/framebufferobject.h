#pragma once

#include <internal/greet_types.h>
#include <internal/greetgl.h>

namespace greet { namespace graphics {

	class FrameBufferObject
	{
	private:
		uint m_fbo;
		uint m_colorTexture;
		uint m_depthTexture;
	public:
		FrameBufferObject();
		void bind();
		void unbind();
		virtual ~FrameBufferObject();
	};
}}