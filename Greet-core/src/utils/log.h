#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <map>

#include <Windows.h>
#include <greet_types.h>
#include <math\maths.h>

#define GREET_LOG_LEVEL_FATAL 0
#define GREET_LOG_LEVEL_ERROR 1
#define GREET_LOG_LEVEL_WARN  2
#define GREET_LOG_LEVEL_INFO  3

namespace std
{
	template <typename T>
	string to_string(const T& t)
	{
		return std::string("[Unsupported type: ") + typeid(T).name()+"]";
	}
}

namespace greet {
	namespace internal {

		static char to_string_buffer[1024 * 10];

		template <class T>
		struct has_iterator
		{
			template<class U> static char(&test(typename U::iterator const*))[1];
			template<class U> static char(&test(...))[2];
			static const bool value = (sizeof(test<T>(0)) == 1);
		};

		template <typename T>
		static char* to_string(T& t)
		{
			return to_string_internal<T>(t, std::integral_constant<bool, has_iterator<T>::value>());
		}

		template <>
		static char* to_string<const char>(const char & t)
		{
			return strcpy(to_string_buffer,&t);
		}

		template <>
		static char* to_string<const char*>(const char* & t)
		{
			return strcpy(to_string_buffer, t);
		}

		template <>
		static char* to_string<const unsigned const char*>(const unsigned const char* & t)
		{
			return strcpy(to_string_buffer, reinterpret_cast<const char*>(t));
		}

		template <>
		static char* to_string<const std::string>(const std::string & t)
		{
			return strcpy(to_string_buffer, t.c_str());
		}

		template <>
		static char* to_string<const bool>(const bool & t)
		{
			return t ? "true" : "false";
		}
		 
		template <>
		static char* to_string<math::vec2>(math::vec2 & t)
		{
			std::string res = "vec2(" + std::to_string(t.x) + "," + std::to_string(t.y) + ")";
			return strcpy(to_string_buffer, res.c_str());
		}

		template <>
		static char* to_string<const math::vec2>(const math::vec2 & t)
		{
			std::string res = "vec2(" + std::to_string(t.x) + "," + std::to_string(t.y) + ")";
			return strcpy(to_string_buffer, res.c_str());
		}

		template <>
		static char* to_string<math::vec3>(math::vec3 & t)
		{
			std::string res = "vec3(" + std::to_string(t.x) + "," + std::to_string(t.y) + "," + std::to_string(t.z) + ")";
			return strcpy(to_string_buffer, res.c_str());
		}

		template <>
		static char* to_string<const math::vec3>(const math::vec3 & t)
		{
			std::string res = "vec3(" + std::to_string(t.x) + "," + std::to_string(t.y) + "," + std::to_string(t.z) + ")";
			return strcpy(to_string_buffer, res.c_str());
		}
		
		template <>
		static char* to_string<math::vec4>(math::vec4 & t)
		{
			std::string res = "vec4(" + std::to_string(t.x) + "," + std::to_string(t.y) + "," + std::to_string(t.z) + "," + std::to_string(t.w) + ")";
			return strcpy(to_string_buffer, res.c_str());
		}

		template <>
		static char* to_string<const math::vec4>(const math::vec4 & t)
		{
			std::string res = "vec4(" + std::to_string(t.x) + "," + std::to_string(t.y) + "," + std::to_string(t.z) + "," + std::to_string(t.w) + ")";
			return strcpy(to_string_buffer, res.c_str());
		}

		template <>
		static char* to_string<math::mat3>(math::mat3 & t)
		{
			std::string res = "mat3=\n";
			for (int i = 0; i < 3; i ++)
			{
				res += "[";
				res += internal::to_string(t.elements[i]);
				res += " | ";
				res += internal::to_string(t.elements[i + 3]);
				res += " | ";
				res += internal::to_string(t.elements[i + 6]);
				res += "]\n";
			}
			return strcpy(to_string_buffer, res.c_str());
		}

		template <>
		static char* to_string<const math::mat3>(const math::mat3 & t)
		{
			std::string res = "mat3=\n";
			for (int i = 0; i < 3; i++)
			{
				res += "[";
				res += internal::to_string(t.elements[i]);
				res += " | ";
				res += internal::to_string(t.elements[i + 3]);
				res += " | ";
				res += internal::to_string(t.elements[i + 6]);
				res += "]\n";
			}
			return strcpy(to_string_buffer,res.c_str());
		}

		template <typename T>
		static std::string format_iterators(T& begin, T& end)
		{
			std::string result;
			bool first = true;
			while (begin != end)
			{
				if (!first)
					result += ", ";
				result += to_string(*begin);
				first = false;
				begin++;
			}
			return result;
		}

		template <typename T>
		static char* to_string_internal(const T& v, const std::true_type& ignored)
		{
			sprintf(to_string_buffer, "Container of size: %d, contents: %s", v.size(), format_iterators(v.begin(), v.end()).c_str());
			return to_string_buffer;
		}

		template <typename T>
		static char* to_string_internal(const T& t, const std::false_type& ignored)
		{
			auto x = std::to_string(t);
			return strcpy(to_string_buffer, x.c_str());
		}

		template<typename X, typename Y>
		static char* to_string(const std::pair<typename X, typename Y>& v)
		{
			sprintf(to_string_buffer, "(Key: %s, Value: %s)", internal::to_string(v.first), internal::to_string(v.second));
			return to_string_buffer;
		}

		template<>
		static char* to_string_internal<const char*>(const char* const& v, const std::false_type& ignored)
		{
			return strcpy(to_string_buffer, v);
		}

		template <typename First>
		static void add_to_buffer(char* buffer, int& position, First&& first)
		{
			const char* formatted = internal::to_string<First>(first);
			uint length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
		}

		template <typename First, typename... Args>
		static void add_to_buffer(char* buffer,int& position, First&& first, Args&&... args)
		{
			const char* formatted = internal::to_string<First>(first);
			uint length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
			if (sizeof...(Args))
			{
				add_to_buffer(buffer, position, std::forward<Args>(args)...);
			}
		}

		template <typename... Args>
		static void log_message(Args... args)
		{
			char buffer[1024 * 10];
			int position = 0;
			add_to_buffer(buffer, position, std::forward<Args>(args)...);
			
			buffer[position++] = '\n';

			buffer[position] = '\0';

			std::cout << buffer;
		}
	}
}

#ifndef GREET_LOG_LEVEL
	#define GREET_LOG_LEVEL GREET_LOG_LEVEL_INFO
#endif

#ifdef _DEBUG
	#define GREET_DEBUG(hint, ...) greet::internal::log_message("[GREET][DBG][",hint,"]: ", __VA_ARGS__)
#else
	#define GREET_DEBUG(...)
#endif

#if GREET_LOG_LEVEL >= GREET_LOG_LEVEL_FATAL
	#define GREET_FATAL(hint, ...) greet::internal::log_message("[GREET][FTL][",hint,"]: ", __VA_ARGS__)
#else
	#define GREET_FATAL(...)
#endif

#if GREET_LOG_LEVEL >= GREET_LOG_LEVEL_ERROR
	#define GREET_ERROR(hint, ...) greet::internal::log_message("[GREET][ERR][",hint,"]: ", __VA_ARGS__)
#else
	#define GREET_ERROR(...)
#endif

#if GREET_LOG_LEVEL >= GREET_LOG_LEVEL_WARN
	#define GREET_WARN(hint, ...) greet::internal::log_message("[GREET][WRN][",hint,"]: ", __VA_ARGS__)
#else
	#define GREET_WARN(...)
#endif

#if GREET_LOG_LEVEL >= GREET_LOG_LEVEL_INFO
	#define GREET_INFO(hint, ...) greet::internal::log_message("[GREET][INF][",hint,"]: ", __VA_ARGS__)
#else
	#define GREET_INFO(...)
#endif

#define GREET_ASSERT(x,hint, ...) \
	do { \
	if (!(x)) \
			{ \
		GREET_FATAL(hint, ""); \
		GREET_FATAL(hint, "*************************"); \
		GREET_FATAL(hint, "    ASSERTION FAILED!    "); \
		GREET_FATAL(hint, "*************************"); \
		GREET_FATAL(hint, "Condition: ", #x); \
		GREET_FATAL(hint, "Comment: "__VA_ARGS__); \
		GREET_FATAL(hint, __FILE__,":", __LINE__); \
		*(int*)NULL = 1024; \
			} \
		} while(0)