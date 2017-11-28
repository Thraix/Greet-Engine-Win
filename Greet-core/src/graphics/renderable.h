#pragma once

#include <graphics/renderers/Renderer2D.h>

namespace Greet {
	class Renderable
	{
	public:

		bool render = true;

		Renderable()
		{

		}

		virtual ~Renderable()
		{

		}
		virtual void begin(Renderer2D* renderer) const {}
		virtual void submit(Renderer2D* renderer) const = 0;
		virtual void end(Renderer2D* renderer) const {}

		virtual bool update(float timeElapsed) = 0;

		virtual void setColor(uint color) = 0;
		virtual inline uint getColor() const = 0;
		virtual void setPosition(const vec2& pos) = 0;
		virtual inline const vec2& getPosition() const = 0;
		virtual void setSize(const vec2& size) = 0;
		virtual inline const vec2& getSize() const = 0;
	};
}
