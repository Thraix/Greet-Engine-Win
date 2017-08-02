#pragma once

#include <internal/greet_types.h>
#include <logging\logger.h>

namespace greet { namespace utils {

	class JSON
	{
		friend class JSONArray;
		friend class JSONOBject;
	private:
		static char* m_indent;
		static uint ostream_indent;

	public:
		static const char* get_indent()
		{
			if (m_indent == NULL)
			{
				ostream_indent = 0;
				m_indent = new char[1024];
				memset(m_indent,'\0',1024);
			}
			return m_indent;
		}

		static void push_indent()
		{
			if (m_indent == NULL)
			{
				ostream_indent = 0;
				m_indent = new char[1024];
				memset(m_indent, '\0', 1024);
			}
			if (ostream_indent != 1024)
			{
				m_indent[ostream_indent++] = '\t';
			}
			else
			{
				LOG_ERROR("JSON", "Maximum output indention reached.");
			}
		}

		static void pop_indent()
		{
			ASSERT(ostream_indent != 0, "JSON INDENT ASSERT");
			m_indent[--ostream_indent] = '\0';
		}
	};
}}