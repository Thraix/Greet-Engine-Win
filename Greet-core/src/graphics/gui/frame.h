#pragma once

#include <string.h>
#include "gui.h"
#include "label.h"
#include <utils/colorutils.h>



namespace Greet {

	class Frame : public GUI
	{
	private:
		std::string m_title;
		Font* m_titleFont;
		uint m_titleColor;
		uint m_titleBackgroundColor;
		bool m_holdFrame;

	public:
		Frame(const vec2& position, const vec2& size, const std::string& title);
		virtual void render(Renderer2D* renderer) const override;
		bool onMoved(const MouseMovedEvent& event, vec2 relativeMousePos) override;
		bool onPressed(const MousePressedEvent& event, vec2 relativeMousePos) override;
		bool onReleased(const MouseReleasedEvent& event, vec2 relativeMousePos) override;
		bool isInsideFrameHeader(const vec2& mouse) const;
	};

}
