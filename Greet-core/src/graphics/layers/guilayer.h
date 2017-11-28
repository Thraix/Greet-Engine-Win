#pragma once

#include <graphics/layers/Layer.h>
#include <event/MouseListener.h>
#include <event/KeyListener.h>
#include <graphics/Window.h>
#include <utils/Utils.h>
#include <graphics/gui/GUI.h>

namespace Greet {

	class GUILayer : public Layer, public KeyListener, public MouseListener, public WindowResizeListener
	{

	private:
		GUI* m_focusedGUI;
		GUI* GetGUI(uint i) { return (GUI*)m_renderables[i]; };
	public:
		GUILayer(Renderer2D* renderer, Shader* shader);
		virtual ~GUILayer();
		void Add(Renderable* renderable) override;
		void Add(GUI* renderable);
		bool OnPressed(const KeyPressedEvent& e) override;
		bool OnReleased(const KeyReleasedEvent& e) override;
		bool OnTyped(const KeyTypedEvent& e) override;
		bool OnPressed(const MousePressedEvent& e) override;
		bool OnReleased(const MouseReleasedEvent& e) override;
		bool OnMoved(const MouseMovedEvent& e) override;
		bool OnScroll(const MouseScrollEvent& e) override;
		void WindowResize(int width, int height) override;
	};

}