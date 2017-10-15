#include "atlasmanager.h"	
namespace Greet{
	std::vector<Atlas*> AtlasManager::m_atlas;

	void AtlasManager::add(Atlas* atlas)
	{
		for (int i = 0;i < m_atlas.size();i++)
		{
			if (atlas->getName() == m_atlas[i]->getName())
			{
				ErrorHandle::setErrorCode(GREET_ERROR_MANAGER_ADD);
				Log::error("Given atlas name already exists: ", atlas->getName().c_str());
				return;
			}
		}
		m_atlas.push_back(atlas);
	}

	Atlas* AtlasManager::get(const std::string& atlasName)
	{
		uint size = m_atlas.size();
		for (uint i = 0; i < size; i++)
		{
			if (atlasName.compare(m_atlas[i]->getName().c_str()) == 0)
			{
				return m_atlas[i];
			}
		}
		ErrorHandle::setErrorCode(GREET_ERROR_MANAGER_GET);
		Log::error("Could not find the given atlas: ", atlasName.c_str());
		return m_atlas[0];
	}

	void AtlasManager::destroy()
	{
		for (uint i = 0; i < m_atlas.size(); i++)
			delete m_atlas[i];
	}

}