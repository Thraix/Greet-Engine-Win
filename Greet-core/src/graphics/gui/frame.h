#pragma once

#include <string.h>
#include "gui.h"
#include "border.h"
#include "label.h"
#include <utils/colorutils.h>



namespace greet { namespace graphics {

	class Frame : public GUI
	{
	private:
		std::string m_title;
		Font* m_titleFont;
		uint m_titleColor;
		uint m_titleBackgroundColor;
		bool m_holdFrame;

	public:
		Frame(const math::vec2& position, const math::vec2& size, const std::string& title);
		virtual void render(Renderer2D* renderer) const override;
		bool onMoved(const event::MouseMovedEvent& event, math::vec2 relativeMousePos) override;
		bool onPressed(const event::MousePressedEvent& event, math::vec2 relativeMousePos) override;
		bool onReleased(const event::MouseReleasedEvent& event, math::vec2 relativeMousePos) override;
		bool isInsideFrameHeader(const math::vec2& mouse) const;
	};

}}
