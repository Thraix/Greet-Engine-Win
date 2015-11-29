#include "batchrenderer2d.h"

namespace greet{ namespace graphics{

	BatchRenderer2D::BatchRenderer2D()
	{
		init();
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		delete m_ibo;
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1,&m_vao);
		for (uint i = 0; i < m_texSlots.size();i++)
		{
			delete &m_texSlots[i];
		}
	}

	void BatchRenderer2D::init()
	{
		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER,m_vbo);

		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_TEXCOORD_INDEX);
		glEnableVertexAttribArray(SHADER_TEXID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);
		glEnableVertexAttribArray(SHADER_SELF_VERTEX_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::vertex));
		glVertexAttribPointer(SHADER_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::texCoord));
		glVertexAttribPointer(SHADER_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::texID)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::color));
		glVertexAttribPointer(SHADER_SELF_VERTEX_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::selfVertex));
		glBindBuffer(GL_ARRAY_BUFFER,0);

		//Generate all the indices at runtime
		GLuint *indices = new GLuint[RENDERER_INDICES_SIZE];
		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i+=6)
		{
			indices[i    ] = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset;
			offset += 4;
		}

		m_ibo = new BatchIndexBuffer(indices, RENDERER_INDICES_SIZE);

		glBindVertexArray(0);
	}

	void BatchRenderer2D::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::submit(const Renderable4Poly* renderable)
	{
		const uint color = renderable->getColor();

		const math::vec2& ul = renderable->getUL();
		const math::vec2& ur = renderable->getUR();
		const math::vec2& dr = renderable->getDR();
		const math::vec2& dl = renderable->getDL();
		const math::vec2& texPos = renderable->getTexPos();
		const math::vec2& texSize = renderable->getTexSize();

		const GLuint texID = renderable->getTexID();

		float ts = getTextureSlot(texID);
		draw(ul,ur,dr,dl, texPos, texSize, ts, color);
	}

	void BatchRenderer2D::submit(const Renderable2D* renderable)
	{

		const uint color = renderable->getColor();

		const math::vec2 texPos = renderable->getTexPos();
		const math::vec2 texSize = renderable->getTexSize();

		const GLuint texID = renderable->getTexID();

		float ts = getTextureSlot(texID);
		const math::Transform& transformation = renderable->getTransform();
		draw(transformation,texPos, texSize, ts, color);
	}

	void BatchRenderer2D::submitString(const Label* label, bool shadow)
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

	void BatchRenderer2D::submit(const math::Transform& transform, uint texID, math::vec2 texPos, math::vec2 texSize, uint color)
	{
		draw(transform,texPos, texSize,getTextureSlot(texID),color);
	}

	void BatchRenderer2D::draw(const math::vec2& ul, const math::vec2& ur, const math::vec2& dr, const math::vec2& dl, const math::vec2& texPos, const math::vec2& texSize, const float textureSlot, const uint color)
	{
		m_buffer->vertex = *m_transformationBack*math::vec2(ul.x, ul.y);
		m_buffer->texCoord = texPos;
		m_buffer->texID = textureSlot;
		m_buffer->color = color;
		m_buffer->selfVertex = math::vec2(1, 0);
		m_buffer++;

		m_buffer->vertex = *m_transformationBack*math::vec2(ur.x, ur.y);
		m_buffer->texCoord = math::vec2(texPos.x, texPos.y + texSize.y);
		m_buffer->texID = textureSlot;
		m_buffer->color = color;
		m_buffer->selfVertex = math::vec2(1, 0);
		m_buffer++;

		m_buffer->vertex = *m_transformationBack*math::vec2(dr.x, dr.y);
		m_buffer->texCoord = math::vec2(texPos.x + texSize.x, texPos.y + texSize.y);
		m_buffer->texID = textureSlot;
		m_buffer->color = color;
		m_buffer->selfVertex = math::vec2(1, 0);
		m_buffer++;

		m_buffer->vertex = *m_transformationBack*math::vec2(dl.x, dl.y);
		m_buffer->texCoord = math::vec2(texPos.x + texSize.x, texPos.y);
		m_buffer->texID = textureSlot;
		m_buffer->color = color;
		m_buffer->selfVertex = math::vec2(1, 0);
		m_buffer++;

		m_ibo->addCount(6);
	}

	void BatchRenderer2D::draw(const math::Transform& transform, const math::vec2& texPos, const math::vec2& texSize, const float textureSlot, const uint color)
	{
		pushMatrix(transform.getMatrix());
		m_buffer->vertex = *m_transformationBack*VERTEX_TOP_LEFT;
		m_buffer->texCoord = texPos;
		m_buffer->texID = textureSlot;
		m_buffer->color = color;
		m_buffer->selfVertex = VERTEX_TOP_LEFT;
		m_buffer++;

		m_buffer->vertex = *m_transformationBack*VERTEX_DOWN_LEFT;
		m_buffer->texCoord = math::vec2(texPos.x, texPos.y + texSize.y);
		m_buffer->texID = textureSlot;
		m_buffer->color = color;
		m_buffer->selfVertex = VERTEX_DOWN_LEFT;
		m_buffer++;

		m_buffer->vertex = *m_transformationBack*VERTEX_DOWN_RIGHT;
		m_buffer->texCoord = math::vec2(texPos.x + texSize.x, texPos.y + texSize.y);
		m_buffer->texID = textureSlot;
		m_buffer->color = color;
		m_buffer->selfVertex = VERTEX_DOWN_RIGHT;
		m_buffer++;

		m_buffer->vertex = *m_transformationBack*VERTEX_TOP_RIGHT;
		m_buffer->texCoord = math::vec2(texPos.x + texSize.x, texPos.y);
		m_buffer->texID = textureSlot;
		m_buffer->color = color;
		m_buffer->selfVertex = VERTEX_TOP_RIGHT;
		m_buffer++;
		popMatrix();
		m_ibo->addCount(6);
	}



	float BatchRenderer2D::getTextureSlot(const GLuint texID)
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

	void BatchRenderer2D::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER,0);
	}

	void BatchRenderer2D::flush()
	{
		for (uint i = 0; i < m_texSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D,m_texSlots[i]);
		}
		
		glBindVertexArray(m_vao);
		m_ibo->enable();

		GLsizei size = m_ibo->getCount();

		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, NULL);

		m_ibo->disable();
		glBindVertexArray(0);

		m_ibo->resetCount();
		m_texSlots.clear();
	}
}}