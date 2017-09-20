#include "mesh.h"

namespace greet { namespace model {

	Mesh::Mesh(const math::vec3* vertices, uint vertexCount, const uint* indices, uint indexCount)
	{
		init(vertices, vertexCount, indices, indexCount);
	}

	Mesh::Mesh(MeshData* data)
	{
		init(data->getVertices(),data->getVertexCount(),data->getIndices(),data->getIndexCount());
		for (uint i = 0;i < data->m_data.size();i++)
		{
			addAttribute(data->m_data[i]);
		}
	}

	void Mesh::init(const math::vec3* vertices, uint vertexCount, const uint* indices, uint indexCount)
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
		addAttribute(MESH_VERTICES_LOCATION, vertices); // vertices
		
		// Set default color to white
		glVertexAttrib4f(MESH_COLORS_LOCATION,1.0f,1.0f,1.0f,1.0f);

		// Unbind
		glBindVertexArray(0);
	}
	Mesh::~Mesh()
	{
		for (auto it = m_vbos.begin();it != m_vbos.end(); it++)
		{
			glDeleteBuffers(1,&it->second);
		}
		m_vbos.clear();
		glDeleteBuffers(1,&m_iboId);
		glDeleteVertexArrays(1,&m_vaoId);
	}

	void Mesh::render() const
	{
		glDrawElements(GL_TRIANGLES, m_indexCount * sizeof(uint), GL_UNSIGNED_INT,0);
	}

	void Mesh::bind() const
	{
		if (m_culling)
		{	
			glEnable(GL_CULL_FACE);
			glFrontFace(m_clockwise ? GL_CW : GL_CCW);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}

		glBindVertexArray(m_vaoId);
		enableAttributes();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
	}

	void Mesh::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		disableAttributes();
		glBindVertexArray(0);
		glDisable(GL_CULL_FACE);
	}

	void Mesh::enableAttributes() const
	{
		for (auto it = m_vbos.begin();it != m_vbos.end(); it++)
		{
			glEnableVertexAttribArray(it->first);
		}	
	}

	void Mesh::disableAttributes() const
	{
		for (auto it = m_vbos.begin();it != m_vbos.end(); it++)
		{
			glDisableVertexAttribArray(it->first);
		}
	}

	void Mesh::addAttribute(uint location, const math::vec3* data)
	{

		if (m_vbos.find(location) != m_vbos.end())
		{
			utils::ErrorHandle::setErrorCode(GREET_ERROR_MESH_LOCATION);
			LOG_ERROR("Shader location already used in mesh:", location);
			return;
		}
		glBindVertexArray(m_vaoId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
		uint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		m_vbos.emplace(location, vbo); // Needed to delete vbo when deleting mesh
		glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(float) * 3, data, GL_STATIC_DRAW);
		glVertexAttribPointer(location, 3, GL_FLOAT, false, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Mesh::addAttribute(uint location, const math::vec2* data)
	{
		if (m_vbos.find(location) != m_vbos.end())
		{
			utils::ErrorHandle::setErrorCode(GREET_ERROR_MESH_LOCATION);
			LOG_ERROR("Shader location already used in mesh:", location);
			return;
		}
		glBindVertexArray(m_vaoId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
		uint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		m_vbos.emplace(location, vbo); // Needed to delete vbo when deleting mesh
		glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(float) * 2, data, GL_STATIC_DRAW);
		glVertexAttribPointer(location, 2, GL_FLOAT, false, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Mesh::addAttribute(uint location, uint attributeSize, const uint* data)
	{
		if (m_vbos.find(location) != m_vbos.end())
		{
			utils::ErrorHandle::setErrorCode(GREET_ERROR_MESH_LOCATION);
			LOG_ERROR("Shader location already used in mesh:",location);
			return;
		}
		glBindVertexArray(m_vaoId);
		uint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		m_vbos.emplace(location, vbo); // Needed to delete vbo when deleting mesh
		glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(byte) * attributeSize, data, GL_STATIC_DRAW);
		glVertexAttribPointer(location, attributeSize, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	void Mesh::addAttribute(AttributeData* data)
	{
		if (m_vbos.find(data->location) != m_vbos.end())
		{
			utils::ErrorHandle::setErrorCode(GREET_ERROR_MESH_LOCATION);
			LOG_ERROR("Shader location already used in mesh:",data->location);
			return;
		}
		glBindVertexArray(m_vaoId);
		uint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		m_vbos.emplace(data->location,vbo); // Needed to delete vbo when deleting mesh
		glBufferData(GL_ARRAY_BUFFER, m_vertexCount * data->memoryValueSize, data->data, GL_STATIC_DRAW);
		glVertexAttribPointer(data->location, data->vertexValueSize, data->glType, data->normalized, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
		glBindVertexArray(0);
	}

	void Mesh::setDefaultAttribute4f(uint location, const math::vec4& data)
	{
		glBindVertexArray(m_vaoId);
		glVertexAttrib4f(location,data.x,data.y,data.z,data.w);
		glBindVertexArray(0);	
	}

	void Mesh::setDefaultAttribute3f(uint location, const math::vec3& data)
	{
		glBindVertexArray(m_vaoId);
		glVertexAttrib3f(location,data.x,data.y,data.z);
		glBindVertexArray(0);
	}
}}