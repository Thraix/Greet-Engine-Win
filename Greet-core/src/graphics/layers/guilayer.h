#pragma once

#include <graphics/layers/layer.h>
#include <event/mouselistener.h>
#include <event/keylistener.h>
#include <graphics/window.h>
#include <utils/utils.h>
#include <graphics/gui/gui.h>

namespace Greet {

	class GUILayer : public Layer, public KeyListener, public MouseListener, public WindowResizeListener
	{

	private:
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