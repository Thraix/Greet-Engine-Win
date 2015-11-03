#include "texture.h"

namespace greet { namespace graphics{
	
	Texture::Texture(std::string filename, std::string name)
		:m_name(name)
	{
		loadTexture(filename);
	}

	Texture::Texture(BYTE* bits, uint width, uint height, uint bpp, std::string name)
		: m_name(name)
	{
		m_width = width;
		m_height = height;
		genTexture(bits,bpp);
	}

	Texture::Texture(uint texID, uint width, uint height, std::string name)
		:m_texID(texID), m_width(width), m_height(height), m_name(name)
	{

	}

	void Texture::loadTexture(const std::string& filename)
	{
		uint bpp = 0;
		BYTE* bits = utils::loadImage(filename.c_str(),&m_width,&m_height,&bpp);
		if (bpp != 24 && bpp != 32)
		{
			GREET_ERROR("TEXTURE","Channel size not supported: ", bpp);
			return;
		}
		genTexture(bits, bpp);
	}

	void Texture::genTexture(BYTE* bits, uint bpp)
	{
		glGenTextures(1, &m_texID);

		glBindTexture(GL_TEXTURE_2D, m_texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, bpp == 32 ? GL_RGBA : GL_RGB, m_width, m_height, 0, bpp == 32 ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, bits);

		glBindTexture(GL_TEXTURE_2D, 0);

		delete[] bits;
	}


	Texture::~Texture()
	{
		glDeleteTextures(1,&m_texID);
	}

	void Texture::enable() const
	{
		glBindTexture(GL_TEXTURE_2D, m_texID);
	}

	void Texture::disable() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}}