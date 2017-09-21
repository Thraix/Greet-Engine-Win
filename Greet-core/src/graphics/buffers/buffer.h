#pragma once

#include <internal/Greetgl.h>

namespace Greet {
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
}
