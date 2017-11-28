#include "EntityModel.h"

namespace Greet {

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
		glEnableVertexAttribArray(SHADER_MASK_TEXCOORD_INDEX);
		glEnableVertexAttribArray(SHADER_MASK_TEXID_INDEX);
		glVertexAttribPointer(SHADER_VERTEX_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::vertex));
		glVertexAttribPointer(SHADER_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::texCoord));
		glVertexAttribPointer(SHADER_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::texID));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::color));
		glVertexAttribPointer(SHADER_MASK_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::maskTexCoord));
		glVertexAttribPointer(SHADER_MASK_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::maskTexID));
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

	void BatchRenderer::submit(const RenderablePoly* renderable)
	{
		const uint color = renderable->getColor();
		const vec2* vertices = renderable->getVertices();
		const uint vertexCount = renderable->getVertexCount();
		draw(renderable->getPosition(),vertices, vertexCount, color);
	}

	void BatchRenderer::submit(const Renderable2D* renderable)
	{

		const uint color = renderable->getColor();

		const vec2 texPos = renderable->getTexPos();
		const vec2 texSize = renderable->getTexSize();

		const vec2 maskTexPos = renderable->getMaskTexPos();
		const vec2 maskTexSize = renderable->getMaskTexSize();

		const GLuint texID = renderable->getTexID();
		const GLuint maskTexID = renderable->getMaskTexID();
		uint ts = getTextureSlot(texID);
		uint mts = getTextureSlot(maskTexID);
		draw(renderable->getPosition(),renderable->getSize(), texPos, texSize, ts, color, mts,maskTexPos,maskTexSize);
	}

	void BatchRenderer::submitString(const std::string& text, const vec2& position, Font* font, const uint& color)
	{
		using namespace ftgl;
		uint ts = getTextureSlot(font->getAtlasID());
		texture_font_t* ftfont = font->getFTFont();
		float x = position.x;
		const vec2& scale = vec2(1,1);//font->getScale();
		float baseline = ftfont->size - ftfont->ascender;
		for(uint i = 0;i<text.length();i++)
		{
			const char& c = text[i];
			texture_glyph_t* glyph = texture_font_get_glyph(ftfont,c);
			if(glyph != NULL)
			{
				if (i > 0)
				{
					float kerning = texture_glyph_get_kerning(glyph,text[i-1]);
					x += kerning / scale.x;
				}
				float x0 = x + glyph->offset_x / scale.x;
				float y0 = position.y - glyph->offset_y / scale.y;
				float x1 = x0 + glyph->width / scale.x;
				float y1 = y0 + glyph->height / scale.y;
					
					
				float u0 = glyph->s0;
				float v0 = 1-glyph->t0;
				float u1 = glyph->s1;
				float v1 = 1-glyph->t1;
				appendVertexBuffer(vec2(x0,y0),vec2(u0,v0),ts,color, 0, vec2(0, 0));
				appendVertexBuffer(vec2(x0,y1),vec2(u0,v1),ts,color, 0, vec2(0, 0));
				appendVertexBuffer(vec2(x1,y1),vec2(u1,v1),ts,color, 0, vec2(0, 0));
				appendVertexBuffer(vec2(x1,y0),vec2(u1,v0),ts,color, 0, vec2(0, 0));
				x += glyph->advance_x / scale.x;
				addIndicesPoly(4);
				m_iboSize += 6;
			}
		}
	}

	void BatchRenderer::submit(const Transform& transform, uint texID, vec2 texPos, vec2 texSize, uint color, uint maskTexId, const vec2& maskTexPos, const vec2& maskTexSize)
	{
		draw(transform, texPos, texSize, getTextureSlot(texID), color, getTextureSlot(maskTexId),maskTexPos,maskTexSize);
	}

	void BatchRenderer::submit(const vec2& position,const vec2& size, uint texID, vec2 texPos, vec2 texSize, uint color,uint maskTexId, const vec2& maskTexPos, const vec2& maskTexSize)
	{
		uint ts = getTextureSlot(texID);
		uint mts = getTextureSlot(maskTexId);
		appendVertexBuffer(vec2(position.x, position.y), vec2(texPos.x, texPos.y), ts, color, mts, vec2(maskTexPos.x, maskTexPos.y));
		appendVertexBuffer(vec2(position.x, position.y + size.y), vec2(texPos.x, texPos.y + texSize.y), ts, color, mts, vec2(maskTexPos.x, maskTexPos.y + maskTexSize.y));
		appendVertexBuffer(vec2(position.x + size.x, position.y + size.y), vec2(texPos.x + texSize.x, texPos.y + texSize.y), ts, color, mts, vec2(maskTexPos.x + maskTexSize.x, maskTexPos.y + maskTexSize.y));
		appendVertexBuffer(vec2(position.x + size.x, position.y), vec2(texPos.x + texSize.x, texPos.y), ts, color, mts, vec2(maskTexPos.x + maskTexSize.x, maskTexPos.y));
		addIndicesPoly(4);
		m_iboSize += 6;
	}

	void BatchRenderer::draw(const vec2& position,const vec2& size, const vec2& texPos, const vec2& texSize, const uint textureSlot, const uint color, const uint& maskTexSlot, const vec2& maskTexPos, const vec2& maskTexSize)
	{
		appendVertexBuffer(vec2(position.x, position.y),vec2(texPos.x, texPos.y),textureSlot,color, maskTexSlot, vec2(maskTexPos.x, maskTexPos.y));
		appendVertexBuffer(vec2(position.x, position.y+size.y),vec2(texPos.x, texPos.y + texSize.y),textureSlot,color, maskTexSlot, vec2(maskTexPos.x, maskTexPos.y+maskTexSize.y));
		appendVertexBuffer(vec2(position.x+size.x, position.y+size.y),vec2(texPos.x + texSize.x, texPos.y + texSize.y),textureSlot,color, maskTexSlot, vec2(maskTexPos.x + maskTexSize.x, maskTexPos.y + maskTexSize.y));
		appendVertexBuffer(vec2(position.x+size.x, position.y),vec2(texPos.x + texSize.x, texPos.y),textureSlot,color, maskTexSlot, vec2(maskTexPos.x + maskTexSize.x, maskTexPos.y));
		addIndicesPoly(4);
		m_iboSize += 6;
	}

	void BatchRenderer::draw(const Transform& transform, const vec2& texPos, const vec2& texSize, const uint textureSlot, const uint& color, const uint& maskTexSlot, const vec2& maskTexPos, const vec2& maskTexSize)
	{
		pushMatrix(transform.getMatrix());
			
		appendVertexBuffer(vec2(0, 0),vec2(texPos.x, texPos.y),textureSlot,color, maskTexSlot,vec2(maskTexPos.x, maskTexPos.y));
		appendVertexBuffer(vec2(0, 1),vec2(texPos.x, texPos.y + texSize.y),textureSlot,color, maskTexSlot, vec2(maskTexPos.x, maskTexPos.y+maskTexSize.y));
		appendVertexBuffer(vec2(1, 1),vec2(texPos.x + texSize.x, texPos.y + texSize.y),textureSlot,color, maskTexSlot, vec2(maskTexPos.x + maskTexSize.x, maskTexPos.y + maskTexSize.y));
		appendVertexBuffer(vec2(1, 0),vec2(texPos.x + texSize.x, texPos.y),textureSlot,color, maskTexSlot, vec2(maskTexPos.x + maskTexSize.x, maskTexPos.y));
			
		popMatrix();
		addIndicesPoly(4);
		m_iboSize += 6;
	}

	void BatchRenderer::draw(const vec2& position, const vec2* vertices, const uint amount, const uint color)
	{
		for (uint i = 0; i < amount; i++)
		{
			appendVertexBuffer(position+vertices[i],vec2(0,0),0,color, 0, vec2(0, 0));
		}
		addIndicesPoly(amount);
		m_iboSize += (amount-2)*3;
	}

	void BatchRenderer::drawRect(const vec2& position, const vec2& size, const uint& color)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		appendVertexBuffer(position, vec2(0, 0), 0, color, 0, vec2(0, 0));
		appendVertexBuffer(vec2(position.x,position.y+size.y), vec2(0, 1), 0, color,0,vec2(0,1));
		appendVertexBuffer(vec2(position.x+size.x, position.y + size.y), vec2(1, 1), 0, color, 0, vec2(1, 1));
		appendVertexBuffer(vec2(position.x + size.x, position.y), vec2(1, 0), 0, color, 0, vec2(1, 0));

		addIndicesPoly(4);
		m_iboSize += 6;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void BatchRenderer::fillRect(const vec2& position, const vec2& size, const uint& color)
	{
		appendVertexBuffer(position, vec2(0, 0), 0, color, 0, vec2(0, 0));
		appendVertexBuffer(vec2(position.x, position.y + size.y), vec2(0, 1), 0, color, 0, vec2(0, 1));
		appendVertexBuffer(vec2(position.x + size.x, position.y + size.y), vec2(1, 1), 0, color, 0, vec2(1, 1));
		appendVertexBuffer(vec2(position.x + size.x, position.y), vec2(1, 0), 0, color, 0, vec2(1, 0));

		addIndicesPoly(4);
		m_iboSize += 6;
	}

	void BatchRenderer::fillRect(const vec2& position, const vec2& size, const uint& color, const Sprite* mask)
	{
		const vec2& m_maskTexPos = mask->getTexPos();
		const vec2& m_maskTexSize = mask->getTexSize();

		const uint& mtid = getTextureSlot(mask->getTextureID());

		appendVertexBuffer(position, vec2(0, 0), 0, color, mtid, m_maskTexPos);
		appendVertexBuffer(vec2(position.x, position.y + size.y), vec2(0, 1), 0, color, mtid, vec2(m_maskTexPos.x, m_maskTexPos.y+m_maskTexSize.y));
		appendVertexBuffer(vec2(position.x + size.x, position.y + size.y), vec2(1, 1), 0, color, mtid, m_maskTexPos+m_maskTexSize);
		appendVertexBuffer(vec2(position.x + size.x, position.y), vec2(1, 0), 0, color, mtid, vec2(m_maskTexPos.x + m_maskTexSize.x, m_maskTexPos.y));

		addIndicesPoly(4);
		m_iboSize += 6;
	}
		
	void BatchRenderer::appendVertexBuffer(const vec2& position, const vec2& texCoord, const uint& texID, const uint& color, const uint& maskTexId, const vec2& maskTexCoord)
	{
		m_buffer->vertex = *m_transformationBack*position;
		m_buffer->texCoord = texCoord;
		m_buffer->texID = texID;
		m_buffer->color = color;
		m_buffer->maskTexCoord = maskTexCoord;
		m_buffer->maskTexID = maskTexId;
		m_buffer++;
	}

	uint BatchRenderer::getTextureSlot(const GLuint texID)
	{
		if (texID == 0)
			return 0.0f;
		uint ts = 0.0f;
		bool found = false;
		const int size = m_texSlots.size();
		for (int i = 0; i < size; i++)
		{
			if (m_texSlots[i] == texID)
			{
				ts = (uint)(i + 1);
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
			ts = (uint)(size + 1);
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
		glDisable(GL_DEPTH_TEST);
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
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_DEPTH_TEST);
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
