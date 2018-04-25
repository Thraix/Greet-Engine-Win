#include "Container.h"

using namespace Greet;

byte Container::RESIZING_LEFT = BIT(0);
byte Container::RESIZING_RIGHT = BIT(1);
byte Container::RESIZING_TOP = BIT(2);
byte Container::RESIZING_BOTTOM = BIT(3);

Container::Container()
	: leftMargin(10), rightMargin(10), topMargin(10), bottomMargin(10)
{

}

void Container::Render(GUIRenderer* renderer) const
{
	content->Render(renderer, pos+Vec2(leftMargin,topMargin));
}

void Container::Update(float timeElapsed)
{
	content->Update(timeElapsed);
}
	 
bool Container::OnPressed(const MousePressedEvent& event)
{
	if (AABBUtils::PointInsideBox(event.GetPosition(), pos - 5, size + 10))
	{
		if (event.GetButton() == GLFW_MOUSE_BUTTON_1)
		{
			CheckResize(event.GetPosition());
			if (m_resizing)
				return true;
		}

		if (AABBUtils::PointInsideBox(event.GetPosition(), pos + Vec2(leftMargin, topMargin), size - Vec2(leftMargin + rightMargin, topMargin + bottomMargin)))
		{
			if (content->OnPressed(event, Vec2(leftMargin, topMargin)) && !hasFocusedContent)
			{
				content->OnFocused();
				hasFocusedContent = true;
			}
		}
		else
		{
			if (hasFocusedContent)
			{
				content->OnUnfocused();
				hasFocusedContent = false;
			}
		}

		return true;
	}
	return false;
}

void Container::OnReleased(const MouseReleasedEvent& event)
{
	if (event.GetButton() == GLFW_MOUSE_BUTTON_1)
	{
		m_resizing = false;
	}
	if(hasFocusedContent)
		content->OnReleased(event, Vec2(leftMargin, topMargin));
}

void Container::OnMoved(const MouseMovedEvent& event)
{
	if (m_resizing)
	{
		Resize(event.GetPosition());
	}
	if (hasFocusedContent)
		content->OnMoved(event, Vec2(leftMargin, topMargin));
}

void Container::OnPressed(const KeyPressedEvent& event)
{
	if (hasFocusedContent)
		content->OnPressed(event);
}

void Container::OnReleased(const KeyReleasedEvent& event)
{
	if (hasFocusedContent)
		content->OnReleased(event);
}
	 
void Container::OnFocused()
{
	// Change the title to be more light, see other windows applications
}

void Container::OnUnfocused()
{
	if (hasFocusedContent)
		content->OnUnfocused();
	// Change the title to be more dark, see other windows applications
}

void Container::CheckResize(const Vec2& mousePos)
{
	if (m_resizable)
	{
		m_resizingFlags = 0;
		if (mousePos.x >= pos.x - 5 && mousePos.x < pos.x + 5)
		{
			m_resizingFlags |= RESIZING_LEFT;
		}
		else if (mousePos.x >= pos.x + size.x - 5 && mousePos.x < pos.x + size.x + 5)
		{
			m_resizingFlags |= RESIZING_RIGHT;
		}
		if (mousePos.y >= pos.y - 5 && mousePos.y < pos.y + 5)
		{
			m_resizingFlags |= RESIZING_TOP;
		}
		else if (mousePos.y >= pos.y + size.y - 5 && mousePos.y < pos.y + size.y + 5)
		{
			m_resizingFlags |= RESIZING_BOTTOM;
		}
		m_resizing = m_resizingFlags != 0;
	}
}

void Container::Resize(const Greet::Vec2& mousePos)
{
	if (m_resizingFlags & RESIZING_LEFT)
	{
		size.x -= pos.x - mousePos.x;
		pos.x = mousePos.x;
	}
	else if (m_resizingFlags & RESIZING_RIGHT)
	{
		size.x = mousePos.x - pos.x;
	}
	if (m_resizingFlags & RESIZING_TOP)
	{
		size.y -= pos.y - mousePos.y;
		pos.y = mousePos.y;
	}
	else if (m_resizingFlags & RESIZING_BOTTOM)
	{
		size.y = mousePos.y - pos.y;
	}
}
