#pragma once

#include<vector>

#include <Greet.h>

class Content
{
protected:
	std::vector<Content*> m_contents;
	Content* m_focused;
	bool isFocused;
	float leftMargin;
	float rightMargin;
	float topMargin;
	float bottomMargin;
	float xSpacing;
	float ySpacing;

public:
	Content();

	virtual void Render(Greet::GUIRenderer* renderer, const Greet::Vec2& position) const;
	virtual void Update(float timeElapsed);

	void AddContent(Content* content);
	Content* RemoveContent(uint index);
	Content* RemoveContent(Content* content);
	Content* GetContent(uint index);

	virtual bool OnPressed(const Greet::MousePressedEvent& event, const Greet::Vec2& translatedPos);
	virtual void OnReleased(const Greet::MouseReleasedEvent& event, const Greet::Vec2& translatedPos);
	virtual void OnMoved(const Greet::MouseMovedEvent& event, const Greet::Vec2& translatedPos);
	virtual void OnPressed(const Greet::KeyPressedEvent& event);
	virtual void OnReleased(const Greet::KeyReleasedEvent& event);

	virtual void OnFocused();
	virtual void OnUnfocused();
	Greet::Vec2 GetSize() const;
	virtual float GetWidth() const;
	virtual float GetHeight() const;

	void SetMargins(float left, float right, float top, float bottom);
};