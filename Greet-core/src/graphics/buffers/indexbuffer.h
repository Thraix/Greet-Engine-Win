#pragma once

#include <greetgl.h>

namespace greet {namespace graphics {
	class IndexBuffer
	{
	private:
		GLuint m_bufferID;
		GLuint m_count;

	public:
		IndexBuffer(GLushort* data, GLsizei count);
		IndexBuffer(GLuint* data, GLsizei count);
		~IndexBuffer();
		void enable() const;
		void disable() const;

		inline GLuint getCount() const { return m_count; }

	};
}}