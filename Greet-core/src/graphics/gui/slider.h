#pragma once

#include <math/math_func.h>
#include <graphics/gui/gui.h>
#include <graphics/gui/slidercontroller.h>
#include <utils/colorutils.h>
#include <graphics/fonts/fontmanager.h>
#include <drivers/rectdriver.h>
#include <drivers/driverdispatcher.h>
#include <drivers/driveradapter.h>

namespace Greet {

	class Slider : public GUI
	{
	private:
		int m_sliderPos;

		float m_stepSize;
		float m_startValue;
		float m_endValue;

		uint m_sliderColor;
		bool m_holdSlider;
		Font* m_sliderFont;
		bool m_inSlider;
		
		SliderController* m_sliderController;

	public:
		Slider(const vec2& position, const vec2& size, float start, float end, float stepSize);
		virtual ~Slider();
		void setStepSize(float stepSize) { m_stepSize = stepSize; }

		void render(Renderer2D* renderer) const override;
		bool onMoved(const MouseMovedEvent& event, vec2 relativeMousePos) override;
		GUI* onPressed(const MousePressedEvent& event, vec2 relativeMousePos) override;
		GUI* onReleased(const MouseReleasedEvent& event, vec2 relativeMousePos) override;
		inline float getStepSize() const { return m_stepSize; }
		inline float getSliderPos() const { return m_sliderPos; }
		inline float getValue() const { return  Math::roundClose((m_sliderPos / (m_size.x - 1))*(m_endValue - m_startValue) + m_startValue,m_stepSize); }
		inline float getPosFromValue() const { return (getValue() - m_startValue) / (m_endValue - m_startValue)*(m_size.x - 1); }
		inline bool isInsideSlider(const vec2& pos) const;
	};
}
