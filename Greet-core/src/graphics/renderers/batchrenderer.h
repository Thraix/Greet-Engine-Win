#pragma once
#include <internal/GreetGL.h>
#include <graphics/renderers/Renderer2D.h>
#include <internal/GreetTypes.h>

#include <graphics/Renderable2D.h>
#include <graphics/RenderablePoly.h>
#include <graphics/buffers/BatchIndexBuffer.h>
#include <logging/Log.h>

#define RENDERER_MAX_TEXTURES	32
#define RENDERER_MAX_SPRITES	360000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX			0x00
#define SHADER_TEXCOORD_INDEX		0x01
#define SHADER_TEXID_INDEX			0x02
#define SHADER_COLOR_INDEX			0x03
#define SHADER_MASK_TEXCOORD_INDEX	0x04
#define SHADER_MASK_TEXID_INDEX		0x05

namespace Greet {

	class BatchRenderer : public Renderer2D
	{

	private:
		uint m_ibo;
		uint m_vbo;
		uint m_vao;
		uint m_iboSize;
		uint m_lastIndex;
		uint* m_indices;
		VertexData* m_buffer;

		std::vector<GLuint> m_texSlots;

	public:
		BatchRenderer();
		virtual ~BatchRenderer();
		void begin() override;
		void submit(const Renderable2D* renderable) override;
		void submit(const RenderablePoly* renderable) override;
		void submit(const Transform& transform, uint texID, vec2 texPos, vec2 texSize, uint color, uint maskTexId, const vec2& maskTexPos, const vec2& maskTexSize) override;
		void submit(const vec2& position, const vec2& size, uint texID, vec2 texPos, vec2 texSize, uint color, uint maskTexId, const vec2& maskTexPos, const vec2& maskTexSize) override;
		void submitString(const std::string& text, const vec2& position, Font* font, const uint& color) override;
		inline void draw(const Transform& transform, const vec2& texPos, const vec2& texSize, const uint textureSlot, const uint& color, const uint& maskTexSlot, const vec2& maskTexPos, const vec2& maskTexSize);
		inline void draw(const vec2& position, const vec2& size, const vec2& texPos, const vec2& texSize, const uint textureSlot, const uint color, const uint& maskTexSlot, const vec2& maskTexPos, const vec2& maskTexSize);
		inline void draw(const vec2& position, const vec2* vertices, const uint amount, const uint color);
		inline void drawRect(const vec2& position, const vec2& size, const uint& color) override;
		inline void fillRect(const vec2& position, const vec2& size, const uint& color) override;
		inline void fillRect(const vec2& position, const vec2& size, const uint& color, const Sprite* mask) override;
		inline void appendVertexBuffer(const vec2& position, const vec2& texCoord, const uint& texID, const uint& color, const uint& maskTexId, const vec2& maskTexCoord);
		uint getTextureSlot(const GLuint texID);
		void end() override;
		void flush() override;
		void enableBuffers();
		void disableBuffers();
		void addIndicesPoly(uint poly);
	private:
		void init();
	};
}
