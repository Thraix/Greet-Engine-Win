#pragma once

#include "GUILayer.h"

namespace Greet {

	GUILayer::GUILayer(GUIRenderer* renderer, Shader* shader)
		: m_renderer(renderer), m_shader(shader), m_projectionMatrix(Mat3::Orthographic(0, Window::GetWidth(), 0, Window::GetHeight()))
	{
		Window::AddResizeCallback(this);
		EventDispatcher::AddKeyListener(DISPATCHER_GUI, *this);
		EventDispatcher::AddMouseListener(DISPATCHER_GUI, *this);

		// Initialize shader.
		GLint texIDs[32];
		for (int i = 0; i < 32; i++)
		{
			texIDs[i] = i;
		}
		m_shader->Enable();
		m_shader->SetUniformMat3("pr_matrix", m_projectionMatrix);
		m_shader->SetUniform1iv("textures", 32, texIDs);
		m_shader->Disable();
	}

	GUILayer::~GUILayer()
	{

		Window::RemoveResizeCallback(this);
		EventDispatcher::RemoveKeyListener(*this);
		EventDispatcher::RemoveMouseListener(*this);
	}

	void GUILayer::Add(GUI* renderable)
	{
		m_guis.push_back(renderable);
	}

	bool GUILayer::Update(float timeElapsed)
	{
		bool update = false;
		for (uint i = 0; i < m_guis.size(); i++)
			update |= m_guis[i]->Update(timeElapsed);
		return update;
	}

	void GUILayer::Render() const
	{
		m_shader->Enable();
		m_renderer->Begin();
		uint size = m_guis.size();
		for (uint i = 0; i < size; i++)
		{
			m_guis[i]->Begin(m_renderer);
			m_guis[i]->Submit(m_renderer);
			m_guis[i]->End(m_renderer);
		}
		m_renderer->End();
		m_renderer->Draw();
		m_shader->Disable();
	}

	void GUILayer::SetProjectionMatrix(Mat3 projectionMatrix)
	{
		m_projectionMatrix = projectionMatrix;
		m_shader->Enable();
		m_shader->SetUniformMat3("pr_matrix", m_projectionMatrix);
		m_shader->Disable();
	}

	void GUILayer::OnPressed(const KeyPressedEvent& e)
	{
		if(m_focusedGUI!=NULL)
			m_focusedGUI->OnPressed(e);
	}

	void GUILayer::OnReleased(const KeyReleasedEvent& e)
	{
		if (m_focusedGUI != NULL)
			m_focusedGUI->OnReleased(e);
	}

	void GUILayer::OnTyped(const KeyTypedEvent& e)
	{
		if (m_focusedGUI != NULL)
			m_focusedGUI->OnTyped(e);
	}

	bool GUILayer::OnPressed(const MousePressedEvent& e)
	{
		//if (m_focusedGUI != NULL && m_focusedGUI->onPressed(e, e.getPosition() - m_focusedGUI->m_position))
		{
		//	return true;
		}
		for (uint i = 0;i < m_guis.size();i++)
		{
			//if (m_focusedGUI == gui)
			//	continue;
			GUI* focusedGUI = m_guis[i]->OnPressed(e, e.GetPosition() - m_guis[i]->m_position);
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

	void GUILayer::OnReleased(const MouseReleasedEvent& e)
	{
		for (uint i = 0;i < m_guis.size();i++)
		{
			m_guis[i]->OnReleased(e, e.GetPosition() - m_guis[i]->m_position);
		}
	}

	void GUILayer::OnMoved(const MouseMovedEvent& e)
	{
		bool moved = false;
		for (uint i = 0;i < m_guis.size();i++)
		{
			m_guis[i]->OnMoved(e, e.GetPosition() - m_guis[i]->m_position);
		}
	}

	void GUILayer::OnScroll(const MouseScrollEvent& e)
	{
	}

	void GUILayer::WindowResize(int width, int height)
	{
		SetProjectionMatrix(Mat3::Orthographic(0, width, 0, height));
	}

}