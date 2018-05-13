#pragma once

#include "Content.h"
#include "Label.h"

class Button : public Content
{
public:
	Label* label;
	Greet::Vec2 size;

public:
	Button(const Greet::Vec2& size, const std::string& text);
	Button(const Greet::Vec2& size, Content* content);
	virtual ~Button();
	void Render(Greet::GUIRenderer* renderer, const Greet::Vec2& position) const override;

	float GetWidth() const override;
	float GetHeight() const override;

	// Listeners
	bool IsFocusable() const override;
};