#pragma once

#include <utils/log.h>
#include <greetgl.h>
#include <utils/imageutils.h>
#include <FreeImage.h>
#include <greet_types.h>

namespace greet { namespace graphics{
	class Texture
	{
	private:
		uint m_texID;
		uint m_width;
		uint m_height;
		std::string m_name;
	public:
		Texture(std::string filename, std::string name);
		Texture(BYTE* bits, uint width, uint height, uint bpp, std::string name);
		Texture(uint texID, uint width, uint height, std::string name);
		~Texture();
		void enable() const;
		void disable() const;

		inline uint getTexID() const { return m_texID; }
		inline uint getWidth() const { return m_width; }
		inline uint getHeight() const { return m_height; }
		inline const std::string& getName() const { return m_name; }
	private:
		void loadTexture(const std::string& filename);
		void genTexture(BYTE* bits, uint bpp);

	};

}}