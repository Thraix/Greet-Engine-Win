#pragma once

#include <internal/greet_types.h>
#include <internal/greetgl.h>
#include <graphics/textures/texture2d.h>
#include <graphics/window.h>
#include <map>

namespace greet { namespace graphics {

	class FrameBufferObject
	{
	private:
		uint m_fbo;
		uint m_width;
		uint m_height;
		std::map<uint, Texture2D*> m_colorTextures;
		Texture2D* m_depthTexture;
		uint m_depthBuffer;
	public:
		FrameBufferObject(uint width, uint height);
		virtual ~FrameBufferObject();
		void bind();
		void unbind();
		void attachColorTexture(uint attachementId);
		Texture2D* getColorTexture(uint attachmentId) const;
		inline Texture2D* getDepthTexture() const { return m_depthTexture; }
	private:
		void attachDepthTexture();
	};
}}