#pragma once

#include <graphics/layers/layer.h>
#include <event/mouselistener.h>
#include <event/keylistener.h>
#include <graphics/window.h>
#include <utils/utils.h>
#include <graphics/gui/gui.h>

namespace greet { namespace graphics {

	class GUILayer : public Layer<GUI>, public event::KeyListener, public event::MouseListener, public listener::WindowResizeListener
	{
	public:
		GUILayer(Renderer2D* renderer, Shader* shader);
		virtual ~GUILayer();

		bool onPressed(const event::KeyPressedEvent& e) override;
		bool onReleased(const event::KeyReleasedEvent& e) override;
		bool onTyped(const event::KeyTypedEvent& e) override;
		bool onPressed(const event::MousePressedEvent& e) override;
		bool onReleased(const event::MouseReleasedEvent& e) override;
		bool onMoved(const event::MouseMovedEvent& e) override;
		bool onScroll(const event::MouseScrollEvent& e) override;
		void windowResize(int width, int height) override;
	};

}}