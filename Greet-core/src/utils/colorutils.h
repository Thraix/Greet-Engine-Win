#pragma once

#include <internal/greet_types.h>
#include <math/maths.h>
#include <logging\logger.h>

#define COLOR_UTILS_MODIFIER 0.1f

namespace greet { namespace utils { namespace ColorUtils {



	inline math::vec3 HSVtoRGB(float h, float s, float v)
	{
		float c = v * s;
		float h6f = h*6.0f;
		uint h6 = (uint)h6f;

		float f = h6f - h6;

		float p = v * (1 - s);
		float q = v * (1 - s * f);
		float t = v * (1 - s * (1 - f));

		switch (h6)
		{
		case 0:
			return math::vec3(v, t, p);
		case 1:
			return math::vec3(q, v, p);
		case 2:
			return math::vec3(p, v, t);
		case 3:
			return math::vec3(p, q, v);
		case 4:
			return math::vec3(t, p, v);
		case 5:
			return math::vec3(v, p, q);
		default:
			return math::vec3(c, c, c);
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
		float p = powf(1.0f-COLOR_UTILS_MODIFIER, level);
		return HSVtoRGB(hue,p,p);
	}
}}}