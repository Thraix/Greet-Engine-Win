#pragma once

#include <graphics/gui/gui.h>
#include <drivers/rectdriver.h>
#include <drivers/driverdispatcher.h>
#include <drivers/driveradapter.h>

namespace Greet {

	class SliderController : public GUI
	{
	private:
		bool m_wasInside;

	public:
		SliderController(vec2 sliderSize, vec2 size);

		virtual bool isInside(const vec2& position) const override;
		virtual void submit(Renderer2D* renderer) const override;

		bool onMoved(const MouseMovedEvent& event, vec2 relativeMousePos) override;
	};

};