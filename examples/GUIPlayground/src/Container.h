#pragma once

#include <Greet.h>
#include <vector>
#include "Content.h"

class Container
{
private:

	static byte RESIZING_LEFT;
	static byte RESIZING_RIGHT;
	static byte RESIZING_TOP;
	static byte RESIZING_BOTTOM;

	Content* content;
	bool hasFocusedContent;

	bool m_resizable;
	bool m_resizing;
	byte m_resizingFlags;

	float leftMargin;
	float rightMargin;
	float topMargin;
	float bottomMargin;

public:
	bool visible;
	Greet::Vec2 pos;
	Greet::Vec2 size;
public:
	Container();
	void Render(Greet::GUIRenderer* renderer) const;
	void Update(float timeElapsed);

	bool OnPressed(const Greet::MousePressedEvent& event);
	void OnReleased(const Greet::MouseReleasedEvent& event);
	void OnMoved(const Greet::MouseMovedEvent& event);
	void OnPressed(const Greet::KeyPressedEvent& event);
	void OnReleased(const Greet::KeyReleasedEvent& event);

	void OnFocused();
	void OnUnfocused();

	// Check if the mouse is within the resize window and sets flags
	void CheckResize(const Greet::Vec2& mousePos);

	// Resize the window the the mouse position
	void Resize(const Greet::Vec2& mousePos);
};