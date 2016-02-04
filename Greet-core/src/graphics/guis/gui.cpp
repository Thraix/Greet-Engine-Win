#include "gui.h"
#include "panel.h"

namespace greet { namespace graphics {

	Font* GUI::s_defaultFont;
	bool GUI::s_mouseUsed;

	GUI::GUI(math::vec2 pos, math::vec2 size)
		: m_guiMatrix(math::Transform().translate(pos)), m_pos(pos), m_size(size),m_transform(math::Transform().translate(pos).scale(size))
	{
		GLint texIDs[32];
		for (int i = 0; i < 32; i++)
		{
			texIDs[i] = i;
		}
		m_bgColor = 0xff000000;
		m_renderbackground = true;
		m_enabled = true;
		m_canSelect = true;
		m_uuid = utils::UUID::getInstance()->getUUID();
	}

	GUI::~GUI()
	{
		uint size = m_children.size();
		for (uint i = 0; i < size; i++)
			delete m_children[i];
		delete m_layout;
	}

	void GUI::setPos(math::vec2 pos)
	{
		m_pos = pos;
		updateMatrix();
	}

	void GUI::resize(math::vec2 size)
	{
		m_size = size;
		m_layout->update(size);
		f_guiResized(this, size);
	}

	void GUI::push(GUI* gui)
	{
		gui->setParent(this);
		m_children.push_back(gui);
		gui->setPanel();
	}

	void GUI::setPanel()
	{
		if (m_parent->m_panel != NULL)
		{
			m_panel = m_parent->m_panel;
			uint size = m_children.size();
			for (int i = 0;i < size;i++)
			{
				m_children[i]->setPanel();
			}
		}
	}

	void GUI::submit(Renderer2D* renderer) const
	{
		if(m_renderbackground)
			renderer->submit(m_transform,0, math::vec2(0, 0), math::vec2(1, 1),m_bgColor);
		submitComponents(renderer);
		renderer->pushMatrix(m_guiMatrix.getMatrix());
		uint size = m_children.size();
		for (uint i = 0; i < size; i++)
			m_children[i]->submit(renderer);
		renderer->popMatrix();

	}

	bool GUI::update(float timeElapsed)
	{
		uint size = m_children.size();
		for (uint i = 0; i < size; i++) {
			m_children[i]->update(timeElapsed);
		}
		if (m_enabled)
		{
			inputComponents(timeElapsed);
		}
		return updateComponents(timeElapsed);
	}

	//Handle all the input
	void GUI::inputComponents(float timeElapsed)
	{
		m_mouseInside = mouseInside();
		if (m_canSelect)
		{
			if (!s_mouseUsed)
			{
				if (Window::isMouseButtonReleased(GLFW_MOUSE_BUTTON_LEFT))
				{
					if (m_mouseInside)
					{
						s_mouseUsed = true;
						m_selected = true;
					}
					else
					{
						m_selected = false;
					}
				}
			}
		}
	}

	bool GUI::mouseInside()
	{
		math::vec2 mouse = getMouse();
		return mouse.x >= m_pos.x && mouse.x < m_pos.x + m_size.x && mouse.y >= m_pos.y && mouse.y < m_pos.y + m_size.y;
	}


	//Updates the transformation matrix to the current position
	void GUI::updateMatrix()
	{
		m_guiMatrix.init().translate(m_pos);
	}

	void GUI::setDefaults(Font * font)
	{
		s_defaultFont = font;
	}

	void GUI::setParent(GUI * gui)
	{
		m_parent = gui;
	}

	math::vec2 GUI::getMouse() const
	{
		// Can't rotate GUI
		//DO I NEED TO FIX?
		if(m_parent!=NULL)
			return m_panel->getInvertedProjectionMatrix() * Window::getMousePos() - m_parent->m_pos;		
		else
			return m_panel->getInvertedProjectionMatrix() * Window::getMousePos();
	}
	void GUI::updateGUI()
	{
		s_mouseUsed = false;
	}

	void GUI::cleanUp()
	{
		
	}


}}
