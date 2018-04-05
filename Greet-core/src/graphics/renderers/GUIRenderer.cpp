#include "GUIRenderer.h"

#include <graphics/gui/GUI.h>

namespace Greet
{

	GUIRenderer::GUIRenderer()
	{
		GLCall(glGenVertexArrays(1, &m_vao));
		GLCall(glGenBuffers(1, &m_vbo));

		GLCall(glBindVertexArray(m_vao));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
		m_textures = new uint[32];
		m_vertices = 10000;
		m_bufferSize = m_vertices * sizeof(GUIVertex) * 4;
		m_iboSize = m_vertices * 6;
		GLCall(glBufferData(GL_ARRAY_BUFFER, m_bufferSize, NULL, GL_DYNAMIC_DRAW));

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glEnableVertexAttribArray(1));
		GLCall(glEnableVertexAttribArray(2));
		GLCall(glEnableVertexAttribArray(3));
		GLCall(glEnableVertexAttribArray(4));
		GLCall(glEnableVertexAttribArray(5));
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (const GLvoid*)offsetof(GUIVertex, GUIVertex::pos)));
		GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (const GLvoid*)offsetof(GUIVertex, GUIVertex::texCoord)));
		GLCall(glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (const GLvoid*)offsetof(GUIVertex, GUIVertex::texId)));
		GLCall(glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (const GLvoid*)offsetof(GUIVertex, GUIVertex::color)));
		GLCall(glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (const GLvoid*)offsetof(GUIVertex, GUIVertex::viewport)));
		GLCall(glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (const GLvoid*)offsetof(GUIVertex, GUIVertex::isHSV)));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		//Generate all the indices at runtime
		m_indices = new uint[m_iboSize];
		GLCall(glGenBuffers(1, &m_ibo));
		GLCall(glBindVertexArray(0));
	}

	void GUIRenderer::Begin()
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
		GLCall(m_buffer = (GUIVertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

		m_bufferBegin = m_buffer;
		m_lastIndex = 0;
		m_iboCount = 0;
		m_textureCount = 0;
	}

	void GUIRenderer::Draw()
	{
		glCullFace(GL_FRONT_AND_BACK);
		GLCall(glDisable(GL_DEPTH_TEST));

		for (byte i = 0; i < m_textureCount; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_textures[i]);
		}

		GLCall(glBindVertexArray(m_vao));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_iboCount, m_indices, GL_DYNAMIC_DRAW));

		GLCall(glDrawElements(GL_TRIANGLES, m_iboSize, GL_UNSIGNED_INT, NULL));

		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
		GLCall(glBindVertexArray(0));

		GLCall(glActiveTexture(GL_TEXTURE0));
		GLCall(glEnable(GL_DEPTH_TEST));
	}

	void GUIRenderer::End()
	{
		GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void GUIRenderer::Flush()
	{
		End();
		Draw();
		Begin();
	}

	void GUIRenderer::PushViewport(const Vec2& pos, const Vec2& size, bool overwrite)
	{
		Vec2 p1 = GetMatrix() * pos;
		Vec2 p2 = GetMatrix() * (pos + size);
		if (!m_viewports.empty() && !overwrite)
		{
			Vec4 top = m_viewports.top();
			p1.x = p1.x < top.x ? top.x : p1.x;
			p1.y = p1.y < top.y ? top.y : p1.y;
			p2.x = p2.x > top.z ? top.z : p2.x;
			p2.y = p2.y > top.w ? top.w : p2.y;
		}
		m_viewports.push(Vec4(p1.x, p1.y, p2.x, p2.y));
	}

	void GUIRenderer::PopViewport()
	{
		if (m_viewports.empty())
		{
			Log::Warning("Trying to pop the last viewport.");
			return;
		}
		m_viewports.pop();
	}

	void GUIRenderer::SubmitLine(const Vec2& pos, float length, float width, bool vertical, const Vec4& color, bool isHsv)
	{

		SubmitRect(pos, Vec2(vertical ? width : length, vertical ? length : width), color,isHsv);
	}

	void GUIRenderer::SubmitTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, const Vec4& color, bool isHsv)
	{
		AppendTriangle(pos1,pos2,pos3,color,isHsv);
	}

	void GUIRenderer::SubmitRect(const Vec2& pos, const Vec2& size, const Vec4& color, bool isHsv)
	{
		AppendQuad(pos, size, Vec2(0, 0), Vec2(1, 1), 0, color, isHsv);
	}

	void  GUIRenderer::SubmitRect(const Vec2& pos, const Vec2& size, const Vec4& color1, const Vec4& color2, const Vec4& color3, const Vec4& color4, bool isHsv)
	{
		AppendQuad(pos, size, Vec2(0, 0), Vec2(1, 1), 0, color1, color2, color3, color4, isHsv);
	}


	void GUIRenderer::SubmitString(const std::string& text, const Vec2& position, Font* font, const Vec4& color, bool isHsv)
	{
		using namespace ftgl;
		float ts = GetTextureSlot(font->GetAtlasID());
		if (ts == 0 && font->GetAtlasID() != 0)
		{
			Flush();
			ts = GetTextureSlot(font->GetAtlasID());
		}

		texture_font_t* ftfont = font->GetFTFont();
		float x = position.x;
		const Vec2& scale = Vec2(1, 1);//font->getScale();
		float baseline = ftfont->size - ftfont->ascender;
		Vec2 pos;
		Vec2 size;
		Vec2 uv0;
		Vec2 uv1;
		for (uint i = 0;i < text.length();i++)
		{
			const char& c = text[i];
			texture_glyph_t* glyph = texture_font_get_glyph(ftfont, c);
			if (glyph != NULL)
			{
				if (i > 0)
				{
					float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
					x += kerning / scale.x;
				}

				pos.x = x + glyph->offset_x / scale.x;
				pos.y = position.y - glyph->offset_y / scale.y;
				size.x = glyph->width / scale.x;
				size.y = glyph->height / scale.y;

				uv0.x = glyph->s0;
				uv0.y = 1 - glyph->t0;
				uv1.x = glyph->s1;
				uv1.y = 1 - glyph->t1;

				AppendQuad(pos, size, uv0, uv1, ts, color, isHsv);

				x += glyph->advance_x / scale.x;
			}
		}
	}

	float GUIRenderer::GetTextureSlot(uint id)
	{
		if (id == 0)
			return 0;
		for (byte i = 0; i < m_textureCount; i++)
		{
			if (m_textures[i] == id)
				return i + 1;
		}

		if (m_textureCount == 32)
			return 0.0f;
		m_textures[m_textureCount++] = id;
		return m_textureCount;
	}

	bool GUIRenderer::NeedFlush(uint indices, uint vertices)
	{
		if (m_vertices - (m_buffer - m_bufferBegin) < vertices)
			return true;
		if (m_iboSize - m_iboCount < indices)
			return true;
		return false;
	}

	Vec4 GUIRenderer::GetViewport(const Vec2& pos1, const Vec2& pos2) const
	{
		if (!m_viewports.empty())
			return m_viewports.top();
		else
		{
			Log::Info("No viewport");
			Vec4 viewport;;
			Vec2 temp = GetMatrix() * Vec2(pos1.x, pos1.y);
			viewport.x = temp.x;
			viewport.y = temp.y;
			temp = GetMatrix() * Vec2(pos2.x, pos2.y);
			viewport.z = temp.x;
			viewport.w = temp.y;
			return viewport;
		}
	}

	void GUIRenderer::AppendTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, const Vec4& color, bool isHsv)
	{
		if (NeedFlush(3, 3))
			Flush();

		Vec4 viewport = GetViewport(Vec2(std::min(std::min(pos1.x,pos2.x),pos3.x), std::min(std::min(pos1.y, pos2.y), pos3.y)), Vec2(std::max(std::max(pos1.x, pos2.x), pos3.x), std::max(std::max(pos1.y, pos2.y), pos3.y)));

		AppendVertexBuffer(pos1, Vec2(0, 0), 0.0f, color, viewport, isHsv);
		AppendVertexBuffer(pos2, Vec2(0, 0), 0.0f, color, viewport, isHsv);
		AppendVertexBuffer(pos3, Vec2(0, 0), 0.0f, color, viewport, isHsv);

		m_indices[m_iboCount++] = m_lastIndex;
		m_indices[m_iboCount++] = m_lastIndex + 1;
		m_indices[m_iboCount++] = m_lastIndex + 2;

		m_lastIndex += 3;
	}

	void GUIRenderer::AppendQuad(const Vec2& position, const Vec2& size, const Vec2& texCoord1, const Vec2& texCoord2, float texId, const Vec4& color1, const Vec4& color2, const Vec4& color3, const Vec4& color4, bool isHsv)
	{
		if (NeedFlush(6, 4))
			Flush();

		Vec4 viewport = GetViewport(position, position + size);

		AppendVertexBuffer(position, texCoord1, texId, color1, viewport, isHsv);
		AppendVertexBuffer(Vec2(position.x, position.y + size.y), Vec2(texCoord1.x, texCoord2.y), texId, color3, viewport, isHsv);
		AppendVertexBuffer(position + size, texCoord2, texId, color4, viewport, isHsv);
		AppendVertexBuffer(Vec2(position.x + size.x, position.y), Vec2(texCoord2.x, texCoord1.y), texId, color2, viewport, isHsv);

		m_indices[m_iboCount++] = m_lastIndex;
		m_indices[m_iboCount++] = m_lastIndex + 1;
		m_indices[m_iboCount++] = m_lastIndex + 2;
		m_indices[m_iboCount++] = m_lastIndex;
		m_indices[m_iboCount++] = m_lastIndex + 2;
		m_indices[m_iboCount++] = m_lastIndex + 3;

		m_lastIndex += 4;
	}

	void GUIRenderer::AppendQuad(const Vec2& position, const Vec2& size, const Vec2& texCoord1, const Vec2& texCoord2, float texId, const Vec4& color, bool isHsv)
	{
		AppendQuad(position, size, texCoord1, texCoord2, texId, color, color, color, color, isHsv);
	}

	void GUIRenderer::AppendVertexBuffer(const Vec2& position, const Vec2& texCoord, float texId, const Vec4& color, const Vec4& viewport, bool isHsv)
	{
		m_buffer->pos = GetMatrix() * position;
		m_buffer->texCoord = texCoord;
		m_buffer->texId = texId;
		m_buffer->color = color;
		m_buffer->viewport = viewport;
		m_buffer->isHSV = isHsv ? 1.0 : 0.0;
		m_buffer++;
	}

}