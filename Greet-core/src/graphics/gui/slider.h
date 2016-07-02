#pragma once

#include <graphics/gui/gui.h>
#include <utils/colorutils.h>

#define SLIDER_WIDTH 7
#define SLIDER_HEIGHT 30
#define SLIDER_WIDTH_2 (SLIDER_WIDTH-1)/2

namespace greet { namespace graphics {

	class Slider : public GUI
	{
	private:
		uint m_pos;
		float m_stepSize;
		Renderable2D* m_slider;
		Renderable2D* m_sliderLine;
	public:
		Slider(const math::vec2& position, const float& width, float stepSize);
		void setStepSize(float stepSize) { m_stepSize = stepSize; }
		inline float getStepSize() const { return m_stepSize; }
		inline float getSliderPos() const { return m_stepSize * m_pos / (m_background->getSize().x - SLIDER_WIDTH); }
		math::vec2 getOffsetTL() const override { return math::vec2(SLIDER_WIDTH_2, 0); }
		math::vec2 getOffsetBR() const { return math::vec2(SLIDER_WIDTH_2, 0); }
	};
}}
