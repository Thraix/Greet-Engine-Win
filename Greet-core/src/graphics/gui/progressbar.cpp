#include "progressbar.h"


namespace Greet {
	
	ProgressBar::ProgressBar(const Vec2& position, const Vec2& size, float* progress, float min, float max, ProgressBarIndicator* indicator, bool vertical)
		: GUI(position, size), m_progressref(*progress), m_progress(*progress), m_min(min), m_max(max), m_indicator(indicator), m_vertical(vertical),
		m_progressColor(ColorUtils::Vec3ToColorHex(ColorUtils::GetMaterialColor(120 / 360.0f, 9))),
		m_labelColor(ColorUtils::Vec3ToColorHex(ColorUtils::GetMaterialColor(120 / 360.0f, 3))), m_progressFont(FontManager::Get("anonymous",size.y-6))
	{
		m_renderBackground = true;
		m_backgroundColor = ColorUtils::Vec3ToColorHex(ColorUtils::GetMaterialColor(120 / 360.0f, 15));
	}

	ProgressBar::ProgressBar(const Vec2& position, const Vec2& size, float progress, float min, float max, ProgressBarIndicator* indicator, bool vertical)
		: GUI(position, size), m_progressref(m_progress), m_progress(progress), m_min(min), m_max(max), m_indicator(indicator), m_vertical(vertical),
		m_progressColor(ColorUtils::Vec3ToColorHex(ColorUtils::GetMaterialColor(120 / 360.0f, 9))), 
		m_labelColor(ColorUtils::Vec3ToColorHex(ColorUtils::GetMaterialColor(120 / 360.0f, 3))), m_progressFont(FontManager::Get("anonymous", size.y - 6))
	{
		m_renderBackground = true;
		m_backgroundColor = ColorUtils::Vec3ToColorHex(ColorUtils::GetMaterialColor(120 / 360.0f, 15));
	}

	void ProgressBar::Render(BatchRenderer2D* renderer) const
	{
		GUI::Render(renderer);
		m_indicator->Render(renderer,m_size,GetProgressPercentage(), m_vertical);
		float yPos = m_size.y / 2.0f + m_progressFont->GetSize()*0.25f;
		std::string value = StringUtils::to_string((uint)(GetProgressPercentage() * 100)) + "%";
		Log::Error("Should draw String: ", __PRETTY_FUNCTION__);
		//renderer->SubmitString(value, Vec2((m_size.x - m_progressFont->GetWidthOfText(value)) / 2.0f, yPos), m_progressFont, m_labelColor);
	}

	void ProgressBar::SetProgress(float progress)
	{
		m_progress = progress;
		m_progressref = m_progress;
	}

	void ProgressBar::SetProgress(float* progress)
	{
		m_progress = *progress;
		m_progressref = *progress;
	}


}