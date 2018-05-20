#pragma once

#include <Greet.h>
#include <vector>
#include "Content.h"
#include "GUIMouseListener.h"

class Container
{
protected:

	static byte RESIZING_LEFT;
	static byte RESIZING_RIGHT;
	static byte RESIZING_TOP;
	static byte RESIZING_BOTTOM;
	static uint RESIZING_MARGIN;

	bool hasFocusedContent;

	bool m_resizing;
	byte m_resizableFlags;
	byte m_resizingFlags;
	Greet::Vec2 m_minSize;

	bool m_stayInsideWindow;

	Greet::Vec2 m_clickPos;
	Greet::Vec2 m_posOrigin;
	Greet::Vec2 m_sizeOrigin;

	GUIMouseListener* m_mouseListener;

public:
	float marginLeft;
	float marginRight;
	float marginTop;
	float marginBottom;

	bool visible;

	Greet::Vec2 pos;
	Greet::Vec2 size;
	Content* content;

public:
	Container();
	Container(const Greet::XMLObject& object);
	Container(const Greet::Vec2& pos, const Greet::Vec2& size, Content* content);
	virtual void PreRender(Greet::GUIRenderer* renderer) const;
	virtual void Render(Greet::GUIRenderer* renderer) const;
	virtual void PostRender(Greet::GUIRenderer* renderer) const;
	virtual void Update(float timeElapsed);

	// Check if the mouse is within the resize window and sets flags
	bool CheckResize(const Greet::Vec2& mousePos);

	// Resize the window the mouse position
	void Resize(const Greet::Vec2& mousePos);

	// Clamp the container inside window after resizing it.
	void ResizeScreenClamp();

	// Getters and setters
	virtual Greet::Vec2 GetContentPosition() const { return Greet::Vec2(marginLeft, marginTop); };
	virtual Greet::Vec2 GetContentSize() const { return size-GetContentPosition() - Greet::Vec2(marginRight, marginBottom); }
	void SetMargins(float left, float right, float top, float bottom);

	// Set listeners
	void SetGUIMouseListener(GUIMouseListener* listener);

	// Listeners
	virtual bool OnPressed(const Greet::MousePressedEvent& event);
	virtual void OnReleased(const Greet::MouseReleasedEvent& event);
	virtual void OnMoved(const Greet::MouseMovedEvent& event);
	virtual void OnPressed(const Greet::KeyPressedEvent& event);
	virtual void OnReleased(const Greet::KeyReleasedEvent& event);
	virtual void OnFocused();
	virtual void OnUnfocused();

};