#pragma once

#include <logging/logger.h>
#include <internal/greetgl.h>
#include <utils/imageutils.h>
#include <FreeImage.h>
#include <graphics/textures/texture.h>

namespace greet { namespace graphics{
	class Texture2D : public Texture
	{
	private:
		uint m_width;
		uint m_height;
	public:
		Texture2D(const std::string& filename, const std::string& name);
		Texture2D(BYTE* bits, uint width, uint height, uint bpp, const std::string& name);
		Texture2D(uint texID, uint width, uint height, const std::string& name);

		inline uint getWidth() const { return m_width; }
		inline uint getHeight() const { return m_height; }
	private:
		void loadTexture(const std::string& filename);
		void genTexture(BYTE* bits, uint bpp);

	};

}}
