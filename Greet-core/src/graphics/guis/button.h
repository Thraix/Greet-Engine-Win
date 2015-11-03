#pragma once

#include "textview.h"

namespace greet{ namespace graphics {
	class Button : public GUI
	{
	
		typedef void(*BUTTON_PRESS)(Button* button);
		typedef void(*BUTTON_RELEASE)(Button* button);

	public:

	protected:
		BUTTON_PRESS m_press;
		BUTTON_PRESS m_release;

		TextView* m_textView;
		bool m_pressedInside;

	public:
		Button(math::vec2 pos, math::vec2 size);
		Button(math::vec2 pos, math::vec2 size, std::string text);
		
		~Button()
		{
			
		}

		void submitComponents(Renderer2D* renderer) const override;
		void inputComponents(float timeElapsed) override;
		void setForegroundColor(uint color) override;
		void setPressListener(BUTTON_PRESS press);
		void setReleaseListener(BUTTON_RELEASE release);
	private:
		inline void init();
	};
}}