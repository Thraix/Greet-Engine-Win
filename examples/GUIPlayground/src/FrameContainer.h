#pragma once

#include "Container.h"
#include "Label.h"
#include <Greet.h>

class FrameContainer : public Container
{
protected:
	// True if this class created the header.
	bool m_shouldDeleteHeader;

	bool m_movable;
	bool m_moving;

	Content* header;

	float headerSpacing;
public:
	float headerSize;

public:
	FrameContainer(const Greet::Vec2& pos, const Greet::Vec2& size, Content* content, const std::string& title);
	FrameContainer(const Greet::Vec2& pos, const Greet::Vec2& size, Content* content, Content* header);
	virtual ~FrameContainer();

	void Render(Greet::GUIRenderer* renderer) const override;

	// Check if the mouse is within the move window
	bool CheckMove(const Greet::Vec2& mousePos);

	// Move the window to the mouse position
	void Move(const Greet::Vec2& mousePos);

	// Clamp the container inside window after moving it.
	void MoveScreenClamp();

	// Getters and setters
	Greet::Vec2 GetContentPosition() const override { return Greet::Vec2(leftMargin, topMargin + headerSize + headerSpacing); };

	// Listeners
	bool OnPressed(const Greet::MousePressedEvent& event) override;
	void OnReleased(const Greet::MouseReleasedEvent& event) override;
	void OnMoved(const Greet::MouseMovedEvent& event) override;
};