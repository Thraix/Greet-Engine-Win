#include "RenderableSquare.h"
namespace Greet 
{
	void RenderableSquare::SetVertex(RenderableSquareVertex** bufferPointer, const Vec2& pos, const Vec2& texCoord, uint color, float texId) const
	{
		(*bufferPointer)->position = pos;
		(*bufferPointer)->texCoord = texCoord;
		(*bufferPointer)->color = color;
		(*bufferPointer)->texId = texId;
		(*bufferPointer)++;
	}

	void RenderableSquare::SetVertices(BatchRenderer2D<RenderableSquareVertex>* renderer, RenderableSquareVertex** bufferPointer) const
	{

		uint texId = renderer->GetTextureSlot(m_texture);
		if (m_texture != nullptr && texId == 0)
		{
			renderer->Flush();
			texId = renderer->GetTextureSlot(m_texture);
		}

		SetVertex(bufferPointer, m_pos, m_texPos, m_color, texId);
		SetVertex(bufferPointer, m_pos + Vec2(0, m_size.y), m_texPos + Vec2(0, m_texSize.y), m_color, texId);
		SetVertex(bufferPointer, m_pos + Vec2(m_size.x, m_size.y), m_texPos + Vec2(m_texSize.x, m_texSize.y), m_color, texId);
		SetVertex(bufferPointer, m_pos + Vec2(m_size.x, 0), m_texPos + Vec2(m_texSize.x, 0), m_color, texId);

		renderer->AddIndicesPoly(GetVertexCount());
	}

	uint RenderableSquare::GetVertexCount() const
	{
		return 4;
	}
}