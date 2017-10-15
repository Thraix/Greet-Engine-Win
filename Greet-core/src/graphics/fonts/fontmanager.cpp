#include "fontmanager.h"

namespace Greet{

	std::vector<FontContainer*> FontManager::m_fonts;

	void FontManager::add(FontContainer* font)
	{
		for (int i = 0;i < m_fonts.size();i++)
		{
			if (font->getName() == m_fonts[i]->getName())
			{
				ErrorHandle::setErrorCode(GREET_ERROR_MANAGER_ADD);
				Log::error("Given font name already exists: ", font->getName().c_str());
				return;
			}
		}
		m_fonts.push_back(font);
	}

	Font* FontManager::get(const std::string& fontname, uint size)
	{
		for (uint i = 0; i < m_fonts.size(); i++)
		{
			if (fontname.compare(m_fonts[i]->getName())==0)
			{
				return m_fonts[i]->getSize(size);
			}
		}
		ErrorHandle::setErrorCode(GREET_ERROR_MANAGER_GET);
		Log::error("Could not find the given font: ", fontname.c_str());
		if (m_fonts.size() > 0)
			return m_fonts[0]->getSize(size);
		return NULL; // Return Default that always can be read.
	}
	
	// TODO: REMOVE FONTS

	void FontManager::destroy()
	{
		for (uint i = 0; i < m_fonts.size(); i++)
		{
			delete m_fonts[i];
		}
		m_fonts.clear();
	}

}