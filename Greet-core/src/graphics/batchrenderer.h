#pragma once

#include "renderer2d.h"
#include <greet_types.h>

#include "renderable2d.h"
#include "renderablepoly.h"
#include "renderable4poly.h"
#include "label.h"
#include "buffers/batchindexbuffer.h"

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
		~BatchRenderer();
		void begin() override;
		void submit(const Renderable2D* renderable) override;
		void submit(const RenderablePoly* renderable) override;
		void submit(const Renderable4Poly* renderable) override;
		void submit(const math::Transform& transformation, uint texID, math::vec2 texPos, math::vec2 texSize, uint color) override;
		void submitString(const Label* label, bool shadow) override;
		inline void draw(const math::Transform& transformation, const math::vec2& texPos, const math::vec2& texSize, const float textureSlot, const uint color);
		inline void draw(const math::vec2& position, const math::vec2* vertices, const uint amount, const uint color);
		float getTextureSlot(const GLuint texID);
		void end() override;
		void flush() override;
		void enableBuffers();
		void disableBuffers();
		void addIndicesPoly(uint poly);
	private:
		void init();
	};
}}