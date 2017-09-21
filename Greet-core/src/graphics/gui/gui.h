#pragma once

#include <graphics/layers/group.h>
#include <math/maths.h>
#include "ltrb.h"
#include <event/keyevent.h>
#include <event/mouseevent.h>
#include <utils/colorutils.h>
#include <listeners/onclicklistener.h>
#include <algorithm>
#include <graphics/textures/texturemanager.h>

#define MOUSE_INSIDE(mouse,xPos,yPos,width,height) mouse.x >= xPos && mouse.x < xPos + width && mouse.y >= yPos && mouse.y < yPos + height
#define MOUSE_INSIDE_GUI(mouse,width,height) mouse.x >= 0 && mouse.x < width && mouse.y >= 0 && mouse.y < height

#define GUI_DEFAULT_BACKGROUND 0xff444444

namespace Greet{
	class GUI : public Group
	{
		protected:

			GUI* m_parent;
			bool m_mouseInside = false;
			//Renderable2D* m_background;
		public:
			LTRB m_padding;
			LTRB m_margin;
			vec2 m_position;
			vec2 m_size;
			uint m_backgroundColor;
			bool m_renderBackground = true;
			std::vector<OnClickListener*> m_onClickListeners;
			static Sprite* m_mask;


		public:
			GUI(const vec2& position, const vec2& size);
			GUI(const vec2& position, const vec2& size, const LTRB& margin, const LTRB& padding);
			virtual ~GUI();
			void setBackgroundColor(uint bgColor) { m_backgroundColor = bgColor;}
			//void renderBackground(bool renderBackground) {m_background->render = renderBackground;}
			bool update(float timeElapsed) override;

			virtual void submit(Renderer2D* renderer) const override;
			virtual void render(Renderer2D* renderer) const;

			virtual void onMouseEnter() { /*Log::info("mouse entered"); */};
			virtual void onMouseExit() { /*Log::info("mouse exited");*/ };
			virtual bool onPressed(KeyPressedEvent& event);
			virtual bool onReleased(KeyReleasedEvent& event);
			virtual bool onPressed(const MousePressedEvent& event, vec2 relativeMousePos);
			virtual bool onReleased(const MouseReleasedEvent& event, vec2 relativeMousePos);
			virtual bool onMoved(const MouseMovedEvent& event, vec2 relativeMousePos);

			void addOnClickListener(OnClickListener* onClick) { m_onClickListeners.push_back(onClick); };
			void removeOnClickListener(OnClickListener* onClick) { m_onClickListeners.erase(std::remove(m_onClickListeners.begin(), m_onClickListeners.end(),onClick), m_onClickListeners.end()); };

			bool isInside(const vec2& position);
			vec2 getContentSize() const { return m_size -vec2(m_padding.left+m_padding.right,m_padding.top+m_padding.bottom); }
			const vec2& getRealPosition();
			inline const vec2& getPosition() const override { return m_position;}
			inline const vec2& getSize() const override { return m_size;}
			inline uint getBackgroundColor() const {return m_backgroundColor;}
			inline bool isRenderBackground() const { return m_renderBackground;}
	};
}
