#pragma once

#include "guilayer.h"

namespace greet { namespace graphics {

	using namespace event;
	using namespace math;
	using namespace utils;

	GUILayer::GUILayer(Renderer2D* renderer, Shader* shader)
		: Layer<GUI>(renderer,shader, mat3::orthographic(0,Window::getWidth(),0,Window::getHeight()))
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

	bool GUILayer::onPressed(const event::KeyPressedEvent& e)
	{
		
		return false;
	}

	bool GUILayer::onReleased(const event::KeyReleasedEvent& e)
	{
		return false;
	}

	bool GUILayer::onTyped(const event::KeyTypedEvent& e)
	{
		return false;
	}

	bool GUILayer::onPressed(const event::MousePressedEvent& e)
	{

		bool pressed = false;
		math::vec2 relativePos;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			relativePos = (e.getPosition() - m_renderables[i]->m_position) - math::vec2(m_renderables[i]->m_margin.left, m_renderables[i]->m_margin.top);
			pressed |= m_renderables[i]->onPressed(e, relativePos);
		}
		return pressed;
	}

	bool GUILayer::onReleased(const event::MouseReleasedEvent& e)
	{
		bool released = false;
		math::vec2 relativePos;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			relativePos = (e.getPosition() - m_renderables[i]->m_position) - math::vec2(m_renderables[i]->m_margin.left, m_renderables[i]->m_margin.top);
			released |= m_renderables[i]->onReleased(e, relativePos);
		}
		return released;
	}

	bool GUILayer::onMoved(const event::MouseMovedEvent& e)
	{
		bool moved = false;
		math::vec2 relativePos;
		for (uint i = 0;i < m_renderables.size();i++)
		{
			relativePos = (e.getPosition() - m_renderables[i]->m_position) - math::vec2(m_renderables[i]->m_margin.left, m_renderables[i]->m_margin.top);
			moved |= m_renderables[i]->onMoved(e,relativePos);
		}
		return moved;
	}

	bool GUILayer::onScroll(const event::MouseScrollEvent& e)
	{
		return false;
	}

	void GUILayer::windowResize(int width, int height)
	{
		setProjectionMatrix(mat3::orthographic(0, width, 0, height));
	}

}}