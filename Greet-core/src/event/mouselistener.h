#pragma once

#include <event/MouseEvent.h>

namespace Greet {

	class MouseListener
	{
		friend class EventDispatcher;
	private:
		uint m_id;
		static uint m_currentId;
	public:
		MouseListener() : m_id(m_currentId++) {}
		// returns true if the event will stop following events from taking place, mostly used for GUI
		virtual bool OnPressed(const MousePressedEvent& e) = 0;// { return false; };
		virtual bool OnReleased(const MouseReleasedEvent& e) = 0;// { return false; };
		virtual bool OnMoved(const MouseMovedEvent& e) = 0;// { return false; };
		virtual bool OnScroll(const MouseScrollEvent& e) = 0;
	};
}