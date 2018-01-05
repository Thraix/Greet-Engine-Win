#pragma once

#include <graphics/textures/Texture2D.h>
#include <graphics/AttributePointer.h>
#include <vector>
#include <math/Maths.h>
#include <stack>

#define RENDERER_MAX_TEXTURES	32

namespace Greet {

	class Renderable;

	class BatchRenderer2D
	{
	private:
		std::stack<Mat3> m_transformationStack;

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

		BatchRenderer2D(const std::vector<AttributePointer>& attributes);
		virtual ~BatchRenderer2D();

		void PushMatrix(const Mat3 &matrix, bool override = false);
		void PopMatrix();
		const Mat3& GetTransformationMatrix();

		void Begin();
		void Draw();
		void End();
		void Flush();
		void** GetBufferPointer();
		uint GetVertexSize() const;
		void Submit(const Renderable* square);
		void FillRect(const Vec2& pos, const Vec2& size, uint color);
		void DrawRect(const Vec2& pos, const Vec2& size, uint color);
		bool NeedFlush(uint verticesSize, uint indexCount);
		uint GetTextureSlot(const Texture2D* texture);
		void AddIndicesPoly(uint vertices);
	};
}