#pragma once

#include "event.h"
#include <internal\greet_types.h>
#include <math\maths.h>

namespace greet { namespace event {

	class MouseButtonEvent : public Event
	{
	protected:
		math::vec2 m_position;
		uint m_button;
	protected:
		MouseButtonEvent(float x, float y, uint button, EventType type)
			: Event(type),m_position(x,y),m_button(button){}
	public:
		inline const float getX() const { return m_position.x; }
		inline const float getY() const { return m_position.y; }
		inline const void setX(float x) { m_position.x = x; }
		inline const void setY(float y) { m_position.y = y; }
		inline const math::vec2& getPosition() const { return m_position; }
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
		math::vec2 m_position;
		math::vec2 m_deltaPosition;
		bool m_dragged;

	public:
		MouseMovedEvent(float x, float y, float dx, float dy, bool dragged)
			:Event(MOUSE_MOVED),m_position(math::vec2(x,y)), m_deltaPosition(math::vec2(dx,dy)),m_dragged(dragged){}
	public:
		inline const float getX() const { return m_position.x; }
		inline const float getY() const { return m_position.y; }
		inline const void setX(float x) { m_position.x = x; }
		inline const void setY(float y) { m_position.y = y; }
		inline const math::vec2& getPosition() const { return m_position; }
		inline const math::vec2& getDeltaPosition() const { return m_deltaPosition; }
		inline const bool isDragged() const { return m_dragged; }
	};
}}