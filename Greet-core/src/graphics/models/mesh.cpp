#include "mesh.h"

namespace greet { namespace model {

	Mesh::Mesh(const float* vertices, const float* normals, const float* texCoords, const uint* colors, uint vertexCount, const uint* indices, uint indexCount)
	{

		init(vertices, normals, texCoords, colors, vertexCount, indices, indexCount);
	}

	Mesh::Mesh(const float* vertices, const float* normals, const uint* colors, uint vertexCount, const uint* indices, uint indexCount)
	{
		float* texCoords = new float[vertexCount * 2];
		memset(texCoords, 1.0f, vertexCount * 2 * sizeof(float));
		init(vertices, normals, texCoords, colors, vertexCount, indices, indexCount);
	}

	Mesh::Mesh(const float* vertices, const float* normals, const float* texCoords, uint color, uint vertexCount, const uint* indices, uint indexCount)
	{
		uint* colors = new uint[vertexCount];
		memset(colors, color, vertexCount*sizeof(uint));
		init(vertices, normals, texCoords, colors, vertexCount, indices, indexCount);
	}

	Mesh::Mesh(const float* vertices, const float* normals, uint color, uint vertexCount, const uint* indices, uint indexCount)
	{
		float* texCoords = new float[vertexCount * 2];
		memset(texCoords, 0.0f, vertexCount * 2 * sizeof(float));
		uint* colors = new uint[vertexCount];
		memset(colors, color, vertexCount*sizeof(uint));
		init(vertices, normals, texCoords, colors, vertexCount, indices, indexCount);
	}

	void Mesh::init(const float* vertices, const float* normals, const float* texCoords, const uint* colors, uint vertexCount, const uint* indices, uint indexCount)
	{
		m_vertexCount = vertexCount;
		m_indexCount = indexCount;
		
		// VAO
		glGenVertexArrays(1, &m_vaoId);
		glBindVertexArray(m_vaoId);

		// IBO
		glGenBuffers(1, &m_iboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint), indices, GL_STATIC_DRAW);

		// Attributes
		addAttribute(3, vertices); // vertices
		addAttribute(2, texCoords); // texCoords
		addAttribute(4, colors); // colors
		addAttribute(3, normals); // normals

		// Unbind
		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		for (uint vbo : m_vbos)
		{
			glDeleteBuffers(1,&vbo);
		}
		m_vbos.clear();
		glDeleteBuffers(1,&m_iboId);
		glDeleteVertexArrays(1,&m_vaoId);
	}

	void Mesh::render() const
	{
		glDrawElements(GL_TRIANGLES,m_indexCount * sizeof(uint), GL_UNSIGNED_INT,0);
	}

	void Mesh::bind() const
	{
		glBindVertexArray(m_vaoId);
		enableAttributes();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
	}

	void Mesh::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		disableAttributes();
		glBindVertexArray(0);
	}

	void Mesh::enableAttributes() const
	{
		for (int i = 0;i < m_attributesCount;i++)
		{
			glEnableVertexAttribArray(i);
		}	
	}

	void Mesh::disableAttributes() const
	{
		for (int i = m_attributesCount-1;i >= 0;i--)
		{
			glDisableVertexAttribArray(i);
		}
	}

	void Mesh::addAttribute(uint attributeSize, const float* data)
	{
		uint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		m_vbos.push_back(vbo); // Needed to delete vbo when deleting mesh
		glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(float) * attributeSize, data, GL_STATIC_DRAW);
		glVertexAttribPointer(m_attributesCount++, attributeSize, GL_FLOAT, false, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Mesh::addAttribute(uint attributeSize, const uint* data)
	{
		uint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		m_vbos.push_back(vbo); // Needed to delete vbo when deleting mesh
		glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(byte) * attributeSize, data, GL_STATIC_DRAW);
		glVertexAttribPointer(m_attributesCount++, attributeSize, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}}