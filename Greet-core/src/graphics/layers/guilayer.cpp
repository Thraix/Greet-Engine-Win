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
		Log::error("Doesn't accept Renderables only GUIs.");
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

		bool pressed = false;
		vec2 relativePos;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = getGUI(i);
			relativePos = (e.getPosition() - gui->m_position) - vec2(gui->m_margin.left, gui->m_margin.top);
			pressed |= gui->onPressed(e, relativePos);
		}
		return pressed;
	}

	bool GUILayer::onReleased(const MouseReleasedEvent& e)
	{
		bool released = false;
		vec2 relativePos;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = getGUI(i);
			relativePos = (e.getPosition() - gui->m_position) - vec2(gui->m_margin.left, gui->m_margin.top);
			released |= gui->onReleased(e, relativePos);
		}
		return released;
	}

	bool GUILayer::onMoved(const MouseMovedEvent& e)
	{
		bool moved = false;
		vec2 relativePos;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			GUI* gui = getGUI(i);
			relativePos = (e.getPosition() - gui->m_position) - vec2(gui->m_margin.left, gui->m_margin.top);
			moved |= gui->onMoved(e,relativePos);
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