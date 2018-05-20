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

		static Vec4 GetColor(const std::string& str)
		{
			if (str[0] == '#')
			{
				std::string color = str.substr(1);
				if (color.length() != 6 && color.length() != 8)
				{
					Log::Error("Invalid length for color: ", str);
					return Vec4(1,0,1,1); // Invalid color pink since its very visible
				}
				if (color.length() == 6)
					color = "FF" + color; // Add alpha to color
				uint colori = LogUtils::HexToDec(color);
				return ColorUtils::ColorHexToVec4(colori);
			}
			Log::Error("Invalid starting character for  color: ", str);
			return Vec4(1, 0, 1, 1); // Invalid color pink since its very visible
		}

		static float CalcSize(const std::string& size, float parentSize)
		{
			float sizeF = atof(size.c_str());
			if (StringUtils::ends_with(size, "%"))
			{
				return sizeF * parentSize * 0.01f; // Convert 100 -> 1
			}
			else // if (StringUtils::ends_with(size, "px")) // if there is no ending it counts as pixels.
			{
				return sizeF;
			}
		}
	};
}