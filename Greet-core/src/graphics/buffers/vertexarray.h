#pragma once

#include <internal/Greetgl.h>
#include "buffer.h"
#include <vector>
#include <internal/Greet_types.h>

namespace Greet {

	class VertexArray
	{
	private:
		GLuint m_arrayID;
		std::vector<Buffer*> m_buffers;
	public:
		VertexArray();
		~VertexArray();
		void addBuffer(Buffer* buffer,GLuint index);
		void enable() const;
		void disable() const;
	};

}
