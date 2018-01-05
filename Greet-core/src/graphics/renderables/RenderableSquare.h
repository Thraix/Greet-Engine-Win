#pragma once

#include <graphics/renderers/BatchRenderer2D.h>
#include <graphics/textures/Texture2D.h>
#include <math/Maths.h>

namespace Greet {
	
	struct RenderableSquareVertex
	{
		Vec2 position;
		Vec2 texCoord;
		float texId;
		uint color;
	};

	class RenderableSquare
	{
	private:
		Vec2 m_pos;
		Vec2 m_size;
		Vec2 m_texPos;
		Vec2 m_texSize;
		uint m_color;
		Texture2D* m_texture;
	public:

		RenderableSquare(const Vec2& pos, const Vec2& size, uint color)
			: m_pos(pos), m_size(size), m_color(color), m_texPos(Vec2(0,0)), m_texSize(Vec2(1,1)), m_texture(nullptr)
		{}

		RenderableSquare(const Vec2& pos, const Vec2& size, Texture2D* texture, const Vec2& texPos = Vec2(0, 0), const Vec2& texSize = Vec2(1, 1))
			: m_pos(pos), m_size(size), m_color(0xffffffff), m_texture(texture), m_texPos(texPos), m_texSize(texSize)
		{}

		RenderableSquare(const Vec2& pos, const Vec2& size, Texture2D* texture, uint color, const Vec2& texPos = Vec2(0, 0), const Vec2& texSize = Vec2(1, 1))
			: m_pos(pos), m_size(size), m_color(color), m_texture(texture), m_texPos(texPos), m_texSize(texSize)
		{}

		static void SetAttribPointers()
		{
			GLCall(glEnableVertexAttribArray(0));
			GLCall(glEnableVertexAttribArray(1));
			GLCall(glEnableVertexAttribArray(2));
			GLCall(glEnableVertexAttribArray(3));
			GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(RenderableSquareVertex), (const GLvoid*)offsetof(RenderableSquareVertex, RenderableSquareVertex::position)));
			GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(RenderableSquareVertex), (const GLvoid*)offsetof(RenderableSquareVertex, RenderableSquareVertex::texCoord)));
			GLCall(glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(RenderableSquareVertex), (const GLvoid*)offsetof(RenderableSquareVertex, RenderableSquareVertex::texId)));
			GLCall(glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(RenderableSquareVertex), (const GLvoid*)offsetof(RenderableSquareVertex, RenderableSquareVertex::color)));
		}

		static uint GetVertexSize()
		{
			return sizeof(RenderableSquareVertex);
		}

		void Draw(BatchRenderer2D<RenderableSquare>* renderer, void** pointer) const;
		inline void SetVertex(RenderableSquareVertex** bufferPointer, const Vec2& pos, const Vec2& texCoord, uint color, float texId) const;
		uint GetVertexCount() const;
	};
}