#pragma once

#include <event/mouseevent.h>

namespace greet { namespace event {

	class MouseListener
	{
		friend class EventDispatcher;
	private:
		uint m_id;
		static uint m_currentId;
	public:
		MouseListener() : m_id(m_currentId++) {}
		// returns true if the event will stop following events from taking place, mostly used for GUI
		virtual bool onPressed(const MousePressedEvent& e) = 0;// { return false; };
		virtual bool onReleased(const MouseReleasedEvent& e) = 0;// { return false; };
		virtual bool onMoved(const MouseMovedEvent& e) = 0;// { return false; };
	};
}}