#include "BatchRenderer2D.h"

namespace Greet { namespace test
{
	void BatchRenderer2D::Begin()
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
		GLCall(m_buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		m_iboSize = 0;
		m_lastIndex = 0;
	}

	void BatchRenderer2D::Flush()
	{
		for (uint i = 0;i < m_usedTextures;i++)
		{
			GLCall(glActiveTexture(GL_TEXTURE0+i));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_texSlots[i]));
		}

		GLCall(glBindVertexArray(m_vao));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_iboSize * sizeof(uint), m_indices, GL_DYNAMIC_DRAW));

		GLCall(glDrawElements(GL_TRIANGLES, m_iboSize, GL_UNSIGNED_INT, NULL));

		GLCall(glBindVertexArray(0));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	void BatchRenderer2D::End()
	{
		GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void BatchRenderer2D::Submit(const Renderable2D* renderable)
	{
		renderable->SetVertices(this, &m_buffer);
	}

	uint BatchRenderer2D::GetTextureSlot(uint texID)
	{
		if (texID == 0)
			return 0;
		uint ts = 0;
		bool found = false;
		uint size = m_usedTextures;
		for (int i = 0;i < size;i++)
		{
			if (m_texSlots[i] == texID)
			{
				return i + 1;
			}
		}

		if (size == RENDERER_MAX_TEXTURES)
		{
			m_usedTextures = 0;
			return 0;
		}
		m_usedTextures++;
		return size;
	}

	void BatchRenderer2D::AddIndicesPoly(uint vertices)
	{
		vertices -= 2;
		for (uint i = 0; i < vertices; i++)
		{
			m_indices[m_iboSize + 3 * i] = m_lastIndex;
			m_indices[m_iboSize + 3 * i + 1] = m_lastIndex + i + 1;
			m_indices[m_iboSize + 3 * i + 2] = m_lastIndex + i + 2;

		}
		m_lastIndex = m_indices[m_iboSize + 3 * (vertices - 1) + 2] + 1;
	}
}}