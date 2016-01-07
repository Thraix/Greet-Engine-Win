#pragma once

#include "renderable2d.h"
#include "renderable4poly.h"
#include "label.h"
#include "buffers/batchindexbuffer.h"

#define RENDERER_MAX_TEXTURES	32
#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX			0x00
#define SHADER_TEXCOORD_INDEX		0x01
#define SHADER_TEXID_INDEX			0x02
#define SHADER_COLOR_INDEX			0x03
#define SHADER_SELF_VERTEX_INDEX	0x04

#define VERTEX_TOP_LEFT				math::vec2(0,0)
#define VERTEX_TOP_RIGHT			math::vec2(1,0)
#define VERTEX_DOWN_RIGHT			math::vec2(1,1)
#define VERTEX_DOWN_LEFT			math::vec2(0,1)


namespace greet{ namespace graphics{
	class BatchRendererSquare : public Renderer2D
	{
	private:
		BatchIndexBuffer* m_ibo;
		GLuint m_vbo;
		GLuint m_vao;
		VertexData* m_buffer;

		std::vector<GLuint> m_texSlots;

	public:
		BatchRendererSquare();
		~BatchRendererSquare();
		void begin() override;
		void submit(const Renderable2D* renderable) override;
		void submit(const RenderablePoly* renderable) override;
		void submit(const Renderable4Poly* renderable) override;
		void submit(const math::Transform& transformation, uint texID, math::vec2 texPos, math::vec2 texSize, uint color) override;
		void submitString(const Label* label, bool shadow) override;
		inline void draw(const math::vec2& ul, const math::vec2& ur, const math::vec2& dr, const math::vec2& dl, const math::vec2& texPos, const math::vec2& texSize, const float textureSlot, const uint color);
		inline void draw(const math::Transform& transformation, const math::vec2& texPos, const math::vec2& texSize, const float textureSlot, const uint color);
		float getTextureSlot(const GLuint texID);
		void end() override;
		void flush() override;
	private:
		void init();
	};
}}