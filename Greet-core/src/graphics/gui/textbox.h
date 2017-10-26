#pragma once

#include <graphics/gui/gui.h>
#include <graphics/fonts/font.h>
#include <graphics/fonts/fontmanager.h>
#include <graphics/window.h>

namespace Greet
{
	class TextBox : public GUI
	{
	protected:
		// Blinks the cursor
		float m_timer;
		// Blinking speed of the cursor
		float m_blinkSpeed;
		// Color of the cursor
		uint m_cursorColor;
		// Color of the text
		uint m_textColor;
		// Font of the text
		Font* m_font;
		// Text that is entered
		std::string m_text;
		// Cursor position
		uint m_cursorPosition;
	public:

		TextBox(const vec2& position, const vec2& size);

		bool update(float timeElapsed) override;
		void render(Renderer2D* renderer) const override;

		void addCharacter(char c);
		void addCharacter(char c, uint index);

		void setText(const std::string& text) { m_text = text;m_cursorPosition = text.size()-1; }
		void setTextColor(uint color) { m_textColor = color; }
		void setCursorColor(uint color) { m_cursorColor = color; }
		void setBlinkingSpeed(float time) { m_blinkSpeed = time; }
		const std::string& getText() const { return m_text; }
		uint getTextColor() const { return m_textColor; }
		uint getCursorColor() const { return m_cursorColor; }
		float getBlinkingSpeed() const { return m_blinkSpeed; }

		bool onPressed(const KeyPressedEvent& e) override;
		bool onReleased(const KeyReleasedEvent& e) override;
		bool onTyped(const KeyTypedEvent& e) override;

		virtual GUI* onPressed(const MousePressedEvent& event, vec2 relativeMousePos) override;

		void onFocused(bool focused);

	};
}