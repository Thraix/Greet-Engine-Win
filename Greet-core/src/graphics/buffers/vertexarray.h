#pragma once

#include <greetgl.h>
#include "buffer.h"
#include <vector>
#include <greet_types.h>

namespace greet { namespace graphics {

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

}}