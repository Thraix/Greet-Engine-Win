#pragma once

#include <Greet.h>

class Content
{

public:
	void Render(Greet::GUIRenderer* renderer) const;
	void Update(float timeElapsed);

	bool OnPressed(const Greet::MousePressedEvent& event, const Vec2& translatedPos);
	void OnReleased(const Greet::MouseReleasedEvent& event, const Vec2& translatedPos);
	void OnMoved(const Greet::MouseMovedEvent& event, const Vec2& translatedPos);
	bool OnPressed(const Greet::KeyPressedEvent& event);
	bool OnReleased(const Greet::KeyReleasedEvent& event);
};