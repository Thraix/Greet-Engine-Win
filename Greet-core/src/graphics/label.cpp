#include "label.h"

namespace greet{ namespace graphics{
	Label::Label(std::string text, std::string fontname, math::vec2 pos, uint color, float size)
		: m_font(managers::FontManager::get(fontname)), m_pos(pos), m_size(size)
	{
		m_texID = m_font->getTextureID();
		calibrateMatrices();
		setColor(color);
		setText(text);

	}

	Label::Label(std::string text, Font* font, math::vec2 pos, uint color, float size)
		: m_font(font), m_pos(pos), m_size(size)
	{
		m_texID = m_font->getTextureID();
		calibrateMatrices();
		setColor(color);
		setText(text);
	}

	Label::~Label()
	{
		for (uint i = 0; i < m_glyphs.size(); i++)
			delete m_glyphs[i];
	}

	void Label::submit(Renderer2D* renderer) const
	{
		if (render)
		{
			renderer->submitString(this, true);
			renderer->submitString(this, false);
		}
	}
	bool Label::update(float timeElapsed)
	{
		return false;
	}

	void Label::clearVector()
	{
		while (!m_glyphs.empty()){
			delete m_glyphs[m_glyphs.size()-1];
			m_glyphs.pop_back();
		}
	}

	void Label::setText(std::string text)
	{

		clearVector();
		uint length = text.length();
		float xOffset = 0;
		for (uint i = 0; i < length; i++)
		{
			const Glyph& glyph = m_font->getGlyph(text[i]);
			m_glyphs.push_back(new RenderableGlyph(&glyph, xOffset));
			xOffset += glyph.getSize().x + glyph.getPixelSize()*2.0f;

		}
	}

	void Label::setColor(uint color)
	{
		float c = 0.35f;
		m_color = color;
		uint red = (uint)(((color >> 24) & 0xff) * c);
		uint green = (uint)(((color >> 16) & 0xff) * c);
		uint blue = (uint)(((color >> 0) & 0xff) * c);
		m_shadowColor = color & 0xff000000 + (red << 16) + (green << 8) + blue;
	}

	void Label::setPos(math::vec2 pos)
	{
		m_pos = pos;
		calibrateMatrices();
	}

	void Label::setSize(float size)
	{
		m_size = size;
		calibrateMatrices();
	}

	void Label::centerText()
	{
		centerTextX();
		centerTextY();
	}

	void Label::centerTextX()
	{
		m_pos.x -= getWidth() / 2.0f;
		calibrateMatrices();
	}

	void Label::centerTextY()
	{
		m_pos.y -= (m_font->getCapHeight() + m_font->getCapY() / 2.0f) * m_size;
		calibrateMatrices();
	}

	float Label::getWidth()
	{
		return (m_glyphs.back()->getXPos()+m_glyphs.back()->getCharWidth()+m_font->getPixelSize())*m_size;
	}

	void Label::calibrateMatrices()
	{
		m_transform = math::mat3::quad(m_pos,math::vec2(m_size, m_size));
		m_shadowTransform = math::mat3::quad(m_pos+m_font->getPixelSize()*m_size,math::vec2(m_size, m_size));
	}
}}