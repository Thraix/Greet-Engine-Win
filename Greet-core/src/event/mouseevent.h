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
		MouseButtonEvent(float x, float y, uint button, Type type)
			: Event(type),m_position(x,y),m_button(button){}

		inline const float getX() const { return m_position.x; }
		inline const float getY() const { return m_position.y; }
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
		bool m_dragged;

	protected:
		MouseMovedEvent(float x, float y, bool dragged)
			:Event(MOUSE_MOVED),m_position(math::vec2(x,y)),m_dragged(dragged){}
	public:
		inline const float getX() const { return m_position.x; }
		inline const float getY() const { return m_position.y; }
		inline const math::vec2& getPosition() const { return m_position; }
		inline const bool isDragged() const { return m_dragged; }
	};
}}