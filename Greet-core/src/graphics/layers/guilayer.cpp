#pragma once

#include "GUILayer.h"

namespace Greet {

	GUILayer::GUILayer(BatchRenderer2D* renderer, Shader* shader)
		: Layer(renderer,shader, Mat3::Orthographic(0,Window::GetWidth(),0,Window::GetHeight()))
	{
		Window::AddResizeCallback(this);
		EventDispatcher::AddKeyListener(DISPATCHER_GUI, *this);
		EventDispatcher::AddMouseListener(DISPATCHER_GUI, *this);
	}

	GUILayer::~GUILayer()
	{

		Window::RemoveResizeCallback(this);
		EventDispatcher::RemoveKeyListener(*this);
		EventDispatcher::RemoveMouseListener(*this);
	}

	void GUILayer::Add(Renderable* renderable)
	{
		Log::Error("GUILayer doesn't accept Renderables only GUIs.");
	}

	void GUILayer::Add(GUI* renderable)
	{
		Layer::Add(renderable);
	}

	bool GUILayer::OnPressed(const KeyPressedEvent& e)
	{
		if(m_focusedGUI!=NULL)
			return m_focusedGUI->OnPressed(e);
		return false;
	}

	bool GUILayer::OnReleased(const KeyReleasedEvent& e)
	{
		if (m_focusedGUI != NULL)
			return m_focusedGUI->OnReleased(e);
		return false;
	}

	bool GUILayer::OnTyped(const KeyTypedEvent& e)
	{
		if (m_focusedGUI != NULL)
			return m_focusedGUI->OnTyped(e);
		return false;
	}

	bool GUILayer::OnPressed(const MousePressedEvent& e)
	{
		//if (m_focusedGUI != NULL && m_focusedGUI->onPressed(e, e.getPosition() - m_focusedGUI->m_position))
		{
		//	return true;
		}
		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = GetGUI(i);
			//if (m_focusedGUI == gui)
			//	continue;
			GUI* focusedGUI = gui->OnPressed(e, e.GetPosition() - gui->m_position);
			if (focusedGUI != NULL)
			{
				if (m_focusedGUI != focusedGUI)
				{
					focusedGUI->SetFocused(true);
					if(m_focusedGUI != NULL)
						m_focusedGUI->SetFocused(false);
				}
				m_focusedGUI = focusedGUI;
				return true;
			}
		}
		if (m_focusedGUI != NULL)
			m_focusedGUI->SetFocused(false);
		m_focusedGUI = NULL;
		return false;
	}

	bool GUILayer::OnReleased(const MouseReleasedEvent& e)
	{
		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = GetGUI(i);
			gui->OnReleased(e, e.GetPosition() - gui->m_position);
		}
		return false;
	}

	bool GUILayer::OnMoved(const MouseMovedEvent& e)
	{
		bool moved = false;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = GetGUI(i);
			moved |= gui->OnMoved(e, e.GetPosition() - gui->m_position);
		}
		return moved;
	}

	bool GUILayer::OnScroll(const MouseScrollEvent& e)
	{
		return false;
	}

	void GUILayer::WindowResize(int width, int height)
	{
		SetProjectionMatrix(Mat3::Orthographic(0, width, 0, height));
	}

}