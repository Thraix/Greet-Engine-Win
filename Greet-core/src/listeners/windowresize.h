#pragma once

namespace greet {namespace listener{
	class WindowResizeListener
	{
	public:
		virtual void windowResize(int width, int height) = 0;
	};
}}