#pragma once

#include <internal/GreetTypes.h>
#include <math/Maths.h>
#include <logging/Logger.h>

#define COLOR_UTILS_MODIFIER 0.1f

namespace Greet { namespace ColorUtils {



	inline Vec3 HSVtoRGB(float h, float s, float v)
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
			return Vec3(v, t, p);
		case 1:
			return Vec3(q, v, p);
		case 2:
			return Vec3(p, v, t);
		case 3:
			return Vec3(p, q, v);
		case 4:
			return Vec3(t, p, v);
		case 5:
			return Vec3(v, p, q);
		default:
			return Vec3(c, c, c);
		}
	}

	inline Vec3 HSVtoRGB(Vec3 hsv)
	{
		return HSVtoRGB(hsv.x,hsv.y,hsv.z);
	}

	inline Vec3 RGBtoHSV(float r, float g, float b)
	{
		float cmin = r < g ? (r < b ? r : b) : (g < b ? g : b);
		float cmax = r > g ? (r > b ? r : b) : (g > b ? g : b);

		float delta = cmax - cmin;
		float s = 0;
		if (cmax != 0)
			s = delta / cmax;
		if (delta == 0)
		{
			return Vec3(0, s, cmax);
		}
		else if (cmax == r)
		{
			return Vec3((g - b) / delta, s, cmax);
		}
		else if (cmax == g)
		{
			return Vec3((b - r) / delta + 2, s, cmax);
		}
		else // if (cmax == b)
		{
			return Vec3((r - g) / delta + 4, s, cmax);
		}
	}

	inline Vec3 RGBtoHSV(uint colorHex)
	{
		return RGBtoHSV(((colorHex & 0xff0000) >> 16)/255.0f, ((colorHex & 0xff00) >> 8) / 255.0f, (colorHex & 0xff) / 255.0f);
	}

	inline Vec3 RGBtoHSV(Vec3 rgb)
	{
		return RGBtoHSV(rgb.x,rgb.y,rgb.z);
	}

	inline uint Vec3ToColorHex(Vec3 color)
	{
		return 0xff000000 | ((int)(color.x * 255) << 16) | ((int)(color.y * 255) << 8) | (int)(color.z * 255);
	}

	inline Vec4 ColorHexToVec4(uint color)
	{
		return Vec4((color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, (color >> 24) & 0xff) / 255.0f;
	}

	inline byte GetAlpha(uint color)
	{
		return color >> 24 & 0xff;
	}

	inline byte GetRed(uint color)
	{
		return color >> 16 & 0xff;
	}

	inline byte GetGreen(uint color)
	{
		return color >> 8 & 0xff;
	}

	inline byte GetBlue(uint color)
	{
		return color & 0xff;
	}

	inline Vec4 HexToVec4(uint color)
	{
		return Vec4(GetRed(color), GetGreen(color), GetBlue(color), GetAlpha(color)) / 255.0f;
	}

	inline uint Vec4ToColorHex(Vec4 color)
	{
		return ((int)(color.w * 255) << 24) | ((int)(color.x * 255) << 16) | ((int)(color.y * 255) << 8) | (int)(color.z * 255);
	}

	inline Vec3 GetMaterialColor(float hue, int level)
	{
		float p = powf(1.0f-COLOR_UTILS_MODIFIER, level);
		return HSVtoRGB(hue,p,p);
	}
}}