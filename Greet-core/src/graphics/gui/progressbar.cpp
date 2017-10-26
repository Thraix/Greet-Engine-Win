#include "progressbar.h"


namespace Greet {
	
	ProgressBar::ProgressBar(const vec2& position, const vec2& size, float* progress, float min, float max)
		: GUI(position, size), m_progressref(*progress), m_progress(*progress), m_min(min), m_max(max), 
		m_progressColor(ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 9))),
		m_labelColor(ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 3))), m_progressFont(FontManager::get("anonymous",size.y-6))
	{
		m_renderBackground = true;
		m_backgroundColor = ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 15));
	}

	ProgressBar::ProgressBar(const vec2& position, const vec2& size, float progress, float min, float max)
		: GUI(position, size), m_progressref(m_progress), m_progress(progress), m_min(min), m_max(max),
		m_progressColor(ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 9))), 
		m_labelColor(ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 3))), m_progressFont(FontManager::get("anonymous", size.y - 6))
	{
		m_renderBackground = true;
		m_backgroundColor = ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 15));
	}

	void ProgressBar::render(Renderer2D* renderer) const
	{
		GUI::render(renderer);

		renderer->fillRect(vec2(0,0),vec2(m_size.x*getProgressPercentage(), m_size.y),m_progressColor,GUI::m_mask);\
		float yPos = m_size.y / 2.0f + m_progressFont->getSize()*0.25f;
		std::string value = StringUtils::toString((uint)(getProgressPercentage() * 100)) + "%";
		renderer->submitString(value, vec2((m_size.x - m_progressFont->getWidthOfText(value)) / 2.0f, yPos), m_progressFont, m_labelColor);
	}

	void ProgressBar::setProgress(float progress)
	{
		m_progress = progress;
		m_progressref = m_progress;
	}

	void ProgressBar::setProgress(float* progress)
	{
		m_progress = *progress;
		m_progressref = *progress;
	}


}