#include "BatchRenderer2D.h"

#include <graphics/renderables/Renderable.h>

namespace Greet {

	BatchRenderer2D::BatchRenderer2D(const std::vector<AttributePointer>& attributes)
	{
		GLCall(glGenVertexArrays(1, &m_vao));
		GLCall(glGenBuffers(1, &m_vbo));

		GLCall(glBindVertexArray(m_vao));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));

		m_vertexSize = attributes[0].stride;

		// vertexSize * shapes * corners in shape
		m_bufferSize = m_vertexSize * 36000 * 4;
		// m_iboSize = shades * indicesPerShape
		m_iboSize = 36000 * 6;

		// Initialize the vertex buffer array
		GLCall(glBufferData(GL_ARRAY_BUFFER, m_bufferSize, nullptr, GL_DYNAMIC_DRAW));

		for (auto it = attributes.begin();it != attributes.end();it++)
		{
			it->SetPointer();
		}

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

		m_indices = new uint[m_iboSize];
		GLCall(glGenBuffers(1, &m_ibo));
		GLCall(glBindVertexArray(0));
		m_texSlots = new uint[RENDERER_MAX_TEXTURES];
		m_usedTextures = 0;
		m_transformationStack.push(Mat3(1));
	}


	BatchRenderer2D::~BatchRenderer2D()
	{
		delete[] m_indices;
		delete[] m_texSlots;
		GLCall(glDeleteBuffers(1, &m_ibo));
		GLCall(glDeleteBuffers(1, &m_vbo));
		GLCall(glDeleteVertexArrays(1, &m_vao));
	}

	void BatchRenderer2D::PushMatrix(const Mat3 &matrix, bool override)
	{
		if (override)
			m_transformationStack.push(matrix);
		else
		{
			Mat3 back = m_transformationStack.top();
			m_transformationStack.push(back * matrix);
		}
	}

	void BatchRenderer2D::PopMatrix()
	{
		if (m_transformationStack.size() > 1)
			m_transformationStack.pop();
		else
			Log::Warning("Trying to pop the last matrix.");
	}

	const Mat3& BatchRenderer2D::GetTransformationMatrix()
	{
		return m_transformationStack.top();
	}

	void BatchRenderer2D::Begin()
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
		GLCall(m_buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		m_bufferBegin = m_buffer;
		m_indexAmount = 0;
		m_lastIndex = 0;
	}

	void BatchRenderer2D::Draw()
	{
		GLCall(glDisable(GL_DEPTH_TEST));
		for (uint i = 0;i < m_usedTextures;i++)
		{
			GLCall(glActiveTexture(GL_TEXTURE0 + i));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_texSlots[i]));
		}

		GLCall(glBindVertexArray(m_vao));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexAmount * sizeof(uint), m_indices, GL_DYNAMIC_DRAW));

		GLCall(glDrawElements(GL_TRIANGLES, m_indexAmount, GL_UNSIGNED_INT, NULL));

		GLCall(glBindVertexArray(0));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		m_indexAmount = 0;
		m_usedTextures = 0;
		GLCall(glActiveTexture(GL_TEXTURE0));
		GLCall(glEnable(GL_DEPTH_TEST));
	}

	void BatchRenderer2D::End()
	{
		GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void BatchRenderer2D::Flush()
	{
		Log::Info("Flush");
		End();
		Draw();
		Begin();
	}

	void** BatchRenderer2D::GetBufferPointer()
	{

		return &m_buffer;
	}

	uint BatchRenderer2D::GetVertexSize() const
	{
		return m_vertexSize;
	}

	void BatchRenderer2D::Submit(const Renderable* square)
	{
		if (!square->IsValidVertex(this))
		{
			Log::Error("Could not render Renderable, VertexSize doesn't match the Renderer.");
			return;
		}
		square->Draw(this);
	}

	void BatchRenderer2D::FillRect(const Vec2& pos, const Vec2& size, uint color)
	{
		Log::Error("Need to fill rect: BatchRenderer2D::FillRect");
	}

	void BatchRenderer2D::DrawRect(const Vec2& pos, const Vec2& size, uint color)
	{
		Log::Error("Need to draw rect: BatchRenderer2D::DrawRect");
	}

	bool BatchRenderer2D::NeedFlush(uint verticesSize, uint indexCount)
	{
		if (m_iboSize < m_indexAmount + indexCount)
			return true;
		if (m_bufferSize < ((char*)m_buffer - (char*)m_bufferBegin) + verticesSize)
			return true;
		return false;
	}



	uint BatchRenderer2D::GetTextureSlot(const Texture2D* texture)
	{
		if (texture == nullptr || texture->GetTexId() == 0)
			return 0;
		uint ts = 0;
		bool found = false;
		for (int i = 0;i < m_usedTextures;i++)
		{
			if (m_texSlots[i] == texture->GetTexId())
			{
				return i + 1;
			}
		}

		if (m_usedTextures == RENDERER_MAX_TEXTURES)
		{
			m_usedTextures = 0;
			return 0;
		}
		m_texSlots[m_usedTextures] = texture->GetTexId();
		m_usedTextures++;
		return m_usedTextures;
	}

	void BatchRenderer2D::AddIndicesPoly(uint vertices)
	{
		vertices -= 2;
		for (uint i = 0; i < vertices; i++)
		{
			m_indices[m_indexAmount + 3 * i] = m_lastIndex;
			m_indices[m_indexAmount + 3 * i + 1] = m_lastIndex + i + 1;
			m_indices[m_indexAmount + 3 * i + 2] = m_lastIndex + i + 2;

		}
		m_lastIndex = m_indices[m_indexAmount + 3 * (vertices - 1) + 2] + 1;
		m_indexAmount += vertices * 3;
	}
}