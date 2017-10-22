#include "slider.h"

#define SLIDER_WIDTH_BASE 7

namespace Greet {
	Slider::Slider(const vec2& position, const vec2& size, float start, float end, float stepSize)
		: GUI(position, vec2(size.x, size.y), LTRB(0, 0, 0, 0)), m_stepSize(stepSize), m_sliderPos(size.x/2), m_startValue(start), m_endValue(end),
		m_sliderFont(FontManager::get("anonymous",24)), m_sliderController(new SliderController(size, vec2(SLIDER_WIDTH_BASE, size.y+6)))
		, m_sliderColor()
	{
		m_renderBackground = true;
		m_backgroundColor = ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 15));
		add(m_sliderController);
	}

	Slider::~Slider()
	{
		//delete m_sliderController;
	}

	bool Slider::onMoved(const MouseMovedEvent& event, vec2 relativeMousePos)
	{
		bool moved = GUI::onMoved(event, relativeMousePos);
		if (event.isDragged())
		{
			if (m_holdSlider)
			{
				m_sliderPos = relativeMousePos.x < 0 ? 0 : (relativeMousePos.x >= m_size.x ? m_size.x - 1 : relativeMousePos.x);
				m_sliderController->m_position.x = m_sliderPos;
			}
		}
		return moved;
	}

	GUI* Slider::onPressed(const MousePressedEvent& event, vec2 relativeMousePos)
	{
		GUI* pressed = GUI::onPressed(event, relativeMousePos);
		if (pressed != this && pressed != m_sliderController)
			return pressed;
		if (event.getButton() == GLFW_MOUSE_BUTTON_1)
		{
			m_holdSlider = true;
			m_sliderPos = relativeMousePos.x < 0 ? 0 : (relativeMousePos.x >= m_size.x ? m_size.x - 1 : relativeMousePos.x);
			m_sliderController->m_position.x = m_sliderPos;
			return pressed;
		}

		// If we didn't press on the slider return NULL
		return NULL;
	}

	GUI* Slider::onReleased(const MouseReleasedEvent& event, vec2 relativeMousePos)
	{
		GUI::onReleased(event, relativeMousePos);
		if (event.getButton() == GLFW_MOUSE_BUTTON_1)
		{
			m_holdSlider = false;
		}
		return NULL;
	}



	void Slider::render(Renderer2D* renderer) const
	{
		GUI::render(renderer);

		uint sliderColor = ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 3));
		// Start and end values
		std::string value = StringUtils::toString(getValue());
		float yPos = m_size.y / 2.0f + m_sliderFont->getSize()*0.25f;
		renderer->submitString(value, vec2((m_size.x - m_sliderFont->getWidthOfText(value)) / 2.0f, yPos), m_sliderFont, sliderColor);
	}

	bool Slider::isInsideSlider(const vec2& pos) const
	{
		return false;//m_sliderController.//MOUSE_INSIDE(pos, m_sliderPos - (m_sliderSize.x - SLIDER_WIDTH_BASE) / 2 - m_padding.left, (m_size.y - m_sliderSize.y)/2 - m_padding.top, m_sliderSize.x, m_sliderSize.y);
	}
}