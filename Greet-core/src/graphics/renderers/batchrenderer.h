#pragma once
#include <internal/greetgl.h>
#include <graphics/renderers/renderer2d.h>
#include <internal/greet_types.h>

#include <graphics/renderable2d.h>
#include <graphics/renderablepoly.h>
#include <graphics/buffers/batchindexbuffer.h>
#include <logging/log.h>

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

namespace greet {namespace graphics{

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
		void submit(const math::Transform& transform, uint texID, math::vec2 texPos, math::vec2 texSize, uint color, uint maskTexId, const math::vec2& maskTexPos, const math::vec2& maskTexSize) override;
		void submit(const math::vec2& position, const math::vec2& size, uint texID, math::vec2 texPos, math::vec2 texSize, uint color, uint maskTexId, const math::vec2& maskTexPos, const math::vec2& maskTexSize) override;
		void submitString(const std::string& text, const math::vec2& position, Font* font, const uint& color) override;
		inline void draw(const math::Transform& transform, const math::vec2& texPos, const math::vec2& texSize, const uint textureSlot, const uint& color, const uint& maskTexSlot, const math::vec2& maskTexPos, const math::vec2& maskTexSize);
		inline void draw(const math::vec2& position, const math::vec2& size, const math::vec2& texPos, const math::vec2& texSize, const uint textureSlot, const uint color, const uint& maskTexSlot, const math::vec2& maskTexPos, const math::vec2& maskTexSize);
		inline void draw(const math::vec2& position, const math::vec2* vertices, const uint amount, const uint color);
		inline void drawRect(const math::vec2& position, const math::vec2& size, const uint& color) override;
		inline void fillRect(const math::vec2& position, const math::vec2& size, const uint& color) override;
		inline void fillRect(const math::vec2& position, const math::vec2& size, const uint& color, const Sprite* mask) override;
		inline void appendVertexBuffer(const math::vec2& position, const math::vec2& texCoord, const uint& texID, const uint& color, const uint& maskTexId, const math::vec2& maskTexCoord);
		uint getTextureSlot(const GLuint texID);
		void end() override;
		void flush() override;
		void enableBuffers();
		void disableBuffers();
		void addIndicesPoly(uint poly);
	private:
		void init();
	};
}}
