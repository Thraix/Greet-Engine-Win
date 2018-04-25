#include "Content.h"

using namespace Greet;

Content::Content()
	: leftMargin(10), rightMargin(10), topMargin(10), bottomMargin(10), xSpacing(10), ySpacing(10)
{
	
}

void Content::Render(GUIRenderer* renderer, const Vec2& position) const
{
	float yPos = topMargin;
	for (auto it = m_contents.begin(); it != m_contents.end(); ++it)
	{
		(*it)->Render(renderer, position+Vec2(leftMargin,yPos));
		yPos += (*it)->GetHeight() + ySpacing;
	}
}

void Content::Update(float timeElapsed)
{
	for (auto it = m_contents.begin(); it != m_contents.end(); ++it)
	{
		(*it)->Update(timeElapsed);
	}
}

bool Content::OnPressed(const MousePressedEvent& event, const Vec2& translatedPos)
{
	if (AABBUtils::PointInsideBox(event.GetPosition(), Vec2(0,0), GetSize()))
	{
		float yPos = topMargin;
		for (auto it = m_contents.rbegin(); it != m_contents.rend(); ++it)
		{
			// Translate the mouse.
			Vec2 translatedPosContent = translatedPos - Vec2(leftMargin, yPos);
			if (AABBUtils::PointInsideBox(translatedPosContent, Vec2(0,0), (*it)->GetSize()))
			{
				// Check if the contents wants focus.
				if ((*it)->OnPressed(event, translatedPosContent))
				{
					if (*it == m_focused)
					{
						m_focused->OnUnfocused();
						(*it)->OnFocused();
						m_focused = *it;
					}
					return true;
				}
			}
			yPos += (*it)->GetHeight() + ySpacing;
		}
	}
	if (m_focused != NULL)
	{
		m_focused->OnUnfocused();
		m_focused = NULL;
	}
	return false;
}

void Content::OnReleased(const MouseReleasedEvent& event, const Vec2& translatedPos)
{
	if (m_focused != NULL)
	{
		// Calculate the focused yPos
		float yPos = topMargin;
		for (auto it = m_contents.begin(); it != m_contents.end(); ++it)
		{
			if (m_focused == *it)
			{
				m_focused->OnReleased(event, translatedPos - Vec2(leftMargin, yPos));
			}
			yPos += (*it)->GetHeight() + ySpacing;
		}
	}
}

void Content::OnMoved(const MouseMovedEvent& event, const Vec2& translatedPos) 
{
	if (m_focused != NULL)
	{
		// Calculate the focused yPos
		float yPos = topMargin;
		for (auto it = m_contents.begin(); it != m_contents.end(); ++it)
		{
			if (m_focused == *it)
			{
				m_focused->OnMoved(event, translatedPos - Vec2(leftMargin, yPos));
			}
			yPos += (*it)->GetHeight() + ySpacing;
		}
	}
}

void Content::OnPressed(const KeyPressedEvent& event)
{
	if (m_focused != NULL)
	{
		m_focused->OnPressed(event);
	}
}

void Content::OnReleased(const KeyReleasedEvent& event)
{
	if (m_focused != NULL)
	{
		m_focused->OnReleased(event);
	}
}

void Content::OnFocused()
{
	
}

void Content::OnUnfocused()
{
	// Unfocus the focused content.
	if (m_focused != NULL)
	{
		m_focused->OnUnfocused();
	}
}

Vec2 Content::GetSize() const
{
	return Vec2(GetWidth(), GetHeight());
}

float Content::GetWidth() const
{
	float width = leftMargin + rightMargin;
	for (auto it = m_contents.begin(); it != m_contents.end(); ++it)
	{
		if (it != m_contents.begin())
			width += xSpacing;
		width += (*it)->GetWidth();
	}
	return width;
}

float Content::GetHeight() const
{
	float maxHeight = 0;
	for (auto it = m_contents.begin(); it != m_contents.end(); ++it)
	{
		maxHeight = Math::Max((*it)->GetHeight(), maxHeight);
	}
	return maxHeight + topMargin + bottomMargin;
}