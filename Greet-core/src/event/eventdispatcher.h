#pragma once

#include <map>
#include <functional>
#include <vector>
#include <event/MouseEvent.h>
#include <event/MouseListener.h>
#include <event/KeyListener.h>
#include <utils/Utils.h>
#include <logging\Logger.h>

#define DISPATCHER_GUI BIT(24)

namespace Greet {
	class Window;
}

namespace Greet {
	class EventDispatcher
	{
	public:
		friend class Window;
		static void addMouseListener(uint priority, MouseListener& listener);
		static void addKeyListener(uint priority, KeyListener& listener);
		static void removeMouseListener(MouseListener& listener);
		static void removeKeyListener(KeyListener& listener);
	private:
		static std::map<uint, std::vector<MouseListener*>, std::greater<uint>> m_mouseListeners;
		static std::map<uint, std::vector<KeyListener*>, std::greater<uint>> m_keyListeners;

		static void onMousePressed(const MousePressedEvent& e);
		static void onMouseReleased(const MouseReleasedEvent& e);
		static void onMouseMoved(const MouseMovedEvent& e);
		static void onMouseScrolled(const MouseScrollEvent& e);

		static void onKeyPressed(const KeyPressedEvent& e);
		static void onKeyReleased(const KeyReleasedEvent& e);
		static void onKeyTyped(const KeyTypedEvent& e);
	};
}
