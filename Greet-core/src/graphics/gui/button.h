#pragma once

#include <graphics/gui/GUI.h>
#include <graphics/fonts/FontManager.h>
#include <drivers\RectDriver.h>
#include <graphics/layers/GUILayer.h>
#include <drivers/DriverDispatcher.h>

#define BUTTON_RESIZE_TIME 0.08f
#define BUTTON_RESIZE_SIZE 3.0f

namespace Greet {
		
	class Button : public GUI
	{

	private:
		Font* m_font;
		std::string m_text;
		bool m_buttonBigger;

	public:
		Button(const vec2& position, const vec2 size, const std::string& text);
		void render(Renderer2D* renderer) const override;

		void onMouseEnter();
		void onMouseExit();
		bool onMoved(const MouseMovedEvent& event, vec2 relativeMousePos) override;
		GUI* onPressed(const MousePressedEvent& event, vec2 relativeMousePos) override;
		GUI* onReleased(const MouseReleasedEvent& event, vec2 relativeMousePos) override;
	};
}