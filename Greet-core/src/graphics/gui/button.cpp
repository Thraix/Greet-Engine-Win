#include "button.h"

namespace greet { namespace graphics {

	using namespace utils;

	Button::Button(const math::vec2& position, const math::vec2 size, const std::string& text)
		: GUI(position,size), m_text(text), m_font(graphics::FontManager::get("anonymous",size.y * 0.75))
	{
		m_renderBackground = true;
		m_backgroundColor = ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 9));
		m_buttonBigger = false;
	}

	void Button::render(Renderer2D* renderer) const
	{
		GUI::render(renderer);
		renderer->submitString(m_text, m_size/2.0f + math::vec2(-m_font->getWidthOfText(m_text)/2, m_font->getSize()*0.25f),m_font, ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 5)));
	}

	void Button::onMouseEnter()
	{
		if (!m_buttonBigger)
		{
			drivers::DriverDispatcher::addDriver(new drivers::RectDriver(m_position.x, m_position.y, m_size.x, m_size.y, -BUTTON_RESIZE_SIZE, -BUTTON_RESIZE_SIZE, BUTTON_RESIZE_SIZE * 2, BUTTON_RESIZE_SIZE * 2, BUTTON_RESIZE_TIME, true, new drivers::DriverAdapter()));
			m_buttonBigger = true;
		}
	}

	void Button::onMouseExit()
	{
		if (m_buttonBigger)
		{
			drivers::DriverDispatcher::addDriver(new drivers::RectDriver(m_position.x, m_position.y, m_size.x, m_size.y, BUTTON_RESIZE_SIZE, BUTTON_RESIZE_SIZE, -BUTTON_RESIZE_SIZE * 2, -BUTTON_RESIZE_SIZE * 2, BUTTON_RESIZE_TIME, true, new drivers::DriverAdapter()));
			m_buttonBigger = false;
		}
	}

	bool Button::onMoved(const event::MouseMovedEvent& event, math::vec2 relativeMousePos)
	{
		GUI::onMoved(event, relativeMousePos);
		return false;
	}

	bool Button::onPressed(const event::MousePressedEvent& event, math::vec2 relativeMousePos)
	{
		GUI::onPressed(event, relativeMousePos);
		return false;
	}
	bool Button::onReleased(const event::MouseReleasedEvent& event, math::vec2 relativeMousePos)
	{
		GUI::onReleased(event, relativeMousePos);
		return false;
	}
} }