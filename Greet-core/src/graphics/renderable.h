#pragma once

#include "renderer2d.h"

namespace greet { namespace graphics {
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
		virtual void submit(Renderer2D* renderer) const = 0;
		virtual bool update(float timeElapsed) = 0;
	};
}}