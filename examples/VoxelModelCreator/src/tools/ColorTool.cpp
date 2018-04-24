#include "ColorTool.h"

#include "../Grid.h"

namespace vmc {
	using namespace Greet;
	bool ColorTool::OnRightClick() {
		if (m_grid->HasSelected())
		{
			Vec4 color = ColorUtils::ColorHexToVec4(m_grid->GetSelectedCube().color);
			Log::Info(color);
			m_grid->GetColorPicker()->SetColorAsRGB(color);
			return true;
		}
		return false;
	};

	bool ColorTool::OnLeftClick() {
		if (m_grid->HasSelected())
		{
			Log::Info(m_grid->GetSelectedCube().color);
			Vec4 color = ColorUtils::ColorHexToVec4(m_grid->GetSelectedCube().color);
			Log::Info(color);
			m_grid->GetColorPicker()->SetColorAsRGB(color);
			return true;
		}
		return false;
	};
}