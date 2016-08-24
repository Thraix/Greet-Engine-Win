#include "slider.h"

#define SLIDER_WIDTH_BASE 7

namespace greet { namespace graphics {
	using namespace utils;
	Slider::Slider(const math::vec2& position, const math::vec2& size, float start, float end, float stepSize)
		: GUI(position, math::vec2(size.x, size.y), LTRB((SLIDER_WIDTH_BASE-1)/2, 0, (SLIDER_WIDTH_BASE - 1) / 2, 0), LTRB()), m_stepSize(stepSize), m_pos((size.x - SLIDER_WIDTH_BASE) / 2.0f), m_startValue(start), m_endValue(end),
		m_sliderFont(FontManager::get("anonymous",24)),
		m_sliderSize(SLIDER_WIDTH_BASE,size.y+6)
		, m_sliderColor(ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 9)))
	{
		m_renderBackground = true;
		m_backgroundColor = ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 15));;
	}

	bool Slider::onMoved(const event::MouseMovedEvent& event, math::vec2 relativeMousePos)
	{
		bool moved = GUI::onMoved(event, relativeMousePos);
		if (event.isDragged())
		{
			if (m_holdSlider)
			{
				m_pos = relativeMousePos.x < 0 ? 0 : (relativeMousePos.x >= m_size.x ? m_size.x - 1 : relativeMousePos.x);
				//m_pos = getPosFromValue();
			}
		}
		bool inSlider = isInsideSlider(relativeMousePos);
		if (inSlider && !m_inSlider)
		{
			float f1 = 0;
			float f2 = 0;
			drivers::DriverDispatcher::addDriver(new drivers::RectDriver(f1, f2, m_sliderSize.x, m_sliderSize.y, -3.0f, -3.0f, 6.0f, 6.0f, 0.08f, true, new drivers::DriverAdapter()));
		}
		else if (!inSlider && m_inSlider)
		{
			float f1 = 0;
			float f2 = 0;
			drivers::DriverDispatcher::addDriver(new drivers::RectDriver(f1, f2, m_sliderSize.x, m_sliderSize.y, 3.0f, 3.0f, -6.0f, -6.0f, 0.08f, true, new drivers::DriverAdapter()));
		}
		m_inSlider = inSlider;
		return moved;
	}

	bool Slider::onPressed(const event::MousePressedEvent& event, math::vec2 relativeMousePos)
	{
		GUI::onPressed(event, relativeMousePos);
		if (event.getButton() == GLFW_MOUSE_BUTTON_1)
		{
			m_holdSlider = false;
			if (isInside(relativeMousePos) || isInsideSlider(relativeMousePos))
			{
				m_holdSlider = true;
				m_pos = relativeMousePos.x < 0 ? 0 : (relativeMousePos.x >= m_size.x ? m_size.x - 1 : relativeMousePos.x);
				return true;
			}
		}
		return false;
	}

	bool Slider::onReleased(const event::MouseReleasedEvent& event, math::vec2 relativeMousePos)
	{
		GUI::onReleased(event, relativeMousePos);
		if (event.getButton() == GLFW_MOUSE_BUTTON_1)
		{
			m_holdSlider = false;
		}
		return false;
	}



	void Slider::render(Renderer2D* renderer) const
	{
		GUI::render(renderer);

		// Slider horizontal line
		//renderer->fillRect(math::vec2(0, SLIDER_HEIGHT / 2.0f - 2), math::vec2(m_width, 4), 0xff616161);
		// Slider vertical line
		renderer->fillRect(math::vec2(m_pos - (m_sliderSize.x - 1) / 2, (m_size.y - m_sliderSize.y)/2.0f), math::vec2(m_sliderSize.x, m_sliderSize.y), ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 9)),GUI::m_mask);

		uint sliderColor = ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 3));
		// Start and end values
		//std::string startValue = utils::toString(m_startValue);
		std::string value = utils::toString(getValue());
		//std::string endValue = utils::toString(m_endValue);
		float yPos = m_size.y / 2.0f + m_sliderFont->getSize()*0.25f;
		//renderer->submitString(startValue, math::vec2(-m_sliderFont->getWidthOfText(startValue)/2.0f, yPos), m_sliderFont, sliderColor);
		//renderer->submitString(endValue, math::vec2(m_width - m_sliderFont->getWidthOfText(endValue) / 2.0f, yPos), m_sliderFont, sliderColor);
		renderer->submitString(value, math::vec2((m_size.x - m_sliderFont->getWidthOfText(value)) / 2.0f, yPos), m_sliderFont, sliderColor);
	}

	bool Slider::isInsideSlider(const math::vec2& pos) const
	{
		return MOUSE_INSIDE(pos, m_pos - (m_sliderSize.x - 1) / 2, 0, m_sliderSize.x, m_sliderSize.y);
	}
}}