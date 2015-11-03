#include "button.h"

namespace greet { namespace graphics {

	Button::Button(math::vec2 pos, math::vec2 size)
		: GUI(pos,size)
	{
		m_textView = new TextView(size / 2.0f, s_defaultFont,size.y - 4.0f,"",m_fgColor);
		init();
	}

	Button::Button(math::vec2 pos, math::vec2 size, std::string text)
		: GUI(pos, size)
	{
		m_textView = new TextView(size / 2.0f, s_defaultFont, size.y - 4.0f, text, m_fgColor);
		init();
	}

	void Button::init()
	{
		m_textView->centerText();
		m_textView->setBackgroundColor(0xff00ff00);
		push(m_textView);
	}

	void Button::inputComponents(float timeElapsed) 
	{
		GUI::inputComponents(timeElapsed);

		if (Window::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			if (m_mouseInside)
			{
				if(m_press!=NULL)
					m_press(this);
				m_pressedInside = true;
			}
		}
		if (Window::isMouseButtonReleased(GLFW_MOUSE_BUTTON_LEFT))
		{
			if (m_pressedInside&&m_mouseInside)
			{
				if (m_release != NULL)
					m_release(this);
			}
			m_pressedInside = false;
		}
	}

	void Button::submitComponents(Renderer2D* renderer) const
	{
		
	}

	void Button::setForegroundColor(uint color)
	{
		GUI::setForegroundColor(color);
		m_textView->setForegroundColor(color);
	}

	void Button::setPressListener(BUTTON_PRESS press)
	{
		m_press = press;
	}

	void Button::setReleaseListener(BUTTON_RELEASE release)
	{
		m_release = release;
	}
}}