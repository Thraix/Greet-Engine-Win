#include "GUI.h"

namespace Greet {
	
	Sprite* GUI::m_mask;

	GUI::GUI(const Vec2& position, const Vec2& size)
	:Group(Vec2(0, 0)), m_position(position), m_size(size), m_margin(LTRB()), m_backgroundColor(GUI_DEFAULT_BACKGROUND)
	{
		m_transformationMatrix = Mat3::Translate(m_position);
		if (m_mask == NULL)
			m_mask = new Sprite(TextureManager::Get2D("mask2"));
	}
	
	GUI::GUI(const Vec2& position, const Vec2& size, const LTRB& margin)
		: Group(Vec2(0,0)), m_position(position), m_size(size), m_margin(margin), m_backgroundColor(GUI_DEFAULT_BACKGROUND)
	{
		m_transformationMatrix = Mat3::Translate(m_position);
		if (m_mask == NULL)
			m_mask = new Sprite(TextureManager::Get2D("mask2"));
	}

	GUI::~GUI()
	{
	}

	void GUI::Add(Renderable* renderable)
	{
		ASSERT(false, "GUI doesn't accept Renderables only GUIs.");
	}

	void GUI::Add(GUI* renderable)
	{
		Group::Add(renderable);
		renderable->m_parent = this;
	}

	bool GUI::OnPressed(const KeyPressedEvent& e)
	{ 
		return false;
	}

	bool GUI::OnReleased(const KeyReleasedEvent& e)
	{ 
		return false;
	}

	bool GUI::OnTyped(const KeyTypedEvent& e)
	{
		return false;
	}

	GUI* GUI::OnPressed(const MousePressedEvent& event, Vec2 relativeMousePos) 
	{ 
		// If we are not inside the GUI return
		if (!m_enabled || !m_mouseInside)
			return NULL; // No GUI that can be focused

		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = ((GUI*)m_renderables[i]);
			// Check if mouse is within child-GUIs
			if (gui->OnPressed(event, TranslateMouse(relativeMousePos, gui)))
				return gui;
		}
		return this;
	}

	GUI* GUI::OnReleased(const MouseReleasedEvent& event, Vec2 relativeMousePos) 
	{ 
		if (!m_enabled)
			return NULL;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = ((GUI*)m_renderables[i]);
			// Check if mouse is within child-GUIs
			gui->OnReleased(event, TranslateMouse(relativeMousePos, gui));
		}
		return NULL;
	}

	bool GUI::OnMoved(const MouseMovedEvent& event, Vec2 relativeMousePos)
	{
		if (IsInside(relativeMousePos))
		{
			if (!m_mouseInside)
				OnMouseEnter();
			m_mouseInside = true;
		}
		else
		{
			if (m_mouseInside)
				OnMouseExit();
			m_mouseInside = false;
		}

		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = ((GUI*)m_renderables[i]);
			gui->OnMoved(event, TranslateMouse(relativeMousePos, gui));
		}
		return m_mouseInside;
	}


	bool GUI::Update(float timeElapsed) 
	{
		if(m_parent == NULL)
			m_transformationMatrix = Mat3::Translate(m_position);
		else
			m_transformationMatrix = Mat3::Translate(m_position + Vec2(m_parent->m_margin.left, m_parent->m_margin.top));
		return Group::Update(timeElapsed);
	}

	void GUI::Submit(Renderer2D* renderer) const
	{
		if(m_renderBackground)
			renderer->FillRect(Vec2(0,0), m_size, m_backgroundColor, m_mask);
		Render(renderer);
	}

	void GUI::Render(Renderer2D* renderer) const
	{
		Group::Submit(renderer);
	}

	const Vec2& GUI::GetRealPosition() const
	{
		if(m_parent)
			return m_parent->GetPosition()+m_position;
		return m_position;
	}

	void GUI::SetFocused(bool focused)
	{
		if (m_focused != focused)
		{
			OnFocused(focused);
			m_focused = focused;
		}
	}

	bool GUI::IsInside(const Vec2& position) const
	{
		return position.x >= 0 && position.x < m_size.x && position.y >= 0 && position.y < m_size.y;
//		return MOUSE_INSIDE_GUI(position, m_size.x, m_size.y);
	}

	Vec2 GUI::TranslateMouse(const Vec2& mousePos, GUI* target) const
	{	
		return mousePos - target->m_position - Vec2(m_margin.left, m_margin.top);
	}
}
