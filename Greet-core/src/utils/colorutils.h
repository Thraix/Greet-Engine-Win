#pragma once

#include <internal/greet_types.h>
#include <math/maths.h>
#include <logging\logger.h>

#define COLOR_UTILS_MODIFIER 0.1f

namespace greet { namespace utils { namespace ColorUtils {



	inline math::vec3 HSVtoRGB(float h, float s, float v)
	{
		float c = v * s;
		uint h6 = (uint)(h * 6) % 6;
		float x = c * (1 - fabs(h6 % 2 - 1));
		float m = v - c;
		switch (h6)
		{
		case 0:
			return math::vec3(c + m, x + m, m);
		case 1:
			return math::vec3(x + m, c + m, m);
		case 2:
			return math::vec3(m, c + m, x + m);
		case 3:
			return math::vec3(m, x + m, c + m);
		case 4:
			return math::vec3(x + m, m, c + m);
		case 5:
			return math::vec3(c + m, m, x + m);
		default:
			return math::vec3(m, m, m);
		}
	}

	inline math::vec3 HSVtoRGB(math::vec3 hsv)
	{
		return HSVtoRGB(hsv.x,hsv.y,hsv.z);
	}

	inline math::vec3 RGBtoHSV(float r, float g, float b)
	{
		float cmin = r < g ? (r < b ? r : b) : (g < b ? g : b);
		float cmax = r > g ? (r > b ? r : b) : (g > b ? g : b);

		float delta = cmax - cmin;
		float s = 0;
		if (cmax != 0)
			s = delta / cmax;
		if (delta == 0)
		{
			return math::vec3(0, s, cmax);
		}
		else if (cmax == r)
		{
			return math::vec3((g - b) / delta, s, cmax);
		}
		else if (cmax == g)
		{
			return math::vec3((b - r) / delta + 2, s, cmax);
		}
		else // if (cmax == b)
		{
			return math::vec3((r - g) / delta + 4, s, cmax);
		}
	}

	inline math::vec3 RGBtoHSV(uint colorHex)
	{
		return RGBtoHSV(((colorHex & 0xff0000) >> 16)/255.0f, ((colorHex & 0xff00) >> 8) / 255.0f, (colorHex & 0xff) / 255.0f);
	}

	inline math::vec3 RGBtoHSV(math::vec3 rgb)
	{
		return RGBtoHSV(rgb.x,rgb.y,rgb.z);
	}

	inline uint vec3ToColorHex(math::vec3 color)
	{
		return 0xff000000 | ((int)(color.x * 255) << 16) | ((int)(color.y * 255) << 8) | (int)(color.z * 255);
	}

	inline uint vec4ToColorHex(math::vec4 color)
	{
		return ((int)(color.w * 255) << 24) | ((int)(color.x * 255) << 16) | ((int)(color.y * 255) << 8) | (int)(color.z * 255);
	}

	inline math::vec3 getMaterialColor(float hue, int level)
	{
		float p = powf(1.0-COLOR_UTILS_MODIFIER, level);
		return HSVtoRGB(hue,p,p);
	}
}}}