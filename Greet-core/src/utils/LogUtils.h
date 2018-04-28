#pragma once


#include <internal/GreetTypes.h>
#include <logging/Log.h>

namespace Greet { namespace LogUtils {


	inline uint Hex10ToDec16(const char c)
	{
		if (c >= '0' && c <= '9')
			return (uint)(c - '0');
		else if (c >= 'a' && c <= 'f')
			return (uint)(c - 'a');
		Log::Warning("Utils::Hex10ToDec16 couldn't recognize the hex character \'", c, "\'");
		return 0;

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

	inline char Dec16ToHex10(int dec)
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

	inline std::string DecToHex(uint dec, uint values = 1)
	{
		std::string s = "";
		bool trailing = true;
		for (uint i = 8; i >= 1; i--)
		{
			char hex = Dec16ToHex10(((dec >> (i * 4 - 4)) & 0xf));
			if (hex != '0' || i <= values || !trailing)
			{
				s += hex;
				if (hex != '0')
					trailing = false;
			}
		}
		return s;
	}

	inline uint HexToDec(std::string hex)
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
				result += Hex10ToDec16(hex[i]) << ((size - i) * 4 - 4);
			}
			return result;
		}
	}

}}