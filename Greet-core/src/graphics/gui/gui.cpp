#include "gui.h"

namespace greet { namespace graphics {
	
	Sprite* GUI::m_mask;

	GUI::GUI(const math::vec2& position, const math::vec2& size)
	:Group(math::vec2(0, 0)), m_position(position), m_size(size), m_padding(LTRB()), m_margin(LTRB()), m_backgroundColor(GUI_DEFAULT_BACKGROUND)
	{
		m_transformationMatrix = math::mat3::translate(m_position + math::vec2(m_margin.left + m_padding.left, m_margin.top + m_padding.top));
		if (m_mask == NULL)
			m_mask = new Sprite(graphics::TextureManager::get("mask2")->getTexId(),32,32,math::vec2(0,0),math::vec2(1,1));
	}
	
	GUI::GUI(const math::vec2& position, const math::vec2& size, const LTRB& margin, const LTRB& padding)
		: Group(math::vec2(0,0)), m_position(position), m_size(size), m_margin(margin), m_padding(padding), m_backgroundColor(GUI_DEFAULT_BACKGROUND)
	{
		m_transformationMatrix = math::mat3::translate(m_position + math::vec2(m_margin.left + m_padding.left, m_margin.top + m_padding.top));
		if (m_mask == NULL)
			m_mask = new Sprite(graphics::TextureManager::get("mask2")->getTexId(), 32, 32, math::vec2(0, 0), math::vec2(1, 1));
	}

	GUI::~GUI()
	{
	}

	bool GUI::onPressed(event::KeyPressedEvent& event)
	{ 
		return m_mouseInside;
	}

	bool GUI::onReleased(event::KeyReleasedEvent& event) 
	{ 
		return m_mouseInside;
	}

	bool GUI::onPressed(const event::MousePressedEvent& event, math::vec2 relativeMousePos) 
	{ 
		math::vec2 pos(relativeMousePos.x - m_padding.left, relativeMousePos.y - m_padding.top);
		GUI* gui;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			gui = ((GUI*)m_renderables[i]);
			gui->onPressed(event, pos - gui->m_position - math::vec2(gui->m_margin.left, gui->m_margin.top));
		}
		return m_mouseInside;
	}

	bool GUI::onReleased(const event::MouseReleasedEvent& event, math::vec2 relativeMousePos) 
	{ 
		math::vec2 pos(relativeMousePos.x - m_padding.left, relativeMousePos.y - m_padding.top);
		GUI* gui;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			gui = ((GUI*)m_renderables[i]);
			gui->onReleased(event, pos - gui->m_position - math::vec2(gui->m_margin.left, gui->m_margin.top));
		}
		return m_mouseInside;
	}

	bool GUI::onMoved(const event::MouseMovedEvent& event, math::vec2 relativeMousePos)
	{
		math::vec2 pos(relativeMousePos.x - m_padding.left, relativeMousePos.y - m_padding.top);
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
			gui->onMoved(event, pos - gui->m_position - math::vec2(gui->m_margin.left, gui->m_margin.top));
		}
		return m_mouseInside;
	}


	bool GUI::update(float timeElapsed) 
	{
		m_transformationMatrix = math::mat3::translate(m_position+math::vec2(m_margin.left+m_padding.left, m_margin.top + m_padding.top));
		return Group::update(timeElapsed);
	}

	void GUI::submit(Renderer2D* renderer) const
	{
		if(m_renderBackground)
			renderer->fillRect(math::vec2(-m_padding.left, -m_padding.top), m_size, m_backgroundColor, m_mask);
		render(renderer);
	}

	void GUI::render(Renderer2D* renderer) const
	{
		Group::submit(renderer);
	}

	const math::vec2& GUI::getRealPosition()
	{
		if(m_parent)
			return m_parent->getPosition()+m_position;
		return m_position;
	}

	bool GUI::isInside(const math::vec2& position)
	{
		return MOUSE_INSIDE_GUI(position, m_size.x, m_size.y);
	}
}}
