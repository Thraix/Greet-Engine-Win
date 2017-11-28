#pragma once

#include <graphics/gui/GUI.h>
#include <drivers/RectDriver.h>
#include <drivers/DriverDispatcher.h>
#include <graphics/layers/GUILayer.h>

namespace Greet {

	class SliderController : public GUI
	{
	private:
		bool m_wasInside;

	public:
		SliderController(const vec2& position, const vec2& size);

		virtual bool isInside(const vec2& position) const override;
		virtual void submit(Renderer2D* renderer) const override;

		bool onMoved(const MouseMovedEvent& event, vec2 relativeMousePos) override;
	};

};