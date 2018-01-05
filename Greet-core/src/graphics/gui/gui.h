#pragma once

#include <graphics/layers/Group.h>
#include <math/Maths.h>
#include "ltrb.h"
#include <event/KeyEvent.h>
#include <event/MouseEvent.h>
#include <utils/ColorUtils.h>
#include <listeners/OnClickListener.h>
#include <algorithm>
#include <graphics/textures/TextureManager.h>
#include <drivers/DriverAdapter.h>
#include <graphics/Sprite.h>
#include <graphics/renderables/Renderable2D.h>

#define MOUSE_INSIDE(mouse,xPos,yPos,width,height) (mouse).x >= (xPos) && (mouse).x < (xPos) + (width) && (mouse).y >= (yPos) && (mouse).y < (yPos) + (height)
#define MOUSE_INSIDE_GUI(mouse,width,height) (mouse).x >= 0 && (mouse).x < (width) && (mouse).y >= 0 && (mouse).y < (height)

#define GUI_DEFAULT_BACKGROUND 0xff444444

namespace Greet{
	class GUI : public Group
	{
		friend class GUILayer;
		protected:

			GUI* m_parent;

			// Mouse is inside GUI
			bool m_mouseInside = false;
			// Can be focused
			bool m_enabled = true;
			// is the GUI focused
			bool m_focused = false;
			//Renderable2D* m_background;
		public:
			LTRB m_margin;
			Vec2 m_position;
			Vec2 m_size;
			uint m_backgroundColor;
			bool m_renderBackground = true;
			std::vector<OnClickListener*> m_onClickListeners;
			static Sprite* m_mask;
		private:
			void SetFocused(bool focused);

		public:
			GUI(const Vec2& position, const Vec2& size);
			GUI(const Vec2& position, const Vec2& size, const LTRB& margin);
			void Add(Renderable* renderable) override;
			void Add(GUI* renderable);
			virtual ~GUI();
			bool IsFocused() const { return m_focused; }
			void SetBackgroundColor(uint bgColor) { m_backgroundColor = bgColor;}
			bool Update(float timeElapsed) override;

			virtual void Submit(BatchRenderer2D* renderer) const override;
			virtual void Render(BatchRenderer2D* renderer) const;

			virtual void OnFocused(bool focused) {};
			virtual void OnMouseEnter() { };
			virtual void OnMouseExit() { };
			virtual bool OnPressed(const KeyPressedEvent& event);
			virtual bool OnReleased(const KeyReleasedEvent& event);
			virtual bool OnTyped(const KeyTypedEvent& event);
			// Returns the pressed GUI
			virtual GUI* OnPressed(const MousePressedEvent& event, Vec2 relativeMousePos);
			// Returns the released GUI
			virtual GUI* OnReleased(const MouseReleasedEvent& event, Vec2 relativeMousePos);

			virtual bool OnMoved(const MouseMovedEvent& event, Vec2 relativeMousePos);

			void AddOnClickListener(OnClickListener* onClick) { m_onClickListeners.push_back(onClick); };
			void RemoveOnClickListener(OnClickListener* onClick) { m_onClickListeners.erase(std::remove(m_onClickListeners.begin(), m_onClickListeners.end(),onClick), m_onClickListeners.end()); };

			virtual bool IsInside(const Vec2& position) const;
			Vec2 TranslateMouse(const Vec2& mousePos, GUI* target) const;
			const Vec2& GetRealPosition() const;
			inline const Vec2& GetPosition() const { return m_position;}
			inline const Vec2& GetSize() const { return m_size;}
			inline uint GetBackgroundColor() const {return m_backgroundColor;}
			inline bool IsRenderBackground() const { return m_renderBackground;}
	};
}
