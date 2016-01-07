#include "batchrenderer.h"



namespace greet {
	namespace graphics {

		BatchRenderer::BatchRenderer()
		{
			init();
		}

		BatchRenderer::~BatchRenderer()
		{
			delete m_indices;
			glDeleteBuffers(1, &m_ibo);
			glDeleteBuffers(1, &m_vbo);
			glDeleteVertexArrays(1, &m_vao);
			for (uint i = 0; i < m_texSlots.size(); i++)
			{
				delete &m_texSlots[i];
			}
		}

		void BatchRenderer::init()
		{
			glGenVertexArrays(1, &m_vao);
			glGenBuffers(1, &m_vbo);

			glBindVertexArray(m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_TEXCOORD_INDEX);
			glEnableVertexAttribArray(SHADER_TEXID_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::vertex));
			glVertexAttribPointer(SHADER_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::texCoord));
			glVertexAttribPointer(SHADER_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::texID));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::color));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			//Generate all the indices at runtime
			m_indices = new GLuint[RENDERER_INDICES_SIZE];
			glGenBuffers(1, &m_ibo);
			glBindVertexArray(0);
		}

		void BatchRenderer::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			m_iboSize = 0;
			m_lastIndex = 0;
		}

		void BatchRenderer::submit(const Renderable4Poly* renderable)
		{
			const uint color = renderable->getColor();

			math::vec2 * vertices = new math::vec2[4]{ renderable->getUL() , renderable->getUR() ,renderable->getDR() ,renderable->getDL() };

			const math::vec2& texPos = renderable->getTexPos();
			const math::vec2& texSize = renderable->getTexSize();

			const GLuint texID = renderable->getTexID();

			float ts = getTextureSlot(texID);
			draw(math::vec2(0,0), vertices,4,0xffffffff);
		}

		void BatchRenderer::submit(const RenderablePoly* renderable)
		{
			const uint color = renderable->getColor();
			const math::vec2* vertices = renderable->getVertices();
			const uint vertexCount = renderable->getVertexCount();
			draw(renderable->getPosition(),vertices, vertexCount, color);
		}

		void BatchRenderer::submit(const Renderable2D* renderable)
		{

			const uint color = renderable->getColor();

			const math::vec2 texPos = renderable->getTexPos();
			const math::vec2 texSize = renderable->getTexSize();

			const GLuint texID = renderable->getTexID();

			float ts = getTextureSlot(texID);
			const math::Transform& transformation = renderable->getTransform();
			draw(transformation, texPos, texSize, ts, color);
		}

		void BatchRenderer::submitString(const Label* label, bool shadow)
		{
			float ts = getTextureSlot(label->getTextureID());
			const std::vector<RenderableGlyph*> glyphs = label->getGlyphs();
			math::mat3 transform;
			uint color;
			if (shadow)
			{
				transform = label->getShadowTransform();
				color = label->getShadowColor();
			}
			else
			{
				transform = label->getTransform();
				color = label->getColor();
			}
			pushMatrix(transform);
			for (uint i = 0; i < glyphs.size(); i++)
			{
				const RenderableGlyph* glyph = glyphs[i];
				draw(glyph->getTransform(), glyph->getTexPos(), glyph->getTexSize(), ts, color);
			}
			popMatrix();
		}

		void BatchRenderer::submit(const math::Transform& transform, uint texID, math::vec2 texPos, math::vec2 texSize, uint color)
		{
			draw(transform, texPos, texSize, getTextureSlot(texID), color);
		}

		void BatchRenderer::draw(const math::Transform& transform, const math::vec2& texPos, const math::vec2& texSize, const float textureSlot, const uint color)
		{
			pushMatrix(transform.getMatrix());
			m_buffer->vertex = *m_transformationBack*math::vec2(0,0);
			m_buffer->texCoord = texPos;
			m_buffer->texID = textureSlot;
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = *m_transformationBack*math::vec2(0, 1);
			m_buffer->texCoord = math::vec2(texPos.x, texPos.y + texSize.y);
			m_buffer->texID = textureSlot;
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = *m_transformationBack*math::vec2(1, 1);
			m_buffer->texCoord = math::vec2(texPos.x + texSize.x, texPos.y + texSize.y);
			m_buffer->texID = textureSlot;
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = *m_transformationBack*math::vec2(1, 0);
			m_buffer->texCoord = math::vec2(texPos.x + texSize.x, texPos.y);
			m_buffer->texID = textureSlot;
			m_buffer->color = color;
			m_buffer++;
			popMatrix();
			addIndicesPoly(4);
			m_iboSize += 6;
		}

		void BatchRenderer::draw(const math::vec2& position, const math::vec2* vertices, const uint amount, const uint color)
		{
			for (uint i = 0; i < amount; i++)
			{
				m_buffer->vertex = *m_transformationBack*(position+vertices[i]);
				m_buffer->texCoord = math::vec2(0,0);
				m_buffer->texID = 0;
				m_buffer->color = color;
				m_buffer++;
			}
			addIndicesPoly(amount);
			m_iboSize += (amount-2)*3;
		}

		float BatchRenderer::getTextureSlot(const GLuint texID)
		{
			float ts = 0.0f;
			if (texID > 0)
			{
				bool found = false;
				const int size = m_texSlots.size();
				for (int i = 0; i < size; i++)
				{
					if (m_texSlots[i] == texID)
					{
						ts = (float)(i + 1);
						found = true;
						break;
					}
				}
				if (!found)
				{
					if (size >= RENDERER_MAX_TEXTURES)
					{
						end();
						flush();
						begin();
					}
					m_texSlots.push_back(texID);
					ts = (float)(size + 1);
				}
			}
			return ts;
		}

		void BatchRenderer::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer::flush()
		{
			for (uint i = 0; i < m_texSlots.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_texSlots[i]);
			}

			enableBuffers();

			glDrawElements(GL_TRIANGLES, m_iboSize, GL_UNSIGNED_INT, NULL);

			disableBuffers();

			m_iboSize = 0;
			m_texSlots.clear();
		}

		void BatchRenderer::enableBuffers()
		{
			glBindVertexArray(m_vao);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_iboSize*sizeof(uint), m_indices, GL_DYNAMIC_DRAW);
		}

		void BatchRenderer::disableBuffers()
		{
			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void BatchRenderer::addIndicesPoly(uint vertices)
		{
			vertices -= 2;
			for (uint i = 0; i < vertices; i++)
			{
				m_indices[m_iboSize + 3 * i] = m_lastIndex;
				m_indices[m_iboSize + 3 * i + 1] = m_lastIndex + i+1;
				m_indices[m_iboSize + 3 * i + 2] = m_lastIndex + i+2;

			}
			m_lastIndex = m_indices[m_iboSize + 3 * (vertices - 1) + 2] + 1;
		}
	}
}