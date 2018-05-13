#include "Content.h"

using namespace Greet;

Content::Content()
	: leftMargin(0), rightMargin(0), topMargin(0), bottomMargin(0), xSpacing(5), ySpacing(5)
{
	m_isFocusable = false;
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

void Content::AddContent(Content* content)
{
	if (content == NULL)
	{
		Log::Warning("Cannot add NULL to content");
		return;
	}
	m_contents.push_back(content);
}

Content* Content::RemoveContent(uint index)
{
	if (index >= m_contents.size())
	{
		Log::Warning("Index out of bound.");
		return NULL;
	}
	auto it = m_contents.begin() + index;
	m_contents.erase(it);
	return *it;
}

Content* Content::RemoveContent(Content* content)
{
	for (auto it = m_contents.begin(); it != m_contents.end();++it)
	{
		if (*it == content)
		{
			m_contents.erase(it);
			return content;
		}
	}
	Log::Warning("Couldn't find content");
	return NULL;
}

Content* Content::GetContent(uint index)
{
	if (index >= m_contents.size())
	{
		Log::Warning("Index out of bound.");
		return NULL;
	}
	return *(m_contents.begin() + index);
}


bool Content::MousePress(const MousePressedEvent& event, const Vec2& translatedPos, const GUIMouseListener& listener)
{
	float yPos = topMargin;
	for (auto it = m_contents.rbegin(); it != m_contents.rend(); ++it)
	{
		// Translate the mouse.
		Vec2 translatedPosContent = translatedPos - Vec2(leftMargin, yPos);
		if ((*it)->IsMouseInside(translatedPosContent))
		{
			// Check if the contents wants focus.
			(*it)->MousePress(event, translatedPosContent, listener);
			if ((*it)->IsFocusable())
			{
				if (*it == m_focused)
				{
					m_focused->OnUnfocused();
					(*it)->OnFocused();
					m_focused = *it;
				}
				listener.OnMousePressed(*it);
				return true;
			}
		}
		yPos += (*it)->GetHeight() + ySpacing;
	}
	if (m_focused != NULL)
	{
		m_focused->OnUnfocused();
		m_focused = NULL;
	}
	return false;
}

void Content::MouseRelease(const MouseReleasedEvent& event, const Vec2& translatedPos, const GUIMouseListener& listener)
{
	if (m_focused != NULL)
	{
		// Calculate the focused yPos
		float yPos = topMargin;
		for (auto it = m_contents.begin(); it != m_contents.end(); ++it)
		{
			if (m_focused == *it)
			{
				m_focused->MouseRelease(event, translatedPos - Vec2(leftMargin, yPos), listener);
				listener.OnMouseReleased(m_focused);
				if (m_focused->IsMouseInside(translatedPos - Vec2(leftMargin, yPos)))
				{
					listener.OnMouseClicked(m_focused);
				}
			}
			yPos += (*it)->GetHeight() + ySpacing;
		}
	}
}

void Content::MouseMove(const MouseMovedEvent& event, const Vec2& translatedPos) 
{
		// Calculate the focused yPos
		float yPos = topMargin;
		for (auto it = m_contents.begin(); it != m_contents.end(); ++it)
		{
			if (m_focused == *it)
			{
				m_focused->MouseMove(event, translatedPos - Vec2(leftMargin, yPos));
			}
			else if (m_focused == NULL)
			{
				
			}
			yPos += (*it)->GetHeight() + ySpacing;
		}
}

void Content::OnKeyPressed(const KeyPressedEvent& event)
{
	if (m_focused != NULL)
	{
		m_focused->OnKeyPressed(event);
	}
}

void Content::OnKeyReleased(const KeyReleasedEvent& event)
{
	if (m_focused != NULL)
	{
		m_focused->OnKeyReleased(event);
	}
}

bool Content::IsMouseInside(const Vec2& mousePos) const
{
	return AABBUtils::PointInsideBox(mousePos, Vec2(0, 0), GetSize());
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

void Content::SetMargins(float left, float right, float top, float bottom)
{
	leftMargin = left;
	rightMargin = right;
	topMargin = top;
	bottomMargin = bottom;
}