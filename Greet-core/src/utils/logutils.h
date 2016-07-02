#pragma once

#include <sstream>

namespace greet {namespace utils{
	template <typename T>
	inline std::string toString(T t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str().c_str();			
	}
}}