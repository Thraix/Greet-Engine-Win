#include "texture2d.h"

namespace greet { namespace graphics{
	
	Texture2D::Texture2D(const std::string& filename, const std::string& name)
		:Texture(name, GL_TEXTURE_2D)
	{
		loadTexture(filename);
	}

	Texture2D::Texture2D(BYTE* bits, uint width, uint height, uint bpp, const std::string& name)
		: Texture(name,GL_TEXTURE_2D)
	{
		m_width = width;
		m_height = height;
		genTexture(bits,bpp);
	}

	Texture2D::Texture2D(uint texId, uint width, uint height, const std::string& name)
		:Texture(texId,name,GL_TEXTURE_2D), m_width(width), m_height(height)
	{

	}

	void Texture2D::loadTexture(const std::string& filename)
	{
		using namespace utils;
		uint bpp = 0;
		BYTE* bits = loadImage(filename.c_str(),&m_width,&m_height,&bpp);
		genTexture(bits, bpp);
	}

	void Texture2D::genTexture(BYTE* bits, uint bpp)
	{
		glGenTextures(1, &m_texId);

		glBindTexture(GL_TEXTURE_2D, m_texId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, bpp == 32 ? GL_RGBA : GL_RGB, m_width, m_height, 0, bpp == 32 ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, bits);
		glBindTexture(GL_TEXTURE_2D, 0);
		delete[] bits;
	}
}}
