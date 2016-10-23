#pragma once

#include <graphics/gui/gui.h>
#include <graphics/fonts/fontmanager.h>
#include <drivers\rectdriver.h>
#include <drivers/driveradapter.h>
#include <drivers/driverdispatcher.h>

#define BUTTON_RESIZE_TIME 0.08f
#define BUTTON_RESIZE_SIZE 3.0f

namespace greet { namespace graphics {
		
	class Button : public GUI
	{

	private:
		Font* m_font;
		std::string m_text;
		bool m_buttonBigger;

	public:
		Button(const math::vec2& position, const math::vec2 size, const std::string& text);
		void render(Renderer2D* renderer) const override;

		void onMouseEnter();
		void onMouseExit();
		bool onMoved(const event::MouseMovedEvent& event, math::vec2 relativeMousePos) override;
		bool onPressed(const event::MousePressedEvent& event, math::vec2 relativeMousePos) override;
		bool onReleased(const event::MouseReleasedEvent& event, math::vec2 relativeMousePos) override;
	};
}}