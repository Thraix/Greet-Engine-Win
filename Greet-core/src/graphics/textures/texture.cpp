#include "Texture.h"

namespace Greet {
	
	Texture::Texture(const std::string& name, uint textureType)
		: m_name(name), m_textureType(textureType)
	{

	}

	Texture::Texture(uint texId, const std::string& name, uint textureType)
		: m_name(name), m_texId(texId), m_textureType(textureType)
	{

	}

	Texture::~Texture()
	{
		glDeleteTextures(1,&m_texId);
	}

	void Texture::enable() const
	{
		glBindTexture(m_textureType, m_texId);
	}

	void Texture::disable() const
	{
		glBindTexture(m_textureType, 0);
	}

}
