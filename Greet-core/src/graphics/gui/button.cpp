#include "button.h"

namespace Greet {

	Button::Button(const vec2& position, const vec2 size, const std::string& text)
		: GUI(position,size), m_text(text), m_font(FontManager::get("anonymous",size.y * 0.75))
	{
		m_renderBackground = true;
		m_backgroundColor = ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 9));
		m_buttonBigger = false;
	}

	void Button::render(Renderer2D* renderer) const
	{
		GUI::render(renderer);
		renderer->submitString(m_text, m_size/2.0f + vec2(-m_font->getWidthOfText(m_text)/2, m_font->getSize()*0.25f),m_font, ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 5)));
	}

	void Button::onMouseEnter()
	{
		if (!m_buttonBigger)
		{
			DriverDispatcher::addDriver(new RectDriver(m_position.x, m_position.y, m_size.x, m_size.y, -BUTTON_RESIZE_SIZE, -BUTTON_RESIZE_SIZE, BUTTON_RESIZE_SIZE * 2, BUTTON_RESIZE_SIZE * 2, BUTTON_RESIZE_TIME, true, new DriverAdapter()));
			m_buttonBigger = true;
		}
	}

	void Button::onMouseExit()
	{
		if (m_buttonBigger)
		{
			DriverDispatcher::addDriver(new RectDriver(m_position.x, m_position.y, m_size.x, m_size.y, BUTTON_RESIZE_SIZE, BUTTON_RESIZE_SIZE, -BUTTON_RESIZE_SIZE * 2, -BUTTON_RESIZE_SIZE * 2, BUTTON_RESIZE_TIME, true, new DriverAdapter()));
			m_buttonBigger = false;
		}
	}

	bool Button::onMoved(const MouseMovedEvent& event, vec2 relativeMousePos)
	{
		GUI::onMoved(event, relativeMousePos);
		return false;
	}

	GUI* Button::onPressed(const MousePressedEvent& event, vec2 relativeMousePos)
	{
		return GUI::onPressed(event, relativeMousePos);
	}
	GUI* Button::onReleased(const MouseReleasedEvent& event, vec2 relativeMousePos)
	{
		GUI::onReleased(event, relativeMousePos);
		return NULL;
	}
}