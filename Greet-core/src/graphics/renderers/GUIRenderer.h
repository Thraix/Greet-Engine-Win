#pragma once

#include <graphics/renderers/Renderer.h>
#include <graphics/fonts/Font.h>
#include <internal/greetgl.h>
#include <math/Vec4.h>
#include <stack>

namespace Greet
{
	class GUI;



	class GUIRenderer : public Renderer
	{
		struct GUIVertex
		{
			Vec2 pos;
			Vec2 texCoord;
			float texId;
			uint color;
			Vec4 viewport;
		};

	private:
		std::stack<Vec4> m_viewports;
		uint m_bufferSize;
		uint m_iboSize;
		uint m_vertices;


		uint m_ibo;
		uint m_vbo;
		uint m_vao;
		uint m_lastIndex;
		uint* m_indices;
		uint m_iboCount;
		GUIVertex* m_buffer;
		GUIVertex* m_bufferBegin;

		uint* m_textures;
		byte m_textureCount;

	public:
		GUIRenderer();
		void Begin();
		void End();
		void Flush();
		void Draw();
		void SubmitString(const std::string& text, const Vec2& position, Font* font, const uint& color);
		void SubmitRect(const Vec2& pos, const Vec2& size, uint color);

		void PushViewport(const Vec2& pos, const Vec2& size, bool overwrite=false);
		void PopViewport();
	private:
		float GetTextureSlot(uint Id);
		bool NeedFlush(uint indices, uint vertices);
		void AppendQuad(const Vec2& position, const Vec2& size, const Vec2& texCoord1, const Vec2& texCoord2, float texID, uint color);
		void AppendVertexBuffer(const Vec2& position, const Vec2& texCoord, float texID, uint color, const Vec4& viewport);
	};
}