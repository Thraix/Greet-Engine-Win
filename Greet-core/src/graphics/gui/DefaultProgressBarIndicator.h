#pragma once

#include <graphics/gui/ProgressBarIndicator.h>

namespace Greet
{
	class DefaultProgressBarIndicator : public ProgressBarIndicator
	{
	private:
		uint m_color;
	public:
		DefaultProgressBarIndicator(uint color)
			: m_color(color)
		{
		
		}

		void Submit(GUIRenderer* renderer, const Vec2& size, float percentage, bool vertical) const override
		{
			if (vertical)
			{
				renderer->SubmitRect(Vec2(0, 0), Vec2(size.x, size.y*percentage), m_color);
			}
			else
			{
				renderer->SubmitRect(Vec2(0, 0), Vec2(size.x*percentage, size.y), m_color);
			}
		}
	};
}