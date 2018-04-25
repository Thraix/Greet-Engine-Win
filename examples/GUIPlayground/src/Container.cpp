#include "Container.h"

using namespace Greet;

byte Container::RESIZING_LEFT = BIT(0);
byte Container::RESIZING_RIGHT = BIT(1);
byte Container::RESIZING_TOP = BIT(2);
byte Container::RESIZING_BOTTOM = BIT(3);

void Container::Render(GUIRenderer* renderer) const
{
	for (auto it = m_contents.begin(); it != m_contents.end(); ++it)
	{
		(*it)->Render(renderer);
	}
}

void Container::Update(float timeElapsed)
{
	for (auto it = m_contents.begin(); it != m_contents.end(); ++it)
	{
		(*it)->Update(timeElapsed);
	}
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

		float yPos = 0;
		for (auto it = m_contents.rbegin(); it != m_contents.rend(); ++it)
		{
			yPos += 40 + 10; // 40 Height + 10 margin
			(*it)->OnPressed(event, Vec2(0,yPos));
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

	float yPos = 0;
	for (auto it = m_contents.rbegin(); it != m_contents.rend(); ++it)
	{
		yPos += 40 + 10; // 40 Height + 10 margin
		(*it)->OnReleased(event, Vec2(0, yPos));
	}
}

void Container::OnMoved(const MouseMovedEvent& event)
{
	if (m_resizing)
	{
		Resize(event.GetPosition());
	}

	float yPos = 0;
	for (auto it = m_contents.rbegin(); it != m_contents.rend(); ++it)
	{
		yPos += 40 + 10; // 40 Height + 10 margin
		(*it)->OnMoved(event, Vec2(0, yPos));
	}
}

bool Container::OnPressed(const KeyPressedEvent& event)
{
	for (auto it = m_contents.rbegin(); it != m_contents.rend(); ++it)
	{
		(*it)->OnPressed(event);
	}
}

bool Container::OnReleased(const KeyReleasedEvent& event)
{
	for (auto it = m_contents.rbegin(); it != m_contents.rend(); ++it)
	{
		(*it)->OnReleased(event);
	}
}
	 
void Container::OnFocused()
{
	
}

void Container::OnUnfocused()
{

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
