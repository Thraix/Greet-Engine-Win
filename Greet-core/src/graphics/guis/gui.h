#pragma once

#include <managers\fontmanager.h>
#include <graphics\renderer2d.h>
#include <graphics\renderable2d.h>
#include <graphics\shaders\shader.h>
#include "layout.h"
#include <graphics\window.h>
#include <utils\log.h>
#include <utils\uuid.h>
 

namespace greet { namespace graphics {

	class Panel;

	typedef void(*GUI_SELECTED)(GUI* gui, bool selected);
	typedef void(*GUI_RESIZE)(GUI* gui, math::vec2 size);

	class GUI : public Renderable
	{

	friend Window;

	protected:

		GUI_SELECTED f_selected;
		GUI_RESIZE f_guiResized;

		Layout* m_layout;
		Panel* m_panel;

		GUI* m_parent;
		std::vector<GUI*> m_children;
		math::mat3 m_transformationMatrix;
		math::mat3 m_transformation;

		math::vec2 m_pos;
		math::vec2 m_size;

		uint m_bgColor;
		uint m_fgColor;

		bool m_selected;
		bool m_enabled;
		bool m_canSelect;
		bool m_mouseInside;

		math::vec2 m_texPos;
		math::vec2 m_texSize;
		Texture* m_texture;
		bool m_renderbackground;


		uint m_uuid;

		static Font* s_defaultFont;
		static bool s_mouseUsed;



	public:
		GUI(math::vec2 pos, math::vec2 size);
		virtual ~GUI();
		void setPos(math::vec2 pos);
		void resize(math::vec2 size);
		void push(GUI* gui);
		void setPanel();
		void submit(Renderer2D* renderer) const override;
		bool update(float timeElapsed) override;
		bool mouseInside();
		virtual void submitComponents(Renderer2D* renderer) const {}
		virtual void inputComponents(float timeElapsed);
		virtual bool updateComponents(float timeElapsed) { return false; }

		inline uint size() const { return m_children.size(); }

		virtual inline void updateMatrix();
		virtual inline void setBackgroundColor(uint bgColor) { m_bgColor = bgColor; }
		virtual inline void setForegroundColor(uint fgColor) { m_fgColor = fgColor; }

		virtual inline void setSelectedListener(GUI_SELECTED selected) { f_selected = selected; }
		virtual inline void setResizeListener(GUI_RESIZE resized) { f_guiResized = resized; }


		inline math::vec2 getPos() const { return m_pos; }
		inline math::vec2 getSize() const { return m_size; }

		inline const math::mat3& getTranformationMatrix() const { return m_transformationMatrix; }

		inline uint getBackgroundColor() const { return m_bgColor; }
		inline uint getForegroundColor() const { return m_fgColor; }
		inline uint getUUID() const { return m_uuid; }

		inline bool isEnabled() const { return m_enabled; }
		inline bool isSelected() const { return m_selected; }
		inline bool canSelect() const { return m_canSelect; }

		inline const GUI& getParent() const { return *m_parent; }
		inline const std::vector<GUI*>& getChildren() const { return m_children; }


		math::vec2 getMouse() const;

		static void setDefaultFont(std::string fontName) { s_defaultFont = new Font(fontName, fontName); }
		static bool isMouseUsed() { return s_mouseUsed; }
		static const Font& getDefaultFont() { return *s_defaultFont; }

		static void setDefaults(Font* font);
	protected:
		void setParent(GUI* gui);
	private:
		static void updateGUI();
		static void cleanUp();
	};
}}