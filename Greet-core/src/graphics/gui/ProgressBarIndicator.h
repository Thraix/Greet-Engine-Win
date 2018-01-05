#pragma once

#include <graphics/gui/GUI.h>

namespace Greet
{
	class ProgressBarIndicator
	{
	public:
		virtual void Render(BatchRenderer2D* renderer, const Vec2& size, float percentage, bool vertical) const = 0;
	};
}