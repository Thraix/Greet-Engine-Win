#pragma once

#include <event/keyevent.h>

#include <logging/logger.h>
namespace greet { namespace event {

	class KeyListener
	{
		friend class EventDispatcher;
	private:
		uint m_id;
		static uint m_currentId;
	public:
		KeyListener() : m_id(m_currentId++) {}
		// returns true if the event will stop following events from taking place, mostly used for GUI
		virtual bool onPressed(const KeyPressedEvent& e) = 0;// { LOG_INFO("KEYLISTENER", "here"); return false; };
		virtual bool onReleased(const KeyReleasedEvent& e) = 0;// { return false; };
		virtual bool onTyped(const KeyTypedEvent& e) = 0;// { return false; };
	};
}}