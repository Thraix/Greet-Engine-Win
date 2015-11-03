#include "fontmanager.h"
namespace greet{ namespace managers{

	std::vector<graphics::Font*> FontManager::m_fonts;

	void FontManager::add(graphics::Font* font)
	{
		m_fonts.push_back(font);
	}

	graphics::Font* FontManager::get(const std::string& fontname)
	{
		uint size = m_fonts.size();

		for (uint i = 0; i < size; i++)
			if (fontname.compare(m_fonts[i]->getName())==0)
				return m_fonts[i];
		GREET_ERROR("FONTMANAGER","Could not find the given font: ", fontname.c_str());
		return m_fonts[0];
	}

	void FontManager::destroy()
	{
		for (uint i = 0; i < m_fonts.size(); i++)
		{
			delete m_fonts[i];
		}
	}

}}