#include "label.h"

#
namespace greet { namespace graphics {
	
	Label::Label(const std::string& text, math::vec2 pos,Font* font, uint color)
	:text(text),position(pos),m_font(font),color(color)
	{
		
	}
	
	Label::Label(const std::string& text, math::vec2 pos,std::string fontname, uint fontsize, uint color)
	:text(text),position(pos),m_font(FontManager::get(fontname,fontsize)),color(color)
	{
		
	}
	
	void Label::submit(Renderer2D* renderer) const
	{
		renderer->submitString(text,position,m_font,color);
	}
	
	bool Label::update(float timeElapsed)
	{
		return false;
	}

	float Label::getWidth() const
	{
		float width = 0;
		uint length = text.length();
		for (uint i = 0;i < length;i++)
		{
			const char& c = text[i];
			ftgl::texture_glyph_t* glyph = ftgl::texture_font_get_glyph(m_font->getFTFont(), c);
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
	
}}
