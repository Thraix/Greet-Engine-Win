#include "atlasmanager.h"	
namespace greet{ namespace graphics {

	std::vector<graphics::Atlas*> AtlasManager::m_atlas;

	void AtlasManager::add(graphics::Atlas* atlas)
	{
		for (int i = 0;i < m_atlas.size();i++)
		{
			if (atlas->getName() == m_atlas[i]->getName())
			{
				utils::ErrorHandle::setErrorCode(GREET_ERROR_MANAGER_ADD);
				LOG_ERROR("ATLASMANAGER", "Given atlas name already exists:", atlas->getName().c_str());
				return;
			}
		}
		m_atlas.push_back(atlas);
	}

	graphics::Atlas* AtlasManager::get(const std::string& atlasName)
	{
		uint size = m_atlas.size();
		for (uint i = 0; i < size; i++)
		{
			if (atlasName.compare(m_atlas[i]->getName().c_str()) == 0)
			{
				return m_atlas[i];
			}
		}
		utils::ErrorHandle::setErrorCode(GREET_ERROR_MANAGER_GET);
		LOG_ERROR("ATLASMANAGER", "Could not find the given atlas: ", atlasName.c_str());
		return m_atlas[0];
	}

	void AtlasManager::destroy()
	{
		for (uint i = 0; i < m_atlas.size(); i++)
			delete m_atlas[i];
	}

}}