#include "Label.h"

using namespace Greet;

Label::Label(const std::string& str, Font* font, const Vec4& color)
	: str(str), font(font), color(color)
{
	hasMaxWidth = false;
}

void Label::Render(Greet::GUIRenderer* renderer, const Vec2& position) const
{
	//renderer->SubmitRect(position, GetSize(), Vec4(1, 1, 1, 1), true);
	renderer->SubmitString(str, position+Vec2(0, font->GetAscender()), font, color, true);
}


float Label::GetWidth() const
{
	float width = font->GetWidthOfText(str);
	return hasMaxWidth ? Math::Min(width, maxWidth) : width;
}

float Label::GetHeight() const
{
	return font->GetSize();
}

bool Label::OnPressed(const MousePressedEvent& event, const Vec2& translatedPos)
{
	// This component cannot get focus, maybe later if we want to be able to select the text?
	return false;
}