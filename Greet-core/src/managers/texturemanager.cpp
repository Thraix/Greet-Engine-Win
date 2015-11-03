#include "texturemanager.h"

namespace greet{ namespace managers{

	std::vector<graphics::Texture*> TextureManager::m_textures;

	void TextureManager::add(graphics::Texture* texture)
	{
		m_textures.push_back(texture);
	}

	graphics::Texture* TextureManager::get(const std::string& texturename)
	{
		uint size = m_textures.size();

		for (uint i = 0; i < size; i++)
			if (texturename.compare(m_textures[i]->getName()) == 0)
				return m_textures[i];
		GREET_ERROR("TEXTUREMANAGER","Could not find the given texture: ", texturename.c_str());
		return m_textures[0];
	}

	void TextureManager::destroy()
	{
		for (uint i = 0; i < m_textures.size(); i++)
		{
			delete m_textures[i];
		}
	}

}}