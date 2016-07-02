#include "slider.h"

namespace greet { namespace graphics {
	using namespace utils;
	Slider::Slider(const math::vec2& position, const float& width, float stepSize)
		: GUI(position,math::vec2(width, SLIDER_HEIGHT)), m_stepSize(stepSize),m_pos((width - SLIDER_WIDTH)/2.0f)
		, m_sliderLine(new Renderable2D(math::vec2(SLIDER_WIDTH_2, SLIDER_HEIGHT / 2.0f-2), math::vec2(width - SLIDER_WIDTH, 4), 0xff919191, NULL))
		, m_slider(new Renderable2D(math::vec2(m_pos-SLIDER_WIDTH_2, 0), math::vec2(SLIDER_WIDTH, SLIDER_HEIGHT), ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 9)), NULL))
	{
		GUI::add(m_sliderLine);
		GUI::add(m_slider);
	}
}}