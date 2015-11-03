#include "textview.h"

namespace greet { namespace graphics {

	TextView::TextView(math::vec2 pos, std::string fontname, float size)
		: GUI(pos, math::vec2(0, 0)), m_label(new Label("", fontname, pos, 0xffffffff, size))
	{
		init();
	}

	TextView::TextView(math::vec2 pos, std::string fontname, float size, std::string text)
		: GUI(pos, math::vec2(0, 0)), m_label(new Label(text, fontname, pos, 0xffffffff, size))
	{
		init();
	}

	TextView::TextView(math::vec2 pos, std::string fontname, float size, std::string text, uint color)
		: GUI(pos,math::vec2(0,0)),m_label(new Label(text,fontname,pos,color,size))
	{
		init();
	}

	TextView::TextView(math::vec2 pos, Font* font, float size)
		: GUI(pos, math::vec2(0, 0)), m_label(new Label("", font, pos, 0xffffffff, size))
	{
		init();
	}

	TextView::TextView(math::vec2 pos, Font* font, float size, std::string text)
		: GUI(pos, math::vec2(0, 0)), m_label(new Label(text, font, pos, 0xffffffff, size))
	{
		init();
	}

	TextView::TextView(math::vec2 pos, Font* font, float size, std::string text, uint color)
		: GUI(pos, math::vec2(0, 0)), m_label(new Label(text, font, pos, color, size))
	{
		init();
	}

	TextView::TextView(math::vec2 pos, float size)
		: GUI(pos, math::vec2(0, 0)), m_label(new Label("", s_defaultFont, pos, 0xffffffff, size))
	{
		init();
	}

	TextView::TextView(math::vec2 pos, float size, std::string text)
		: GUI(pos, math::vec2(0, 0)), m_label(new Label(text, s_defaultFont, pos, 0xffffffff, size))
	{
		init();
	}

	TextView::TextView(math::vec2 pos, float size, std::string text, uint color)
		: GUI(pos, math::vec2(0, 0)), m_label(new Label(text, s_defaultFont, pos, color, size))
	{
		init();
	}

	void TextView::init()
	{
		m_size = math::vec2(m_label->getWidth(), m_label->getSize());
		m_canSelect = false;
		m_renderbackground = false;
		updateMatrix();
	}

	void TextView::submitComponents(Renderer2D* renderer) const
	{
		m_label->submit(renderer);
	}

	void TextView::setForegroundColor(uint color)
	{
		GUI::setForegroundColor(color);
		m_label->setColor(color);
	}
}}
