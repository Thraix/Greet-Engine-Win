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

		// True if the slider should snap into position
		bool m_snap;

		// Size of the steps in between snap values
		float m_stepSize;
		// Value when the slider is at the start
		float m_startValue;
		// Value when the slider is at the end
		float m_endValue;
		// True if the label should be displayed as a percentage.
		bool m_percentage;

		// True if the user is holding the slider
		bool m_holdSlider;
		// Slider label font
		Font* m_sliderFont;
		
		// The slidercontroller for this slider
		// Will get deleted by the engine
		SliderController* m_sliderController;

		// Defined labels for the slider
		// If empty display the value instead
		std::vector<std::string> m_labels;
	private:
		void snapSlider();
	public:
		Slider(const vec2& position, const vec2& size, float start, float end, float stepSize, float sliderWidth = 7);
		Slider(const vec2& position, const vec2& size, const std::vector<std::string>& labels, float sliderWidth = 7);
		virtual ~Slider();

		void render(Renderer2D* renderer) const override;
		bool onMoved(const MouseMovedEvent& event, vec2 relativeMousePos) override;
		GUI* onPressed(const MousePressedEvent& event, vec2 relativeMousePos) override;
		GUI* onReleased(const MouseReleasedEvent& event, vec2 relativeMousePos) override;

		void setSnapping(bool snapping);
		bool isInside(const vec2& position) const override;
		void setRenderPercentage(bool percentage);
		void setStepSize(float stepSize) { if(m_labels.empty()) m_stepSize = stepSize; }
		void setSliderController(SliderController* controller);
		void setValue(float value);
		inline float getValue() const;
		inline float getPosFromValue() const;
		inline float getPosFromValue(float value) const;
		inline float getStepSize() const { return m_stepSize; }
		inline float getSliderPos() const { return m_sliderController->m_position.x; }

	};
}
