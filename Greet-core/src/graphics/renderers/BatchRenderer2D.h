#pragma once

#include <graphics/textures/Texture2D.h>
#include <graphics/AttributePointer.h>
#include <vector>
#include <math/Maths.h>

#define RENDERER_MAX_TEXTURES	32

namespace Greet {

	template<class T>
	class BatchRenderer2D
	{
	private:
		uint m_bufferSize;
		uint m_vertexSize;
		uint m_indexAmount;
		uint m_vao;
		uint m_vbo;
		uint m_ibo;
		uint* m_indices;
		void* m_bufferBegin;
		void* m_buffer;
		uint m_iboSize;
		uint m_lastIndex;
		uint* m_texSlots;
		uint m_usedTextures;
	public:

		BatchRenderer2D(uint triangles = 720000, uint indicesPerTriangle = 3)
		{
			GLCall(glGenVertexArrays(1, &m_vao));
			GLCall(glGenBuffers(1, &m_vbo));

			GLCall(glBindVertexArray(m_vao));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));

			m_vertexSize = T::GetVertexSize();
			// vertexSize * triangles * nrCornersInTriangle
			m_bufferSize = m_vertexSize * triangles * 3;
			m_iboSize = triangles * indicesPerTriangle;

			// Initialize the vertex buffer array
			GLCall(glBufferData(GL_ARRAY_BUFFER, m_bufferSize, nullptr, GL_DYNAMIC_DRAW));

			T::SetAttribPointers();

			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

			m_indices = new uint[m_iboSize];
			GLCall(glGenBuffers(1, &m_ibo));
			GLCall(glBindVertexArray(0));
			m_texSlots = new uint[RENDERER_MAX_TEXTURES];
			m_usedTextures = 0;
		}

		virtual ~BatchRenderer2D()
		{
			delete[] m_indices;
			delete[] m_texSlots;
			GLCall(glDeleteBuffers(1, &m_ibo));
			GLCall(glDeleteBuffers(1, &m_vbo));
			GLCall(glDeleteVertexArrays(1, &m_vao));
		}

		void Begin()
		{
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
			GLCall(m_buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
			m_bufferBegin = m_buffer;
			m_indexAmount = 0;
			m_lastIndex = 0;
		}

		void Draw()
		{
			GLCall(glCullFace(GL_FRONT_AND_BACK));
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

		void End()
		{
			GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}

		void Flush()
		{
			End();
			Draw();
			Begin();
		}

		template<class V>
		void Submit(const V* renderable)
		{
			if (NeedFlush(renderable->GetVertexCount()))
				Flush();
			renderable->Draw(this, &m_buffer);
		}

		bool NeedFlush(uint vertices)
		{
			if (m_iboSize < m_indexAmount + (vertices - 2) * 3)
				return true;
			if (m_bufferSize < ((char*)m_buffer - (char*)m_bufferBegin) / m_vertexSize + vertices)
				return true;
			return false;
		}



		uint GetTextureSlot(const Texture2D* texture)
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

		void AddIndicesPoly(uint vertices)
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
	};

	struct Renderable2DVertex
	{
		Vec2 position;
		uint color;

		static void SetAttribPointers()
		{
			GLCall(glEnableVertexAttribArray(0));
			GLCall(glEnableVertexAttribArray(1));
			GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Renderable2DVertex), (const GLvoid*)offsetof(Renderable2DVertex, Renderable2DVertex::position)));
			GLCall(glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Renderable2DVertex), (const GLvoid*)offsetof(Renderable2DVertex, Renderable2DVertex::color)));
		}
	};
}