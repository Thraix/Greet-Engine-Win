#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace greet { namespace utils{

	inline std::vector<std::string> split_string(const std::string &s, const std::string& delimiter) {
		size_t start = 0;
		size_t end = s.find_first_of(delimiter);

		std::vector<std::string> output;

		while (end <= std::string::npos)
		{
			output.emplace_back(s.substr(start, end - start));

			if (end == std::string::npos)
				break;

			start = end + 1;
			end = s.find_first_of(delimiter, start);
		}

		return output;
	}
	inline void replace_all(std::string& str, const std::string& from, const std::string& to)
	{
		if (from.empty())
			return;
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos)
		{
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
	}
	inline bool starts_with(const std::string& s, const std::string& prefix)
	{
		return s.compare(0, prefix.size(), prefix) == 0;
			
	}
}}