#pragma once

#include <graphics/gui/GUI.h>

namespace Greet
{
	class ProgressBarIndicator
	{
	public:
		virtual void Render(Renderer2D* renderer, const Vec2& size, float percentage, bool vertical) const = 0;
	};
}