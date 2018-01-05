#include "Renderable2D.h"

#include <graphics/renderers/BatchRenderer2D.h>

namespace Greet 
{

	void Renderable2D::Draw(BatchRenderer2D* renderer) const
	{
		// Check if the renderer needs to be flushed
		if (renderer->NeedFlush(sizeof(Renderable2DVertex) * 4, 6))
			renderer->Flush();

		// Check if we can draw with the texture.
		uint texId = renderer->GetTextureSlot(sprite->GetTexture());
		if (sprite->GetTexture() != nullptr && texId == 0)
		{
			// Flush the renderer if it cannot add another texture.
			renderer->Flush();
			texId = renderer->GetTextureSlot(sprite->GetTexture());
		}

		// Buffer for rendering
		Renderable2DVertex** vertices = (Renderable2DVertex**)renderer->GetBufferPointer();

		// Add the values to the buffers
		SetVertex(vertices, pos, sprite->GetTexPos(), color, texId);
		SetVertex(vertices, pos + Vec2(0, size.y), sprite->GetTexPos() + Vec2(0, sprite->GetTexSize().y), color, texId);
		SetVertex(vertices, pos + Vec2(size.x, size.y), sprite->GetTexPos() + Vec2(sprite->GetTexSize().x, sprite->GetTexSize().y), color, texId);
		SetVertex(vertices, pos + Vec2(size.x, 0), sprite->GetTexPos() + Vec2(sprite->GetTexSize().x, 0), color, texId);

		renderer->AddIndicesPoly(4);
	}

	void Renderable2D::SetVertex(Renderable2DVertex** bufferPointer, const Vec2& pos, const Vec2& texCoord, uint color, float texId) const
	{
		// Set values to vertex
		(*bufferPointer)->position = pos;
		(*bufferPointer)->texCoord = texCoord;
		(*bufferPointer)->color = color;
		(*bufferPointer)->texId = texId;
		(*bufferPointer)++;
	}
}