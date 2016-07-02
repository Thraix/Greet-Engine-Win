#pragma once

#include <internal/greetgl.h>

namespace greet { namespace graphics {
	class Buffer
	{
	private:
		GLuint m_bufferID;
		GLuint m_componentCount;

	public:
		Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
		~Buffer();
		void enable() const;
		void disable() const;

		inline GLuint getComponentCount() const { return m_componentCount; }

	};
}}
