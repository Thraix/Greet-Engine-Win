#pragma once

#include "GUIMouseListener.h"
#include "GUIUtils.h"

#include <vector>
#include <Greet.h>

class Content
{
protected:
	bool m_isFocusable;
	std::vector<Content*> m_contents;
	Content* m_focused;
	bool isFocused;
	float marginLeft;
	float marginRight;
	float marginTop;
	float marginBottom;
	Greet::XMLObject xmlObject;

	float ySpacing;

	Greet::Vec2 size;
	Content* parent;
	Greet::Vec4 backgroundColor;

public:
	Content();
	Content(const Greet::XMLObject& object, Content* parent);

	virtual void Render(Greet::GUIRenderer* renderer, const Greet::Vec2& position) const;
	virtual void Update(float timeElapsed);

	void AddContent(Content* content);
	Content* RemoveContent(uint index);
	Content* RemoveContent(Content* content);
	Content* GetContent(uint index);

	// Returns true if this component or a child that was pressed is focusable.
	bool MousePress(const Greet::MousePressedEvent& event, const Greet::Vec2& translatedPos, const GUIMouseListener& listener);
	void MouseRelease(const Greet::MouseReleasedEvent& event, const Greet::Vec2& translatedPos, const GUIMouseListener& listener);
	void MouseMove(const Greet::MouseMovedEvent& event, const Greet::Vec2& translatedPos);

	//virtual void OnMousePressed(const Greet::MousePressedEvent& event, const Greet::Vec2& translatedPos);
	//virtual void OnMouseReleased(const Greet::MouseReleasedEvent& event, const Greet::Vec2& translatedPos);
	//virtual void OnMouseClicked(const Greet::MouseReleasedEvent& event, const Greet::Vec2& translatedPos);
	//virtual void OnMouseMoved(const Greet::MouseMovedEvent& event, const Greet::Vec2& translatedPos);
	//virtual void OnMouseEntered();
	//virtual void OnMouseExited();
	virtual void OnKeyPressed(const Greet::KeyPressedEvent& event);
	virtual void OnKeyReleased(const Greet::KeyReleasedEvent& event);


	virtual void OnFocused();
	virtual void OnUnfocused();
	virtual bool IsFocusable() const { return m_isFocusable; };

	void SetSpacing(float spacing);
	float GetSpacing() const;
	bool IsMouseInside(const Greet::Vec2& mousePos) const;
	Greet::Vec2 GetSize() const;
	void SetSize(const Greet::Vec2& size);
	virtual float GetWidth() const;
	virtual float GetHeight() const;
	virtual float GetPotentialWidth() const;
	virtual float GetPotentialHeight() const;

	void SetMargins(float left, float right, float top, float bottom);
};