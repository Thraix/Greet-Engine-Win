#include "atlasmanager.h"

namespace greet{ namespace managers {

	std::vector<graphics::Atlas*> AtlasManager::m_atlas;

	void AtlasManager::add(graphics::Atlas* sound)
	{
		m_atlas.push_back(sound);
	}

	graphics::Atlas* AtlasManager::get(const std::string& atlasName)
	{
		uint size = m_atlas.size();

		for (uint i = 0; i < size; i++)
			if (atlasName.compare(m_atlas[i]->getName()) == 0)
				return m_atlas[i];
		GREET_ERROR("ATLASMANAGER", "Could not find the given atlas: ", atlasName.c_str());
		return m_atlas[0];
	}

	void AtlasManager::destroy()
	{
		for (uint i = 0; i < m_atlas.size(); i++)
			delete m_atlas[i];
	}

}}