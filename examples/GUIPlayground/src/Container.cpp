#include "Container.h"

using namespace Greet;

byte Container::RESIZING_LEFT = BIT(0);
byte Container::RESIZING_RIGHT = BIT(1);
byte Container::RESIZING_TOP = BIT(2);
byte Container::RESIZING_BOTTOM = BIT(3);
uint Container::RESIZING_MARGIN = 5;

Container::Container(const Vec2& pos, const Vec2& size, Content* content)
	: pos(pos), size(size), content(content)
{
	
	m_resizableFlags = RESIZING_LEFT | RESIZING_RIGHT | RESIZING_TOP | RESIZING_BOTTOM;
	m_stayInsideWindow = true;
	leftMargin = 10;
	rightMargin = 10;
	topMargin = 10;
	bottomMargin = 10;
	m_minSize = Vec2(100, 100);
}

void Container::PreRender(GUIRenderer* renderer) const
{
	renderer->PushViewport(pos, size, false);
}

void Container::Render(GUIRenderer* renderer) const
{
	// Frame around Container
	renderer->SubmitRect(pos, size, Vec4(0,0,0.5,1), true);
	// Container content
	renderer->SubmitRect(pos+1,size-2,ColorUtils::GetMaterialColorAsHSV(0.5,5),true);
	// Render the content
	content->Render(renderer, pos + GetContentPosition());
}


void Container::PostRender(GUIRenderer* renderer) const
{
	renderer->PopViewport();
}


void Container::Update(float timeElapsed)
{
	content->Update(timeElapsed);
}


bool Container::CheckResize(const Vec2& mousePos)
{
	m_resizingFlags = 0;
	if (m_resizableFlags | RESIZING_LEFT != 0 && mousePos.x >= pos.x - RESIZING_MARGIN && mousePos.x < pos.x + RESIZING_MARGIN)
	{
		m_resizingFlags |= RESIZING_LEFT;
	}
	else if (m_resizableFlags | RESIZING_RIGHT != 0 && mousePos.x >= pos.x + size.x - RESIZING_MARGIN && mousePos.x < pos.x + size.x + RESIZING_MARGIN)
	{
		m_resizingFlags |= RESIZING_RIGHT;
	}
	if (m_resizableFlags | RESIZING_TOP != 0 && mousePos.y >= pos.y - RESIZING_MARGIN && mousePos.y < pos.y + RESIZING_MARGIN)
	{
		m_resizingFlags |= RESIZING_TOP;
	}
	else if (m_resizableFlags | RESIZING_BOTTOM != 0 && mousePos.y >= pos.y + size.y - RESIZING_MARGIN && mousePos.y < pos.y + size.y + RESIZING_MARGIN)
	{
		m_resizingFlags |= RESIZING_BOTTOM;
	}
	m_resizing = m_resizingFlags != 0;
	return m_resizing;
}

void Container::Resize(const Greet::Vec2& mousePos)
{
	Vec2 diff = m_posOrigin - (m_clickPos - mousePos);
	if (m_resizingFlags & RESIZING_LEFT)
	{
		pos.x = m_posOrigin.x - (m_clickPos.x - mousePos.x);
		size.x = m_sizeOrigin.x + (m_clickPos.x - mousePos.x);
		if (size.x < m_minSize.x)
		{
			pos.x = m_posOrigin.x + (m_sizeOrigin.x - m_minSize.x);
			size.x = m_minSize.x;
		}
	}
	else if (m_resizingFlags & RESIZING_RIGHT)
	{
		size.x = m_sizeOrigin.x - (m_clickPos.x - mousePos.x);
		if (size.x < m_minSize.x)
			size.x = m_minSize.x;
	}
	if (m_resizingFlags & RESIZING_TOP)
	{
		pos.y = m_posOrigin.y - (m_clickPos.y - mousePos.y);
		size.y = m_sizeOrigin.y + (m_clickPos.y - mousePos.y);
		if (size.y < m_minSize.y)
		{
			pos.y = m_posOrigin.y + (m_sizeOrigin.y - m_minSize.y);
			size.y = m_minSize.y;
		}
	}
	else if (m_resizingFlags & RESIZING_BOTTOM)
	{
		size.y = m_sizeOrigin.y - (m_clickPos.y - mousePos.y);
		if (size.y < m_minSize.y)
			size.y = m_minSize.y;
	}
	ResizeScreenClamp();
}

void Container::ResizeScreenClamp()
{
	if (m_stayInsideWindow)
	{
		if (pos.x < 0)
		{
			pos.x = 0;
			size.x = m_posOrigin.x + m_sizeOrigin.x;
		}
		else if (pos.x > Window::GetWidth() - size.x)
		{
			size.x = Window::GetWidth() - m_posOrigin.x;
		}
		if (pos.y < 0)
		{
			pos.y = 0;
			size.y = m_posOrigin.y + m_sizeOrigin.y;
		}
		else if (pos.y > Window::GetHeight() - size.y)
			size.y = Window::GetWidth() - m_posOrigin.y;
	}
}

void Container::SetMargins(float left, float right, float top, float bottom)
{
	leftMargin = left;
	rightMargin = right;
	topMargin = top;
	bottomMargin = bottom;
}
	 
bool Container::OnPressed(const MousePressedEvent& event)
{
	if (AABBUtils::PointInsideBox(event.GetPosition(), pos - RESIZING_MARGIN, size + 2 * RESIZING_MARGIN))
	{
		if (event.GetButton() == GLFW_MOUSE_BUTTON_1)
		{
			m_posOrigin = pos;
			m_sizeOrigin = size;
			m_clickPos = event.GetPosition();
			if (CheckResize(event.GetPosition()))
			{
				return true;
			}
		}

		if (AABBUtils::PointInsideBox(event.GetPosition(), pos+GetContentPosition(), GetContentSize()))
		{
			if (content->OnPressed(event, event.GetPosition() - GetContentPosition()) && !hasFocusedContent)
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
