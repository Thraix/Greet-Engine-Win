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
		GUI* getGUI(uint i) { return (GUI*)m_renderables[i]; };
	public:
		GUILayer(Renderer2D* renderer, Shader* shader);
		virtual ~GUILayer();
		void add(Renderable* renderable) override;
		void add(GUI* renderable);
		bool onPressed(const KeyPressedEvent& e) override;
		bool onReleased(const KeyReleasedEvent& e) override;
		bool onTyped(const KeyTypedEvent& e) override;
		bool onPressed(const MousePressedEvent& e) override;
		bool onReleased(const MouseReleasedEvent& e) override;
		bool onMoved(const MouseMovedEvent& e) override;
		bool onScroll(const MouseScrollEvent& e) override;
		void windowResize(int width, int height) override;
	};

}