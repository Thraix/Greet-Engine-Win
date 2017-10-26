#include "slider.h"

namespace Greet {

	Slider::Slider(const vec2& position, const vec2& size, float start, float end, float stepSize, float sliderWidth)
		: GUI(position, vec2(size.x, size.y)), m_stepSize(stepSize), m_startValue(start), m_endValue(end), m_snap(false),
			m_sliderFont(FontManager::get("anonymous",24)), m_sliderController(new SliderController(size/2, vec2(sliderWidth, size.y+6)))
	{
		m_renderBackground = true;
		m_backgroundColor = ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 15));
		add(m_sliderController);
		m_sliderController->m_position.x = getPosFromValue();
	}

	Slider::Slider(const vec2& position, const vec2& size, const std::vector<std::string>& labels, float sliderWidth)
		: Slider(position, size, 0,labels.size()-1,1,sliderWidth)
	{
		m_labels = labels;
		setSnapping(true);
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
				m_sliderController->m_position.x = relativeMousePos.x;
				Math::clamp(&m_sliderController->m_position.x, 0, m_size.x-1);
				if(m_snap)
					snapSlider();
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
			m_sliderController->m_position.x = relativeMousePos.x;
			Math::clamp(&m_sliderController->m_position.x, 0, m_size.x);
			if (m_snap)
				snapSlider();
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
		std::string value;
		if (m_labels.size() == 0)
		{
			if(m_percentage)
				value = StringUtils::toString((int)(getValue() / (m_endValue - m_startValue) * 100))+"%";
			else
				value = StringUtils::toString(getValue());
		}
		else
		{
			value = m_labels[getValue()];
		}
		float yPos = m_size.y / 2.0f + m_sliderFont->getSize()*0.25f;
		renderer->submitString(value, vec2((m_size.x - m_sliderFont->getWidthOfText(value)) / 2.0f, yPos), m_sliderFont, sliderColor);
	}

	void Slider::snapSlider()
	{
		m_sliderController->m_position.x = getPosFromValue();
	}

	bool Slider::isInside(const vec2& position) const
	{
		return GUI::isInside(position) || m_sliderController->isInside(translateMouse(position, m_sliderController));
	}

	void Slider::setSnapping(bool snapping)
	{
		m_snap = snapping;
		if(m_snap)
			snapSlider();
	}

	void Slider::setRenderPercentage(bool percentage)
	{
		m_percentage = percentage;
	}

	void Slider::setSliderController(SliderController* controller)
	{
		controller->m_position.x = m_sliderController->m_position.x;
		GUI::remove(m_sliderController);
		delete m_sliderController;
		m_sliderController = controller;
		GUI::add(controller);
	}

	void Slider::setValue(float value)
	{
		Math::clamp(&value, m_startValue, m_endValue);
		m_sliderController->m_position.x = getPosFromValue(value);
	}

	float Slider::getValue() const
	{ 
		return Math::roundClose((m_sliderController->m_position.x / (m_size.x-1))*(m_endValue - m_startValue) + m_startValue, m_stepSize);
	}

	float Slider::getPosFromValue(float value) const
	{
		return (value - m_startValue) / (m_endValue - m_startValue)*(m_size.x-1);
	}

	float Slider::getPosFromValue() const 
	{ 
		return getPosFromValue(getValue()); 
	}
}