#include "VertexArray.h"

namespace Greet {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_arrayID);
	}

	VertexArray::~VertexArray()
	{
		for (uint i = 0; i < m_buffers.size(); i++)
			delete m_buffers[i];
		glDeleteVertexArrays(1, &m_arrayID);
	}

	void VertexArray::addBuffer(Buffer* buffer, GLuint index)
	{
		enable();
		buffer->enable();

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT,GL_FALSE, 0, 0);

		buffer->disable();
		disable();

		m_buffers.push_back(buffer);
	}

	void VertexArray::enable() const
	{
		glBindVertexArray(m_arrayID);
	}

	void VertexArray::disable() const
	{
		glBindVertexArray(0);
	}

}