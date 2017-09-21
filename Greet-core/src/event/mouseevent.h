#pragma once

#include "event.h"
#include <internal\Greet_types.h>
#include <math\maths.h>

namespace Greet {

	class MouseButtonEvent : public Event
	{
	protected:
		vec2 m_position;
		uint m_button;
	protected:
		MouseButtonEvent(float x, float y, uint button, EventType type)
			: Event(type),m_position(x,y),m_button(button){}
	public:
		inline const float getX() const { return m_position.x; }
		inline const float getY() const { return m_position.y; }
		inline const void setX(float x) { m_position.x = x; }
		inline const void setY(float y) { m_position.y = y; }
		inline const vec2& getPosition() const { return m_position; }
		inline const uint getButton() const { return m_button; }
	};

	class MousePressedEvent : public MouseButtonEvent
	{
	public:
		MousePressedEvent(float x, float y, uint button)
			: MouseButtonEvent(x, y, button, MOUSE_PRESSED) {}
	};

	class MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(float x, float y, uint button)
			: MouseButtonEvent(x, y, button, MOUSE_RELEASED) {}
	};

	class MouseMovedEvent : public Event
	{
	private:
		vec2 m_position;
		vec2 m_deltaPosition;
		bool m_dragged;

	public:
		MouseMovedEvent(float x, float y, float dx, float dy, bool dragged)
			:Event(MOUSE_MOVED),m_position(vec2(x,y)), m_deltaPosition(vec2(dx,dy)),m_dragged(dragged){}
	public:
		inline const float getX() const { return m_position.x; }
		inline const float getY() const { return m_position.y; }
		inline const float getDX() const { return m_deltaPosition.x; }
		inline const float getDY() const { return m_deltaPosition.y; }
		inline const void setX(float x) { m_position.x = x; }
		inline const void setY(float y) { m_position.y = y; }
		inline const vec2& getPosition() const { return m_position; }
		inline const vec2& getDeltaPosition() const { return m_deltaPosition; }
		inline const bool isDragged() const { return m_dragged; }
	};

	class MouseScrollEvent : public Event
	{
	private:
		int m_scroll;
		int m_scrollDirection;
	public:
		MouseScrollEvent(int scroll)
			//															Calculate the direction, keeping in mind div by 0
			:Event(MOUSE_SCROLLED), m_scroll(scroll), m_scrollDirection(scroll / (scroll < 0 ? -scroll : (scroll == 0 ? 1 : scroll))) {}

		inline const int getScroll() const { return m_scroll; };
		inline const int getDirection() const { return m_scrollDirection; }

	};
}