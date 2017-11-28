#include "BatchIndexBuffer.h"

namespace Greet {
	BatchIndexBuffer::BatchIndexBuffer(GLushort *data, GLsizei amount)
		: m_count(0)
	{
		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, amount * sizeof(GLshort), data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	BatchIndexBuffer::BatchIndexBuffer(GLuint* data, GLsizei amount)
		: m_count(0)
	{
		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, amount * sizeof(GLuint), data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
	BatchIndexBuffer::~BatchIndexBuffer()
	{
		glDeleteBuffers(1,&m_bufferID);
	}

	void BatchIndexBuffer::Enable() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
	}

	void BatchIndexBuffer::Disable() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}