#include "frame.h"

namespace greet { namespace graphics {
	using namespace utils;
	Frame::Frame(const math::vec2& position, const math::vec2& size, const std::string& title)
	: GUI(position,size, LTRB(), LTRB(10,30,10,10)), m_title(title),m_titleFont(FontManager::get("anonymous", 20))
		,m_titleColor(ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 3)))
		,m_titleBackgroundColor(ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 9)))
	{
		
	}

	void Frame::render(Renderer2D* renderer) const 
	{
		GUI::render(renderer);
		renderer->fillRect(math::vec2(-m_padding.left, -m_padding.top), math::vec2(m_size.x, m_padding.top),m_titleBackgroundColor,GUI::m_mask);
		renderer->submitString(m_title, math::vec2(0, -8),m_titleFont,m_titleColor);
	}

	bool Frame::onMoved(const event::MouseMovedEvent& event, math::vec2 relativeMousePos)
	{
		bool moved = GUI::onMoved(event, relativeMousePos);
		if (event.isDragged())
		{
			if (m_holdFrame)
			{
				m_position += event.getDeltaPosition();
				//m_position.x = m_position.x < 0 ? 0 : m_position.x + m_size.x >= Window::getWidth() ? Window::getWidth() - m_size.x : m_position.x;
				//m_position.y = m_position.y < 0 ? 0 : m_position.y + m_size.y >= Window::getHeight() ? Window::getHeight() - m_size.y : m_position.y;
			}
		}
		return moved;
	}

	bool Frame::onPressed(const event::MousePressedEvent& event, math::vec2 relativeMousePos)
	{
		GUI::onPressed(event, relativeMousePos);
		if (event.getButton() == GLFW_MOUSE_BUTTON_1)
		{
			m_holdFrame = false;
			if (isInsideFrameHeader(relativeMousePos))
			{
				m_holdFrame = true;
				return true;
			}
		}
		return false;
	}

	bool Frame::onReleased(const event::MouseReleasedEvent& event, math::vec2 relativeMousePos)
	{
		GUI::onReleased(event, relativeMousePos);
		if (event.getButton() == GLFW_MOUSE_BUTTON_1)
		{
			m_holdFrame = false;
		}
		return false;
	}

	bool Frame::isInsideFrameHeader(const math::vec2& mouse) const
	{
		return MOUSE_INSIDE(mouse,0,0,m_size.x,m_padding.top);
	}
}}
