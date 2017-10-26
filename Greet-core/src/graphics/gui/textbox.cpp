#include "textbox.h"


namespace Greet
{

	TextBox::TextBox(const vec2& position, const vec2& size)
		:GUI(position,size, LTRB(3,2,3,2)), m_font(FontManager::get("anonymous", size.y-6)), m_cursorColor(ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 9))),
		m_textColor(ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 3))),	m_blinkSpeed(0.5f)
	{
		m_renderBackground = true;
		m_backgroundColor = ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 15));
	}

	void TextBox::render(Renderer2D* renderer) const
	{
		GUI::render(renderer);
		renderer->submitString(m_text, vec2(m_margin.left, m_font->getSize()), m_font, m_textColor);
		const vec2& pos = getRealPosition();
		if (isFocused())
		{
			if (m_timer < m_blinkSpeed)
			{
				float width = m_font->getWidthOfText(m_text,0,m_cursorPosition);
				renderer->drawRect(vec2(m_margin.left+width-1, m_margin.top), vec2(1, m_size.y - (m_margin.top+ m_margin.bottom)), m_cursorColor);
			}
		}
	}

	bool TextBox::update(float timeElapsed)
	{
		m_timer += timeElapsed;
		if (m_timer >= m_blinkSpeed*2)
			m_timer = 0;
		return GUI::update(timeElapsed);
	}

	void TextBox::addCharacter(char c)
	{
		addCharacter(c, m_cursorPosition);
	}

	void TextBox::addCharacter(char c, uint index)
	{
		if (index > m_text.size())
			index = m_text.size();
		m_text.insert(m_text.begin()+index,c);
	}


	void TextBox::onFocused(bool focused)
	{
		m_timer = 0;
	}

	bool TextBox::onPressed(const KeyPressedEvent& e)
	{
		if (e.getButton() == GLFW_KEY_BACKSPACE)
		{
			if (m_cursorPosition > 0)
			{
				m_text.erase(m_text.begin() + --m_cursorPosition);
			}
		}
		else if (e.getButton() == GLFW_KEY_LEFT)
		{
			if (m_cursorPosition > 0)
				m_cursorPosition--;
		}
		else if (e.getButton() == GLFW_KEY_RIGHT)
		{
			if (m_cursorPosition < m_text.size())
				m_cursorPosition++;
		}
		else if (e.getButton() == GLFW_KEY_END)
		{
			m_cursorPosition = m_text.size();
		}
		else if (e.getButton() == GLFW_KEY_HOME)
		{
			m_cursorPosition = 0;
		}
		else if (e.getButton() == GLFW_KEY_DELETE)
		{
			if (m_cursorPosition < m_text.size())
			{
				m_text.erase(m_text.begin() + m_cursorPosition);
			}
		}
		m_timer = 0;
		return false;
	}

	bool TextBox::onReleased(const KeyReleasedEvent& e)
	{
		return false;
	}

	bool TextBox::onTyped(const KeyTypedEvent& e)
	{
		addCharacter(e.getCharCode());
		if (m_font->getWidthOfText(m_text) > m_size.x - m_margin.left - m_margin.right)
			m_text.erase(m_text.end() - 1);
		else
			m_cursorPosition++;
		m_timer = 0;
		return true;
	}

	GUI* TextBox::onPressed(const MousePressedEvent& e, vec2 relativeMousePos)
	{
		GUI* gui = GUI::onPressed(e, relativeMousePos);
		// Check if mouse is inside of the textbox
		if (gui != this)
			return gui;

		float x = relativeMousePos.x - m_margin.left;

		float* widths = m_font->getPartialWidths(m_text);

		int i = 1;
		while (x > widths[i] && i <=m_text.size())
		{
			Log::info(x, ": ", widths[i]);
			i++;
		}

		m_cursorPosition = i - 1;


		return this;
	}

}