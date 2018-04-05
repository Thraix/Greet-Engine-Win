#pragma once

#include <graphics/renderers/Renderer.h>
#include <graphics/fonts/Font.h>
#include <internal/GreetGL.h>
#include <math/Vec4.h>
#include <stack>
#include <algorithm>

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
			Vec4 color;
			Vec4 viewport;
			float isHSV;
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
		void SubmitLine(const Vec2& pos, float length, float width, bool vertical, const Vec4& color, bool isHsv);
		void SubmitString(const std::string& text, const Vec2& position, Font* font, const Vec4& color, bool isHsv = true);
		void SubmitTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, const Vec4& color, bool isHsv = true);
		void SubmitRect(const Vec2& pos, const Vec2& size, const Vec4& color, bool isHsv = true);
		void SubmitRect(const Vec2& pos, const Vec2& size, const Vec4& color1, const Vec4& color2, const Vec4& color3, const Vec4& color4, bool isHsv = true);

		void PushViewport(const Vec2& pos, const Vec2& size, bool overwrite=false);
		void PopViewport();
	private:
		float GetTextureSlot(uint Id);
		bool NeedFlush(uint indices, uint vertices);
		Vec4 GetViewport(const Vec2& pos1, const Vec2& pos2) const;
		void AppendTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, const Vec4& color, bool isHsv);
		void AppendQuad(const Vec2& position, const Vec2& size, const Vec2& texCoord1, const Vec2& texCoord2, float texID, const Vec4& color1, const Vec4& color2, const Vec4& color3, const Vec4& color4, bool isHsv);
		void AppendQuad(const Vec2& position, const Vec2& size, const Vec2& texCoord1, const Vec2& texCoord2, float texID, const Vec4& color, bool isHsv);
		void AppendVertexBuffer(const Vec2& position, const Vec2& texCoord, float texID, const Vec4& color, const Vec4& viewport, bool isHsv);
	};
}