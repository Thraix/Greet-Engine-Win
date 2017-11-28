#pragma once

#include <string.h>
#include "GUI.h"
#include "label.h"
#include <utils/ColorUtils.h>



namespace Greet {

	class Frame : public GUI
	{
	private:
		std::string m_title;
		Font* m_titleFont;
		uint m_titleColor;
		uint m_titleBackgroundColor;
		bool m_holdFrame;
		Vec2 m_holdPosition;

	public:
		Frame(const Vec2& position, const Vec2& size, const std::string& title);
		virtual void Render(Renderer2D* renderer) const override;
		bool OnMoved(const MouseMovedEvent& event, Vec2 relativeMousePos) override;
		GUI* OnPressed(const MousePressedEvent& event, Vec2 relativeMousePos) override;
		GUI* OnReleased(const MouseReleasedEvent& event, Vec2 relativeMousePos) override;
		bool IsInsideFrameHeader(const Vec2& mouse) const;
	};

}
