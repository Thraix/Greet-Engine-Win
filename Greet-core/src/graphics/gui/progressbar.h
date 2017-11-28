#pragma once

#include <graphics/gui/GUI.h>
#include <graphics/fonts/FontManager.h>

namespace Greet {

	class ProgressBar : public GUI
	{
		float m_progress;
		float& m_progressref;
		float m_min;
		float m_max;
		uint m_progressColor;
		uint m_labelColor;
		Font* m_progressFont;

	public:
		ProgressBar(const vec2& position, const vec2& size, float* progress, float min, float max);
		ProgressBar(const vec2& position, const vec2& size, float progress, float min, float max);

		void render(Renderer2D* renderer) const override;

		void setProgress(float* progress);
		void setProgress(float progress);
		float getProgress() const { return m_progressref; }
		float getProgressPercentage() const { return (m_progressref - m_min) / (m_max - m_min); }

		uint getLabelColor() const { return m_labelColor; }
		uint getProgressColor() const { return m_progressColor; }

		void setLabelColor(uint color) { m_labelColor = color; }
		void setProgressColor(uint color) { m_progressColor = color; }

	};
}