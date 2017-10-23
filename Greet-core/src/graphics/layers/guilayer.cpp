#pragma once

#include "guilayer.h"

namespace Greet {

	GUILayer::GUILayer(Renderer2D* renderer, Shader* shader)
		: Layer(renderer,shader, mat3::orthographic(0,Window::getWidth(),0,Window::getHeight()))
	{
		Window::addResizeCallback(this);
		EventDispatcher::addKeyListener(DISPATCHER_GUI, *this);
		EventDispatcher::addMouseListener(DISPATCHER_GUI, *this);
	}

	GUILayer::~GUILayer()
	{

		Window::removeResizeCallback(this);
		EventDispatcher::removeKeyListener(*this);
		EventDispatcher::removeMouseListener(*this);
	}

	void GUILayer::add(Renderable* renderable)
	{
		Log::error("GUILayer doesn't accept Renderables only GUIs.");
	}

	void GUILayer::add(GUI* renderable)
	{
		Layer::add(renderable);
	}

	bool GUILayer::onPressed(const KeyPressedEvent& e)
	{
		
		return false;
	}

	bool GUILayer::onReleased(const KeyReleasedEvent& e)
	{
		return false;
	}

	bool GUILayer::onTyped(const KeyTypedEvent& e)
	{
		return false;
	}

	bool GUILayer::onPressed(const MousePressedEvent& e)
	{
		//if (m_focusedGUI != NULL && m_focusedGUI->onPressed(e, e.getPosition() - m_focusedGUI->m_position))
		{
		//	return true;
		}
		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = getGUI(i);
			//if (m_focusedGUI == gui)
			//	continue;
			GUI* focusedGUI = gui->onPressed(e, e.getPosition() - gui->m_position);
			if (focusedGUI != NULL)
			{
				if (m_focusedGUI != focusedGUI)
				{
					focusedGUI->setFocused(true);
					if(m_focusedGUI != NULL)
						m_focusedGUI->setFocused(false);
				}
				m_focusedGUI = focusedGUI;
				return true;
			}
		}
		m_focusedGUI = NULL;
		return false;
	}

	bool GUILayer::onReleased(const MouseReleasedEvent& e)
	{
		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = getGUI(i);
			gui->onReleased(e, e.getPosition() - gui->m_position);
		}
		return false;
	}

	bool GUILayer::onMoved(const MouseMovedEvent& e)
	{
		bool moved = false;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = getGUI(i);
			moved |= gui->onMoved(e, e.getPosition() - gui->m_position);
		}
		return moved;
	}

	bool GUILayer::onScroll(const MouseScrollEvent& e)
	{
		return false;
	}

	void GUILayer::windowResize(int width, int height)
	{
		setProjectionMatrix(mat3::orthographic(0, width, 0, height));
	}

}