#include "EventDispatcher.h"

namespace Greet {

	std::map<uint, std::vector<MouseListener*>, std::greater<uint>> EventDispatcher::m_mouseListeners;
	std::map<uint, std::vector<KeyListener*>, std::greater<uint>> EventDispatcher::m_keyListeners;

	typedef std::map<uint, std::vector<MouseListener*>, std::greater<int>>::iterator it_mouseMap;
	typedef std::vector<MouseListener*>::iterator it_mouseListener;

	typedef std::map<uint, std::vector<KeyListener*>, std::greater<int>>::iterator it_keyMap;
	typedef std::vector<KeyListener*>::iterator it_keyListener;

	void EventDispatcher::addMouseListener(uint priority, MouseListener& listener)
	{
		for (it_mouseMap it = m_mouseListeners.begin();it != m_mouseListeners.end(); it++)
		{
			if (it->first == priority)
			{
				it->second.push_back(&listener);
			}
		}
		std::vector<MouseListener*> listeners;
		listeners.push_back(&listener);
		m_mouseListeners.insert(std::pair<uint, std::vector<MouseListener*>>(priority,listeners));
	}

	void EventDispatcher::addKeyListener(uint priority, KeyListener& listener)
	{
		for (it_keyMap it = m_keyListeners.begin();it != m_keyListeners.end(); it++)
		{
			if (it->first == priority)
			{
				it->second.push_back(&listener);
				return;
			}
		}
		std::vector<KeyListener*> listeners;
		listeners.push_back(&listener);
		m_keyListeners.insert(std::pair<uint, std::vector<KeyListener*>>(priority, listeners));
	}

	void EventDispatcher::removeMouseListener(MouseListener& listener)
	{
		for (it_mouseMap it = m_mouseListeners.begin();it != m_mouseListeners.end(); it++)
		{
			std::vector<MouseListener*> listeners = it->second;
			for (it_mouseListener it2 = listeners.begin(); it2 != listeners.end(); it2++)
			{
				if ((*it2)->m_id == listener.m_id)
				{
					listeners.erase(it2);
					return;
				}
			}
		}
		Log::warning("Could not remove listener, doesn't exist.");
	}

	void EventDispatcher::removeKeyListener(KeyListener& listener)
	{
		for (it_keyMap it = m_keyListeners.begin();it != m_keyListeners.end(); it++)
		{
			std::vector<KeyListener*> listeners = it->second;
			for (it_keyListener it2 = listeners.begin(); it2 != listeners.end(); it2++)
			{
				if ((*it2)->m_id == listener.m_id)
				{
					listeners.erase(it2);
					return;
				}
			}
		}
		Log::warning("Could not remove listener, doesn't exist.");
	}

	void EventDispatcher::onMousePressed(const MousePressedEvent& e)
	{
		for (it_mouseMap it = m_mouseListeners.begin();it != m_mouseListeners.end(); it++)
		{
			std::vector<MouseListener*> listeners = it->second;
			for (it_mouseListener it2 = listeners.begin(); it2 != listeners.end(); it2++)
			{
				if ((*it2)->onPressed(e))
					return;
			}
		}
	}

	void EventDispatcher::onMouseReleased(const MouseReleasedEvent& e)
	{
		bool done = false;
		for (it_mouseMap it = m_mouseListeners.begin();it != m_mouseListeners.end(); it++)
		{
			std::vector<MouseListener*> listeners = it->second;
			for (it_mouseListener it2 = listeners.begin(); it2 != listeners.end(); it2++)
			{
				if ((*it2)->onReleased(e))
					return;
			}
		}
	}

	void EventDispatcher::onMouseMoved(const MouseMovedEvent& e)
	{
		for (it_mouseMap it = m_mouseListeners.begin();it != m_mouseListeners.end(); it++)
		{
			std::vector<MouseListener*> listeners = it->second;
			for (it_mouseListener it2 = listeners.begin(); it2 != listeners.end(); it2++)
			{
				if ((*it2)->onMoved(e))
				return;
			}
		}
	}

	void EventDispatcher::onMouseScrolled(const MouseScrollEvent& e)
	{
		for (it_mouseMap it = m_mouseListeners.begin();it != m_mouseListeners.end(); it++)
		{
			std::vector<MouseListener*> listeners = it->second;
			for (it_mouseListener it2 = listeners.begin(); it2 != listeners.end(); it2++)
			{
				if ((*it2)->onScroll(e))
					return;
			}
		}
	}

	void EventDispatcher::onKeyPressed(const KeyPressedEvent& e)
	{
		for (it_keyMap it = m_keyListeners.begin();it != m_keyListeners.end(); it++)
		{
			std::vector<KeyListener*> listeners = it->second;
			for (it_keyListener it2 = listeners.begin(); it2 != listeners.end(); it2++)
			{
				if ((*it2)->onPressed(e))
				{
					return;
				}
			}
		}
	}

	void EventDispatcher::onKeyReleased(const KeyReleasedEvent& e)
	{
		for (it_keyMap it = m_keyListeners.begin();it != m_keyListeners.end(); it++)
		{
			std::vector<KeyListener*> listeners = it->second;
			for (it_keyListener it2 = listeners.begin(); it2 != listeners.end(); it2++)
			{
				if ((*it2)->onReleased(e))
					return;
			}
		}
	}

	void EventDispatcher::onKeyTyped(const KeyTypedEvent& e)
	{
		for (it_keyMap it = m_keyListeners.begin();it != m_keyListeners.end(); it++)
		{
			std::vector<KeyListener*> listeners = it->second;
			for (it_keyListener it2 = listeners.begin(); it2 != listeners.end(); it2++)
			{
				if ((*it2)->onTyped(e))
					return;
			}
		}
	}
}