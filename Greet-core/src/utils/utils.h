#pragma once

#include <ctime>
#include <internal/greet_types.h>

#define BIT(x) 1 << x

namespace greet {namespace utils{

	template<typename Base, typename T>
	inline bool instanceof(const T *ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}

	inline float roundDown(float numToRound, float multiple)
	{
		if (multiple == 0)
			return 0;
		return ((int)(numToRound / multiple))*multiple;
	}

	inline float roundUp(float numToRound, float multiple)
	{
		if (multiple == 0)
			return 0;
		float ans = ((int)(numToRound / multiple))*multiple;
		return ans < numToRound ? ans + multiple : ans;
	}

	inline float roundClose(float numToRound, float multiple)
	{
		if (multiple == 0)
			return 0;
		float down = ((int)(numToRound / multiple))*multiple;
		float up = down < numToRound ? down + multiple : down;
		return (numToRound - down) < (up - numToRound) ? down : up;
	}

	inline std::string getTime()
	{
		time_t currentTime;
		struct tm *localTime;
		time(&currentTime);
		localTime = localtime(&currentTime);
		int hour = localTime->tm_hour;
		int min = localTime->tm_min;
		std::string res = "";
		if (hour < 10)
			res += "0";
		res += toString(hour)+":";
		if (min < 10)
			res += "0";
		res += toString(min);
		return res;
	}

	inline byte* getBytesFromString(const std::string& s)
	{
		std::cout << s << std::endl;
		byte* bytes = new byte[s.length()];
		for(uint i = 0;i<s.length();i++)
		{
			bytes[i] = s[i];
		}
		return bytes;
	}

	inline uint HSVtoARGB(float hue, float sat, float val)
	{
		int h = (int)(hue * 6.0f);
		float f = hue * 6.0f - h;
		float p = val* (1.0f - sat);
		float q = val* (1.0f - f*sat);
		float t = val* (1.0f - (1.0f - f)*sat);
		float r = 0;
		float g = 0;
		float b = 0;
		switch (h) {
		case 0:
			r = val;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = val;
			b = p;
			break;
		case 2:
			r = p;
			g = val;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = val;
			break;
		case 4:
			r = t;
			g = p;
			b = val;
			break;
		case 5:
			r = val;
			g = p;
			b = q;
			break;
		}
		return 0xff000000 + ((int)(r * 255.0f) << 16) + ((int)(g * 255.0f) << 8) + (int)(b * 255.0f);
	}

	inline unsigned long long powi(uint b, uint n)
	{
		unsigned long long r = 1;
		for (uint i = 0; i < n; i++)
		{
			r *= b;
		}
		return r;
	}

	inline uint hex16_to_dec(const char c)
	{
		switch (c)
		{
		case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
			return (uint)(c - '0');
		case 'a':
			return 10;
		case 'b':
			return 11;
		case 'c':
			return 12;
		case 'd':
			return 13;
		case 'e':
			return 14;
		case 'f':
			return 15;
		default:
			return 0;
		}
	}

	inline char dec16_to_hex(int dec)
	{
		switch (dec)
		{
		case 0:
			return '0';
		case 1:
			return '1';
		case 2:
			return '2';
		case 3:
			return '3';
		case 4:
			return '4';
		case 5:
			return '5';
		case 6:
			return '6';
		case 7:
			return '7';
		case 8:
			return '8';
		case 9:
			return '9';
		case 10:
			return 'a';
		case 11:
			return 'b';
		case 12:
			return 'c';
		case 13:
			return 'd';
		case 14:
			return 'e';
		case 15:
			return 'f';
		default:
			return '0';
		}
	}

	inline std::string dec_to_hex(uint dec, uint values = 1)
	{
		std::string s = "";
		bool begin = true;
		for (uint i = 8; i >= 1; i--)
		{
			char hex = dec16_to_hex(((dec >> (i * 4 - 4)) & 0xf));
			if (hex != '0' || !begin || values >= i)
				s += hex;
			else if (hex != '0')
				begin = false;
		}
		return s;
	}

	inline uint hex_to_dec(std::string hex)
	{
		if (hex.length() > 8)
		{
			return 0;
		}
		else
		{
			uint result = 0;

			int size = hex.length();
			for (int i = 0; i < size; i++)
			{
				result += hex16_to_dec(hex[i]) << ((size - i) * 4 - 4);
			}
			return result;
		}
	}
}}
