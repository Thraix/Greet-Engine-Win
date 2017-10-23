#include "gui.h"

namespace Greet {
	
	Sprite* GUI::m_mask;

	GUI::GUI(const vec2& position, const vec2& size)
	:Group(vec2(0, 0)), m_position(position), m_size(size), m_margin(LTRB()), m_backgroundColor(GUI_DEFAULT_BACKGROUND)
	{
		m_transformationMatrix = mat3::translate(m_position);
		if (m_mask == NULL)
			m_mask = new Sprite(TextureManager::get2D("mask2"));
	}
	
	GUI::GUI(const vec2& position, const vec2& size, const LTRB& margin)
		: Group(vec2(0,0)), m_position(position), m_size(size), m_margin(margin), m_backgroundColor(GUI_DEFAULT_BACKGROUND)
	{
		m_transformationMatrix = mat3::translate(m_position);
		if (m_mask == NULL)
			m_mask = new Sprite(TextureManager::get2D("mask2"));
	}

	GUI::~GUI()
	{
	}

	void GUI::add(Renderable* renderable)
	{
		ASSERT(false, "GUI doesn't accept Renderables only GUIs.");
	}

	void GUI::add(GUI* renderable)
	{
		Group::add(renderable);
		renderable->m_parent = this;
	}

	bool GUI::onPressed(KeyPressedEvent& event)
	{ 
		return false;
	}

	bool GUI::onReleased(KeyReleasedEvent& event) 
	{ 
		return false;
	}

	GUI* GUI::onPressed(const MousePressedEvent& event, vec2 relativeMousePos) 
	{ 
		// If we are not inside the GUI return
		if (!m_enabled || !m_mouseInside)
			return NULL; // No GUI that can be focused

		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = ((GUI*)m_renderables[i]);
			// Check if mouse is within child-GUIs
			if (gui->onPressed(event, translateMouse(relativeMousePos, gui)))
				return gui;
		}
		return this;
	}

	GUI* GUI::onReleased(const MouseReleasedEvent& event, vec2 relativeMousePos) 
	{ 
		if (!m_enabled)
			return NULL;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = ((GUI*)m_renderables[i]);
			// Check if mouse is within child-GUIs
			gui->onReleased(event, translateMouse(relativeMousePos, gui));
		}
		return NULL;
	}

	bool GUI::onMoved(const MouseMovedEvent& event, vec2 relativeMousePos)
	{
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

		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = ((GUI*)m_renderables[i]);
			gui->onMoved(event, translateMouse(relativeMousePos, gui));
		}
		return m_mouseInside;
	}


	bool GUI::update(float timeElapsed) 
	{
		if(m_parent == NULL)
			m_transformationMatrix = mat3::translate(m_position);
		else
			m_transformationMatrix = mat3::translate(m_position + vec2(m_parent->m_margin.left, m_parent->m_margin.top));
		return Group::update(timeElapsed);
	}

	void GUI::submit(Renderer2D* renderer) const
	{
		if(m_renderBackground)
			renderer->fillRect(vec2(0,0), m_size, m_backgroundColor, m_mask);
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

	bool GUI::isInside(const vec2& position) const
	{
		return position.x >= 0 && position.x < m_size.x && position.y >= 0 && position.y < m_size.y;
//		return MOUSE_INSIDE_GUI(position, m_size.x, m_size.y);
	}

	vec2 GUI::translateMouse(const vec2& mousePos, GUI* target) const
	{	
		return mousePos - target->m_position - vec2(m_margin.left, m_margin.top);
	}
}
