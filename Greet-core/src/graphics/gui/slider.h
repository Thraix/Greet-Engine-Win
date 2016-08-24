#pragma once

#include <graphics/gui/gui.h>
#include <utils/colorutils.h>
#include <graphics/fonts/fontmanager.h>
#include <drivers/rectdriver.h>
#include <drivers/driverdispatcher.h>
#include <drivers/driveradapter.h>

namespace greet { namespace graphics {

	class Slider : public GUI
	{
	private:
		int m_pos;
		float m_stepSize;
		float m_startValue;
		float m_endValue;
		uint m_sliderColor;
		bool m_holdSlider;
		Font* m_sliderFont;
		bool m_inSlider;

		math::vec2 m_sliderSize;

	public:
		Slider(const math::vec2& position, const math::vec2& size, float start, float end, float stepSize);
		void setStepSize(float stepSize) { m_stepSize = stepSize; }

		void render(Renderer2D* renderer) const override;
		bool onMoved(const event::MouseMovedEvent& event, math::vec2 relativeMousePos) override;
		bool onPressed(const event::MousePressedEvent& event, math::vec2 relativeMousePos) override;
		bool onReleased(const event::MouseReleasedEvent& event, math::vec2 relativeMousePos) override;
		inline float getStepSize() const { return m_stepSize; }
		inline float getSliderPos() const { return m_stepSize * m_pos / (m_size.x - m_sliderSize.x); }
		inline float getValue() const { return utils::roundClose((m_pos / (m_size.x - 1))*(m_endValue - m_startValue) + m_startValue,m_stepSize); }
		inline float getPosFromValue() const { return (getValue() - m_startValue) / (m_endValue - m_startValue)*(m_size.x - 1); }
		inline bool isInsideSlider(const math::vec2& pos) const;
	};
}}
