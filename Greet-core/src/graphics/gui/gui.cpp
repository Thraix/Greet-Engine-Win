#include "gui.h"

namespace greet { namespace graphics {
	
	GUI::GUI(const math::vec2& position, const math::vec2& size)
	:Group(position), m_position(position),m_background(new Renderable2D(math::vec2(0,0),size, GUI_DEFAULT_BACKGROUND, new Sprite())),m_parent(this)
	{
		m_background->render = true;
		Group::add(m_background);
	}
	
	GUI::~GUI()
	{
	}
	
	void GUI::setPosition(const math::vec2& position)
	{
		m_transformationMatrix = math::mat3::translate(position);
		m_position = position;
	}
	
	void GUI::setSize(const math::vec2& size)
	{
		m_background->setSize(size);
	}

	void GUI::add(Renderable* renderable)
	{
		renderable->setPosition(renderable->getPosition()+getOffsetTL());
		Group::add(renderable);
	}

	const math::vec2& GUI::getRealPosition()
	{
		if(m_parent != NULL)
			return m_parent->getPosition()+m_position;
		return m_position;
	}

	bool GUI::isInside(const math::vec2& position)
	{
		return position.x >= m_position.x && m_position.x+m_background->getSize().x > position.x && position.y >= m_position.y && m_position.y+m_background->getSize().y > position.y;
	}
}}
