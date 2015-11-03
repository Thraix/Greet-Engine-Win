#pragma once

#include <greetgl.h>

namespace greet {namespace graphics {
	class BatchIndexBuffer
	{
	private:
		GLuint m_bufferID;
		GLsizei m_count;
	public:
		BatchIndexBuffer(GLushort* data, GLsizei amount);
		BatchIndexBuffer(GLuint* data, GLsizei amount);

		~BatchIndexBuffer();
		void enable();
		void disable();
		void addCount(GLuint count){ m_count += count; }
		void resetCount(){ m_count = 0; }
		inline GLsizei getCount() const { return m_count; }
	};
}}