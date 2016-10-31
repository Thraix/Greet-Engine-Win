#pragma once

#include <vector>
#include <math/maths.h>
#include <graphics/fonts/font.h>
#include <logging/logger.h>
#include <graphics/renderers/renderer.h>
#include <graphics/sprite.h>

namespace greet{ namespace graphics{

	class Renderable;
	class Renderable2D;
	class Renderable4Poly;
	class RenderablePoly;
	class Label;

	class Renderer2D : public Renderer
	{
	public:
		virtual ~Renderer2D() {}
		virtual void begin() {}
		virtual void flush() = 0;
		virtual void end() {}

		virtual void submit(const Renderable2D *renderable) = 0;
		virtual void submit(const RenderablePoly *renderable) = 0;
		virtual void submit(const math::Transform& transform, uint texID, math::vec2 texPos, math::vec2 texSize, uint color, uint maskTexId, const math::vec2& maskTexPos, const math::vec2& maskTexSize) = 0;
		virtual void submit(const math::vec2& position, const math::vec2& size, uint texID, math::vec2 texPos, math::vec2 texSize, uint color, uint maskTexId, const math::vec2& maskTexPos, const math::vec2& maskTexSize) = 0;
		virtual void submitString(const std::string& text, const math::vec2& position, Font* font, const uint& color) = 0;

		virtual void drawRect(const math::vec2& position, const math::vec2& size, const uint& color) = 0;
		virtual void fillRect(const math::vec2& position, const math::vec2& size, const uint& color) = 0;
		virtual void fillRect(const math::vec2& position, const math::vec2& size, const uint& color, const Sprite* mask) = 0;
	};
}}
