#pragma once

#include <greet_types.h>
#include <math\maths.h>

namespace greet { namespace graphics {

	class GUI;

	class Layout
	{

	public:

	protected:
		GUI* gui;
	public:
		virtual void update(math::vec2 size) = 0;

	protected:

	};
}}