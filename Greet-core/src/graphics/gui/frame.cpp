#include "frame.h"
#include <graphics/window.h>
namespace Greet {

	Frame::Frame(const vec2& position, const vec2& size, const std::string& title)
	: GUI(position,size, LTRB(10,40,10,10)), m_title(title),m_titleFont(FontManager::get("anonymous", 20))
		,m_titleColor(ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 3)))
		,m_titleBackgroundColor(ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 9)))
	{
		
	}

	void Frame::render(Renderer2D* renderer) const 
	{
		GUI::render(renderer);
		renderer->fillRect(vec2(0, 0), vec2(m_size.x, m_margin.top-10),m_titleBackgroundColor,GUI::m_mask);
		renderer->submitString(m_title, vec2(m_margin.left, 22),m_titleFont,m_titleColor);
	}

	bool Frame::onMoved(const MouseMovedEvent& event, vec2 relativeMousePos)
	{
		bool moved = GUI::onMoved(event, relativeMousePos);
		if (event.isDragged())
		{
			if (m_holdFrame)
			{
				m_position = m_holdPosition + event.getPosition();
				m_position.x = m_position.x < 0 ? 0 : m_position.x + m_size.x >= Window::getWidth() ? Window::getWidth() - m_size.x : m_position.x;
				m_position.y = m_position.y < 0 ? 0 : m_position.y + m_size.y >= Window::getHeight() ? Window::getHeight() - m_size.y : m_position.y;
			}
		}
		return moved;
	}

	GUI* Frame::onPressed(const MousePressedEvent& event, vec2 relativeMousePos)
	{
		GUI* pressed = GUI::onPressed(event, relativeMousePos);
		if (pressed != this)
			return pressed;

		if (event.getButton() == GLFW_MOUSE_BUTTON_1)
		{
			m_holdFrame = false;
			if (isInsideFrameHeader(relativeMousePos))
			{
				m_holdPosition = m_position - event.getPosition();
				m_holdFrame = true;
				return this;
			}
		}
		return NULL;
	}

	GUI* Frame::onReleased(const MouseReleasedEvent& event, vec2 relativeMousePos)
	{
		GUI::onReleased(event, relativeMousePos);
		if (event.getButton() == GLFW_MOUSE_BUTTON_1)
		{
			m_holdFrame = false;
		}
		return NULL;
	}

	bool Frame::isInsideFrameHeader(const vec2& mouse) const
	{
		return MOUSE_INSIDE(mouse,0,0,m_size.x,m_margin.top-10);
	}
}
