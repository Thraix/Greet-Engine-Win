#pragma once

#include<vector>

#include <Greet.h>

class Content
{
private:
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
	void Render(Greet::GUIRenderer* renderer, const Greet::Vec2& position) const;
	void Update(float timeElapsed);

	bool OnPressed(const Greet::MousePressedEvent& event, const Greet::Vec2& translatedPos);
	void OnReleased(const Greet::MouseReleasedEvent& event, const Greet::Vec2& translatedPos);
	void OnMoved(const Greet::MouseMovedEvent& event, const Greet::Vec2& translatedPos);
	void OnPressed(const Greet::KeyPressedEvent& event);
	void OnReleased(const Greet::KeyReleasedEvent& event);

	void OnFocused();
	void OnUnfocused();
	Greet::Vec2 GetSize() const;
	float GetWidth() const;
	float GetHeight() const;
};