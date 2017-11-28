#pragma once

#include <event/KeyEvent.h>

#include <logging/Log.h>

namespace Greet {

	class KeyListener
	{
		friend class EventDispatcher;
	private:
		uint m_id;
		static uint m_currentId;
	public:
		KeyListener() : m_id(m_currentId++) {}
		// returns true if the event will stop following events from taking place, mostly used for GUI
		virtual bool OnPressed(const KeyPressedEvent& e) = 0;// { Log::info("KEYLISTENER", "here"); return false; };
		virtual bool OnReleased(const KeyReleasedEvent& e) = 0;// { return false; };
		virtual bool OnTyped(const KeyTypedEvent& e) = 0;// { return false; };
	};
}