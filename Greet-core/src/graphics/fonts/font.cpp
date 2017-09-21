#include "font.h"
#include <direct.h>

namespace Greet{

	Font::Font(FontContainer* container, uint size)
	: m_container(container), m_size(size)
	{
		init();
	}

	void Font::init()
	{
		m_atlas = ftgl::texture_atlas_new(512,512,2);
		if (m_container->getData() == NULL)
		{
			m_font = ftgl::texture_font_new_from_file(m_atlas, m_size, m_container->getFileName().c_str());
			ASSERT(m_font, "Could not load font from file:", m_container->m_filename);
		}
		else
		{
			m_font = ftgl::texture_font_new_from_memory(m_atlas, m_size, m_container->m_data, m_container->m_datasize);
			ASSERT(m_font, "Could not load font from memory:", m_container->m_filename);
		}
	
	}
	
	float Font::getWidthOfText(const std::string& text) const
	{
		float width = 0;
		uint length = text.length();
		for (uint i = 0;i < length;i++)
		{
			const char& c = text[i];
			ftgl::texture_glyph_t* glyph = ftgl::texture_font_get_glyph(getFTFont(), c);
			if (glyph != NULL)
			{
				if (i != length - 1)
					width += glyph->advance_x;
				else
					width += glyph->width;
			}
		}
		return width;
	}
}