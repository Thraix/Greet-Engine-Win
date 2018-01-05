#pragma once

#include <graphics/renderables/Renderable.h>
#include <graphics/textures/Texture2D.h>
#include <graphics/Sprite.h>
#include <math/Maths.h>

namespace Greet {
	
	class BatchRenderer2D;

	struct Renderable2DVertex
	{
		Vec2 position;
		Vec2 texCoord;
		float texId;
		uint color;

		static std::vector<AttributePointer> GetAttributePointers()
		{
			std::vector<AttributePointer> pointers;
			pointers.push_back(AttributePointer(0, 2, GL_FLOAT, false, sizeof(Renderable2DVertex), (const GLvoid*)offsetof(Renderable2DVertex, Renderable2DVertex::position)));
			pointers.push_back(AttributePointer(0, 2, GL_FLOAT, false, sizeof(Renderable2DVertex), (const GLvoid*)offsetof(Renderable2DVertex, Renderable2DVertex::texCoord)));
			pointers.push_back(AttributePointer(0, 1, GL_FLOAT, false, sizeof(Renderable2DVertex), (const GLvoid*)offsetof(Renderable2DVertex, Renderable2DVertex::texId)));
			pointers.push_back(AttributePointer(0, 4, GL_UNSIGNED_BYTE, true, sizeof(Renderable2DVertex), (const GLvoid*)offsetof(Renderable2DVertex, Renderable2DVertex::color)));
			return pointers;
		}
	};

	class Renderable2D : public Renderable
	{
	public:
		Vec2 pos;
		Vec2 size;
		uint color;
		Sprite* sprite;

	public:

		Renderable2D(const Vec2& pos, const Vec2& size, uint color)
			: pos(pos), size(size), color(color), sprite(new Sprite())
		{}

		Renderable2D(const Vec2& pos, const Vec2& size, Texture2D* texture, const Vec2& texPos = Vec2(0, 0), const Vec2& texSize = Vec2(1, 1))
			: pos(pos), size(size), color(0xffffffff), sprite(new Sprite(texture, texPos,texSize))
		{}

		Renderable2D(const Vec2& pos, const Vec2& size, Texture2D* texture, uint color, const Vec2& texPos = Vec2(0, 0), const Vec2& texSize = Vec2(1, 1))
			: pos(pos), size(size), color(color), sprite(new Sprite(texture, texPos, texSize))
		{}

		~Renderable2D()
		{
			delete sprite;
		}

		int GetVertexSize() const override { return sizeof(Renderable2DVertex); };
		void Draw(BatchRenderer2D* renderer) const override;
		inline void SetVertex(Renderable2DVertex** bufferPointer, const Vec2& pos, const Vec2& texCoord, uint color, float texId) const;
	};
}