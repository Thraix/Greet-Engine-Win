#pragma once

#include <vector>
#include <math/maths.h>
#include <graphics/fonts/font.h>
#include <logging/log.h>
#include <graphics/renderers/renderer.h>
#include <graphics/sprite.h>

namespace Greet{

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
		virtual void submit(const Transform& transform, uint texID, vec2 texPos, vec2 texSize, uint color, uint maskTexId, const vec2& maskTexPos, const vec2& maskTexSize) = 0;
		virtual void submit(const vec2& position, const vec2& size, uint texID, vec2 texPos, vec2 texSize, uint color, uint maskTexId, const vec2& maskTexPos, const vec2& maskTexSize) = 0;
		virtual void submitString(const std::string& text, const vec2& position, Font* font, const uint& color) = 0;

		virtual void drawRect(const vec2& position, const vec2& size, const uint& color) = 0;
		virtual void fillRect(const vec2& position, const vec2& size, const uint& color) = 0;
		virtual void fillRect(const vec2& position, const vec2& size, const uint& color, const Sprite* mask) = 0;
	};
}
