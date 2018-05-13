#pragma once

#include <Greet.h>
#include "Content.h"

class Label : public Content
{
private:
	bool hasMaxWidth;
public:
	float maxWidth;
	std::string str;
	Greet::Font* font;
	Greet::Vec4 color;

public:
	Label(const std::string& str, Greet::Font* font, const Greet::Vec4& color);
	void Render(Greet::GUIRenderer* renderer, const Greet::Vec2& position) const override;
	
	float GetWidth() const override;
	float GetHeight() const override;
};