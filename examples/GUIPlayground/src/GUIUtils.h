#pragma once

#include <graphics/Window.h>
#include <utils/StringUtils.h>

#include "Button.h"


namespace Greet
{
	class GUIUtils
	{
	public:

		static Container* GetContainer(const XMLObject& object)
		{
			if (object.GetName() == "Container")
			{
				return new Container(object);
			}
			else if (object.GetName() == "FrameContainer")
			{

			}

			return new Container();
		}


		static Content* GetContent(const XMLObject& object)
		{
			if (object.GetName() == "Button")
			{
				//return new Button(object);
			}
			Log::Warning("Could not read XML object ", object.GetName(), ".");
			return new Content(); // Return plain content to avoid crash.
		}

		static bool GetBoolean(const std::string& str)
		{
			if (str == "true")
				return true;
			return false;
		}

		static float CalcXSize(const std::string& size)
		{
			float sizeF = atof(size.c_str());
			if (StringUtils::ends_with(size, "%"))
			{
				return sizeF * Window::GetWidth() * 0.01f; // Convert 100 -> 1
			}
			else // if (StringUtils::ends_with(size, "px")) // if there is no ending it counts as pixels.
			{
				return sizeF;
			}
		}

		static float CalcYSize(const std::string& size)
		{
			float sizeF = atof(size.c_str());
			if (StringUtils::ends_with(size, "%"))
			{
				return sizeF * Window::GetHeight() * 0.01f; // Convert 100 -> 1
			}
			else // if (StringUtils::ends_with(size, "px")) // if there is no ending it counts as pixels.
			{
				return sizeF;
			}
		}
	};
}