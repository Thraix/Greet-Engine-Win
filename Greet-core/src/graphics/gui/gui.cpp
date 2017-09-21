#include "gui.h"

namespace Greet {
	
	Sprite* GUI::m_mask;

	GUI::GUI(const vec2& position, const vec2& size)
	:Group(vec2(0, 0)), m_position(position), m_size(size), m_padding(LTRB()), m_margin(LTRB()), m_backgroundColor(GUI_DEFAULT_BACKGROUND)
	{
		m_transformationMatrix = mat3::translate(m_position + vec2(m_margin.left + m_padding.left, m_margin.top + m_padding.top));
		if (m_mask == NULL)
			m_mask = new Sprite(TextureManager::get2D("mask2"));
	}
	
	GUI::GUI(const vec2& position, const vec2& size, const LTRB& margin, const LTRB& padding)
		: Group(vec2(0,0)), m_position(position), m_size(size), m_margin(margin), m_padding(padding), m_backgroundColor(GUI_DEFAULT_BACKGROUND)
	{
		m_transformationMatrix = mat3::translate(m_position + vec2(m_margin.left + m_padding.left, m_margin.top + m_padding.top));
		if (m_mask == NULL)
			m_mask = new Sprite(TextureManager::get2D("mask2"));
	}

	GUI::~GUI()
	{
	}

	bool GUI::onPressed(KeyPressedEvent& event)
	{ 
		return m_mouseInside;
	}

	bool GUI::onReleased(KeyReleasedEvent& event) 
	{ 
		return m_mouseInside;
	}

	bool GUI::onPressed(const MousePressedEvent& event, vec2 relativeMousePos) 
	{ 
		vec2 pos(relativeMousePos.x - m_padding.left, relativeMousePos.y - m_padding.top);
		GUI* gui;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			gui = ((GUI*)m_renderables[i]);
			gui->onPressed(event, pos - gui->m_position - vec2(gui->m_margin.left, gui->m_margin.top));
		}
		return m_mouseInside;
	}

	bool GUI::onReleased(const MouseReleasedEvent& event, vec2 relativeMousePos) 
	{ 
		vec2 pos(relativeMousePos.x - m_padding.left, relativeMousePos.y - m_padding.top);
		GUI* gui;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			gui = ((GUI*)m_renderables[i]);
			gui->onReleased(event, pos - gui->m_position - vec2(gui->m_margin.left, gui->m_margin.top));
		}
		return m_mouseInside;
	}

	bool GUI::onMoved(const MouseMovedEvent& event, vec2 relativeMousePos)
	{
		vec2 pos(relativeMousePos.x - m_padding.left, relativeMousePos.y - m_padding.top);
		if (isInside(relativeMousePos))
		{
			if (!m_mouseInside)
				onMouseEnter();
			m_mouseInside = true;
		}
		else
		{
			if (m_mouseInside)
				onMouseExit();
			m_mouseInside = false;
		}
		GUI* gui;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			gui = ((GUI*)m_renderables[i]);
			gui->onMoved(event, pos - gui->m_position - vec2(gui->m_margin.left, gui->m_margin.top));
		}
		return m_mouseInside;
	}


	bool GUI::update(float timeElapsed) 
	{
		m_transformationMatrix = mat3::translate(m_position+vec2(m_margin.left+m_padding.left, m_margin.top + m_padding.top));
		return Group::update(timeElapsed);
	}

	void GUI::submit(Renderer2D* renderer) const
	{
		if(m_renderBackground)
			renderer->fillRect(vec2(-m_padding.left, -m_padding.top), m_size, m_backgroundColor, m_mask);
		render(renderer);
	}

	void GUI::render(Renderer2D* renderer) const
	{
		Group::submit(renderer);
	}

	const vec2& GUI::getRealPosition()
	{
		if(m_parent)
			return m_parent->getPosition()+m_position;
		return m_position;
	}

	bool GUI::isInside(const vec2& position)
	{
		return MOUSE_INSIDE_GUI(position, m_size.x, m_size.y);
	}
}
