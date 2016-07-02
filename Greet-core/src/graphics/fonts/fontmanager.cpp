#include "fontmanager.h"

namespace greet{ namespace graphics {

	std::vector<graphics::Font*> FontManager::m_fonts;

	void FontManager::add(graphics::Font* font)
	{
		m_fonts.push_back(font);
	}

	Font* FontManager::get(const std::string& fontname, float size)
	{
		for (uint i = 0; i < m_fonts.size(); i++)
		{
			if (fontname.compare(m_fonts[i]->getName())==0)
			{
				return getSize(fontname,size,i);
			}
		}
		LOG_ERROR("FONTMANAGER","Could not find the given font: ", fontname.c_str());
		return getSize(m_fonts[0]->getName(),size,0);
	}
	
	Font* FontManager::getSize(const std::string& fontname, float size, uint pos)
	{
		for(uint i = pos;i<m_fonts.size();i++)
		{
			if (fontname.compare(m_fonts[i]->getName())==0)
			{
				if(m_fonts[i]->getSize()==size)
				{
					return m_fonts[i];
				}
			}
		}
		Font* newFont;
		if(m_fonts[pos]->getFileName().compare(""))
			newFont = new Font(m_fonts[pos]->getFileName(),fontname,size);
		else
			newFont = new Font(m_fonts[pos]->getData(),m_fonts[pos]->getDataSize(),fontname,size);
		add(newFont);
		return newFont;
	}
	
	// TODO: REMOVE FONTS

	void FontManager::destroy()
	{
		for (uint i = 0; i < m_fonts.size(); i++)
		{
			delete m_fonts[i];
		}
	}

}}