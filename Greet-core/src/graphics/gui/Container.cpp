#include "Container.h"

#include "GUIUtils.h"
#include <utils/Utils.h>
#include <utils/AABBUtils.h>

namespace Greet {

	byte Container::RESIZING_LEFT = BIT(0);
	byte Container::RESIZING_RIGHT = BIT(1);
	byte Container::RESIZING_TOP = BIT(2);
	byte Container::RESIZING_BOTTOM = BIT(3);
	uint Container::RESIZING_MARGIN = 5;

	Container::Container()
		: Container(Vec2(0, 0), Vec2(100, 100), new Content())
	{

	}

	Container::Container(const XMLObject& object)
		: xmlObject(object.GetStrippedXMLObject())
	{
		m_resizableFlags = RESIZING_LEFT | RESIZING_RIGHT | RESIZING_TOP | RESIZING_BOTTOM;
		content = new Content();
		backgroundColor = Vec4(1, 1, 1, 1);
		minSize = size = Vec2(100, 100);
		marginTop = marginLeft = marginBottom = marginRight = 10;
		borderTop = borderLeft = borderBottom = borderRight = 0;
		if (object.HasProperty("spacing"))
		{
			content->SetSpacing(GUIUtils::CalcSize(object.GetProperty("spacing"), Window::GetHeight()));
		}
		if (object.HasProperty("width"))
		{
			size.w = GUIUtils::CalcSize(object.GetProperty("width"), Window::GetWidth());
		}
		if (object.HasProperty("height"))
		{
			size.h = GUIUtils::CalcSize(object.GetProperty("height"), Window::GetHeight());
		}
		if (object.HasProperty("minWidth"))
		{
			minSize.x = GUIUtils::CalcSize(object.GetProperty("minWidth"), Window::GetWidth());
		}
		if (object.HasProperty("minHeight"))
		{
			minSize.y = GUIUtils::CalcSize(object.GetProperty("minHeight"), Window::GetHeight());
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
			marginTop = GUIUtils::CalcSize(object.GetProperty("marginTop"), Window::GetHeight());
		}
		if (object.HasProperty("marginLeft"))
		{
			marginLeft = GUIUtils::CalcSize(object.GetProperty("marginLeft"), Window::GetWidth());
		}
		if (object.HasProperty("marginBottom"))
		{
			marginBottom = GUIUtils::CalcSize(object.GetProperty("marginBottom"), Window::GetHeight());
		}
		if (object.HasProperty("marginRight"))
		{
			marginRight = GUIUtils::CalcSize(object.GetProperty("marginRight"), Window::GetWidth());
		}
		if (object.HasProperty("borderTop"))
		{
			borderTop = GUIUtils::CalcSize(object.GetProperty("borderTop"), Window::GetHeight());
		}
		if (object.HasProperty("borderLeft"))
		{
			borderLeft = GUIUtils::CalcSize(object.GetProperty("borderLeft"), Window::GetWidth());
		}
		if (object.HasProperty("borderBottom"))
		{
			borderBottom = GUIUtils::CalcSize(object.GetProperty("borderBottom"), Window::GetHeight());
		}
		if (object.HasProperty("borderRight"))
		{
			borderRight = GUIUtils::CalcSize(object.GetProperty("borderRight"), Window::GetWidth());
		}
		if (object.HasProperty("backgroundColor"))
		{
			backgroundColor = GUIUtils::GetColor(object.GetProperty("backgroundColor"));
		}
		if (object.HasProperty("borderColor"))
		{
			borderColor = GUIUtils::GetColor(object.GetProperty("borderColor"));
		}
		content->SetMargins(0, 0, 0, 0);
		content->SetSize(GetContentSize());
		pos = Vec2(0, 0);
		for (int i = 0;i < object.GetObjectCount();i++)
		{
			content->AddContent(GUIUtils::GetContent(object.GetObject(i), content));
		}
	}

	Container::Container(const Vec2& pos, const Vec2& size, Content* content)
		: pos(pos), size(size), content(content), xmlObject(XMLObject())
	{
		// Allow resizing in all directions
		m_resizableFlags = RESIZING_LEFT | RESIZING_RIGHT | RESIZING_TOP | RESIZING_BOTTOM;
		m_stayInsideWindow = true;
		marginLeft = 10;
		marginRight = 10;
		marginTop = 10;
		marginBottom = 10;
		minSize = Vec2(100, 100);
	}

	Container::~Container()
	{
		delete content;
	}

	void Container::PreRender(GUIRenderer* renderer) const
	{
		renderer->PushViewport(pos, size, false);
	}

	void Container::Render(GUIRenderer* renderer) const
	{
		// Frame around Container
		renderer->SubmitRect(pos, size, borderColor, false);
		// Container content
		renderer->SubmitRect(pos + Vec2(borderLeft, borderTop), size - Vec2(borderLeft + borderRight, borderTop + borderBottom), backgroundColor, false);
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

	void Container::Resize(const Vec2& mousePos)
	{
		Vec2 diff = m_posOrigin - (m_clickPos - mousePos);
		if (m_resizingFlags & RESIZING_LEFT)
		{
			pos.x = m_posOrigin.x - (m_clickPos.x - mousePos.x);
			size.x = m_sizeOrigin.x + (m_clickPos.x - mousePos.x);
			if (size.x < minSize.x)
			{
				pos.x = m_posOrigin.x + (m_sizeOrigin.x - minSize.x);
				size.x = minSize.x;
			}
		}
		else if (m_resizingFlags & RESIZING_RIGHT)
		{
			size.x = m_sizeOrigin.x - (m_clickPos.x - mousePos.x);
			if (size.x < minSize.x)
				size.x = minSize.x;
		}
		if (m_resizingFlags & RESIZING_TOP)
		{
			pos.y = m_posOrigin.y - (m_clickPos.y - mousePos.y);
			size.y = m_sizeOrigin.y + (m_clickPos.y - mousePos.y);
			if (size.y < minSize.y)
			{
				pos.y = m_posOrigin.y + (m_sizeOrigin.y - minSize.y);
				size.y = minSize.y;
			}
		}
		else if (m_resizingFlags & RESIZING_BOTTOM)
		{
			size.y = m_sizeOrigin.y - (m_clickPos.y - mousePos.y);
			if (size.y < minSize.y)
				size.y = minSize.y;
		}
		ResizeScreenClamp();
		content->SetSize(GetContentSize());
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

	void Container::OnWindowResize(int width, int height)
	{
		if (xmlObject.HasProperty("width"))
		{
			const std::string& w = xmlObject.GetProperty("width");
			if (!GUIUtils::IsStaticSize(w))
			{
				size.w = GUIUtils::CalcSize(w, width);
			}
		}
		if (xmlObject.HasProperty("height"))
		{
			const std::string& h = xmlObject.GetProperty("height");
			if (!GUIUtils::IsStaticSize(h))
			{
				size.h = GUIUtils::CalcSize(h, height);
			}
		}
		content->SetSize(GetContentSize());
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

			if (AABBUtils::PointInsideBox(event.GetPosition(), pos + GetContentPosition(), GetContentSize()))
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
		if (hasFocusedContent)
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
}
