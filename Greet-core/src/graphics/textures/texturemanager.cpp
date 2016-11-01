#include "texturemanager.h"

namespace greet{ namespace graphics{

	std::vector<graphics::Texture*> TextureManager::m_textures;

	void TextureManager::add(graphics::Texture* texture)
	{
		for (int i = 0;i < m_textures.size();i++)
		{
			if (texture->getName() == m_textures[i]->getName())
			{
				utils::ErrorHandle::setErrorCode(GREET_ERROR_MANAGER_ADD);
				LOG_ERROR("TEXTUREMANAGER", "Given texture name already exists:", texture->getName().c_str());
				return;
			}
		}
		m_textures.push_back(texture);
	}

	graphics::Texture* TextureManager::get(const std::string& texturename)
	{
		uint size = m_textures.size();
		for (uint i = 0; i < size; i++)
		{
			if (texturename.compare(m_textures[i]->getName().c_str()) == 0)
			{
				return m_textures[i];
			}
		}
		utils::ErrorHandle::setErrorCode(GREET_ERROR_MANAGER_GET);
		LOG_ERROR("TEXTUREMANAGER","Could not find the given texture: ", texturename.c_str());
		return m_textures[0];
	}

	Texture2D* TextureManager::get2D(const std::string& texturename)
	{
		return (Texture2D*)get(texturename);
	}

	CubeMap* TextureManager::get3D(const std::string& texturename)
	{
		return (CubeMap*)get(texturename);
	}

	void TextureManager::destroy()
	{
		for (uint i = 0; i < m_textures.size(); i++)
		{
			delete m_textures[i];
		}
	}

}}