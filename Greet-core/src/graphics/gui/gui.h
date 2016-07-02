#pragma once

#include <graphics/layers/group.h>
#include <math/maths.h>

#define GUI_DEFAULT_BACKGROUND 0xff444444

namespace greet{ namespace graphics {
	class GUI : public Group
	{
		protected:
			GUI* m_parent;
			Renderable2D* m_background;
			math::vec2 m_position;
		public:
			GUI(const math::vec2& position, const math::vec2& size);
			virtual ~GUI();

			void setPosition(const math::vec2& position);
			void setSize(const math::vec2& size);
			void setBackgroundColor(uint bgColor) { m_background->m_color = bgColor;}
			void renderBackground(bool renderBackground) {m_background->render = renderBackground;}
			bool isInside(const math::vec2& position);
			void add(Renderable* renderable) override;
			virtual math::vec2 getOffsetTL() const { return math::vec2(0,0);}
			virtual math::vec2 getOffsetBR() const { return math::vec2(0,0);}
			math::vec2 getContentSize() const { return m_background->getSize()-getOffsetTL()-getOffsetBR(); }
			const math::vec2& getRealPosition();
			inline const math::vec2& getPosition() const override { return m_position;}
			inline const math::vec2& getSize() const override { return m_background->getSize();}
			inline uint getBackgroundColor() const {return m_background->m_color;}
			inline bool isRenderBackground() const { return m_background->render;}
	};
}}
