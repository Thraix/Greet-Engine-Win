#include "slidercontroller.h"

namespace Greet
{

	SliderController::SliderController(vec2 sliderSize, vec2 size)
		: GUI(vec2(sliderSize.x / 2, sliderSize.y / 2), size, LTRB(0, 0, 0, 0))
	{
		setBackgroundColor(ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 9)));
	}

	void SliderController::submit(Renderer2D* renderer) const
	{
		if (m_renderBackground)
			renderer->fillRect(vec2(-(m_size.x - 1)/2,-m_size.y/2), m_size, m_backgroundColor, m_mask);
		render(renderer);
	}

	bool SliderController::onMoved(const MouseMovedEvent& event, vec2 relativeMousePos)
	{
		// Check if mouse is inside the controller
		GUI::onMoved(event, relativeMousePos);
		bool inside = m_mouseInside;
		if (inside && !m_wasInside)
		{
			// Dummy variables
			float f0, f1;
			DriverDispatcher::addDriver(new RectDriver(f0, f1, m_size.x, m_size.y, -3.0f, -3.0f, 6.0f, 6.0f, 0.08f, true, new DriverAdapter()));
		}
		else if (!inside && m_wasInside)
		{
			// Dummy variables
			float f0, f1;
			DriverDispatcher::addDriver(new RectDriver(f0, f1, m_size.x, m_size.y, 3.0f, 3.0f, -6.0f, -6.0f, 0.08f, true, new DriverAdapter()));
		}
		m_wasInside = inside;
		return false;
	}

	bool SliderController::isInside(const vec2& position) const
	{
		return position.x >= -(m_size.x - 1) / 2 && position.x < m_size.x - (m_size.x - 1)/2 && position.y >= -m_size.y / 2 && position.y < m_size.y/2;
	}
}