#pragma once

namespace Greet {
	class WindowResizeListener
	{
	public:
		virtual void windowResize(int width, int height) = 0;
	};
}