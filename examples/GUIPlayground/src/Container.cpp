#include "Container.h"

#include "GUIUtils.h"

using namespace Greet;

byte Container::RESIZING_LEFT = BIT(0);
byte Container::RESIZING_RIGHT = BIT(1);
byte Container::RESIZING_TOP = BIT(2);
byte Container::RESIZING_BOTTOM = BIT(3);
uint Container::RESIZING_MARGIN = 5;

Container::Container()
	: Container(Vec2(0,0), Vec2(100,100), new Content())
{

}

Container::Container(const Greet::XMLObject& object)
{
	float w = 100, h = 100; // Default size
	m_resizableFlags = RESIZING_LEFT | RESIZING_RIGHT | RESIZING_TOP | RESIZING_BOTTOM;
	content = new Content();
	marginLeft = 10;
	marginRight = 10;
	marginTop = 10;
	marginBottom = 10;

	if (object.HasProperty("width"))
	{
		w = GUIUtils::CalcXSize(object.GetProperty("width"));
	}
	if (object.HasProperty("height"))
	{
		h = GUIUtils::CalcYSize(object.GetProperty("height"));
	}
	if (object.HasProperty("resizeLeft"))
	{
		if (!GUIUtils::GetBoolean(object.GetProperty("resizeLeft")))
			m_resizableFlags &= ~RESIZING_LEFT;
	}
	if (object.HasProperty("resizeRight"))
	{
		if (!GUIUtils::GetBoolean(object.GetProperty("resizeRight")))
		{
			m_resizableFlags &= ~RESIZING_RIGHT;
		}
	}
	if (object.HasProperty("resizeTop"))
	{
		if (!GUIUtils::GetBoolean(object.GetProperty("resizeTop")))
			m_resizableFlags &= ~RESIZING_TOP;
	}
	if (object.HasProperty("resizeBottom"))
	{
		if (!GUIUtils::GetBoolean(object.GetProperty("resizeBottom")))
			m_resizableFlags &= ~RESIZING_BOTTOM;
	}
	if (object.HasProperty("marginTop"))
	{
		marginTop = GUIUtils::CalcYSize(object.GetProperty("marginTop"));
	}
	if (object.HasProperty("marginLeft"))
	{
		marginLeft = GUIUtils::CalcXSize(object.GetProperty("marginLeft"));
	}
	if (object.HasProperty("marginBottom"))
	{
		marginBottom = GUIUtils::CalcYSize(object.GetProperty("marginBottom"));
	}
	if (object.HasProperty("marginRight"))
	{
		marginRight = GUIUtils::CalcXSize(object.GetProperty("marginRight"));
	}
	Log::Info(Vec4(marginTop,marginLeft,marginBottom, marginRight));
	content->SetMargins(0, 0, 0, 0);
	size = Vec2(w, h);
	pos = Vec2(0, 0);
	for (int i = 0;i < object.GetObjectCount();i++)
	{
		content->AddContent(GUIUtils::GetContent(object.GetObject(i)));
	}
}

Container::Container(const Vec2& pos, const Vec2& size, Content* content)
	: pos(pos), size(size), content(content)
{
	// Allow resizing in all directions;
	m_resizableFlags = RESIZING_LEFT | RESIZING_RIGHT | RESIZING_TOP | RESIZING_BOTTOM;
	m_stayInsideWindow = true;
	marginLeft = 10;
	marginRight = 10;
	marginTop = 10;
	marginBottom = 10;
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
	if ((m_resizableFlags & RESIZING_LEFT) != 0 && mousePos.x >= pos.x - RESIZING_MARGIN && mousePos.x < pos.x + RESIZING_MARGIN)
	{
		m_resizingFlags |= RESIZING_LEFT;
	}
	else if ((m_resizableFlags & RESIZING_RIGHT) != 0 && mousePos.x >= pos.x + size.x - RESIZING_MARGIN && mousePos.x < pos.x + size.x + RESIZING_MARGIN)
	{
		m_resizingFlags |= RESIZING_RIGHT;
	}
	if ((m_resizableFlags & RESIZING_TOP) != 0 && mousePos.y >= pos.y - RESIZING_MARGIN && mousePos.y < pos.y + RESIZING_MARGIN)
	{
		m_resizingFlags |= RESIZING_TOP;
	}
	else if ((m_resizableFlags & RESIZING_BOTTOM) != 0 && mousePos.y >= pos.y + size.y - RESIZING_MARGIN && mousePos.y < pos.y + size.y + RESIZING_MARGIN)
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
	marginLeft = left;
	marginRight = right;
	marginTop = top;
	marginBottom = bottom;
}

void Container::SetGUIMouseListener(GUIMouseListener* listener)
{
	m_mouseListener = listener;
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
			if (content->MousePress(event, event.GetPosition() - GetContentPosition(), *m_mouseListener) && !hasFocusedContent)
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
		content->MouseRelease(event, Vec2(marginLeft, marginTop), *m_mouseListener);
}

void Container::OnMoved(const MouseMovedEvent& event)
{
	if (m_resizing)
	{
		Resize(event.GetPosition());
	}
	if (hasFocusedContent)
		content->MouseMove(event, Vec2(marginLeft, marginTop));
}

void Container::OnPressed(const KeyPressedEvent& event)
{
	//if (hasFocusedContent)
	//	content->KeyPress(event);
}

void Container::OnReleased(const KeyReleasedEvent& event)
{
	//if (hasFocusedContent)
	//	content->KeyRelease(event);
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
