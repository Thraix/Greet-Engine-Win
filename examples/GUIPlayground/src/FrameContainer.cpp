#include "FrameContainer.h"

using namespace Greet;

FrameContainer::FrameContainer(const Greet::Vec2& pos, const Greet::Vec2& size, Content* content, const std::string& title)
	: Container(pos,size,content), header(new Content()), m_shouldDeleteHeader(true)
{
	Label* label = new Label(title, FontManager::Get("roboto", 20), ColorUtils::GetMaterialColorAsHSV(0.75, 2));
	header->AddContent(label);
	header->SetMargins(0, 0,5, 0);
	SetMargins(10,10,0,10);
	headerSize = 30;
	headerSpacing = 10;
	m_movable = true;
	label->maxWidth = size.x - leftMargin - rightMargin;
}

FrameContainer::FrameContainer(const Greet::Vec2& pos, const Greet::Vec2& size, Content* content, Content* header)
	: Container(pos,size,content), header(content), m_shouldDeleteHeader(false)
{
	SetMargins(10, 10, 0, 10);
	headerSize = header->GetHeight();
	headerSpacing = 10;
	m_movable = true;
}

FrameContainer::~FrameContainer()
{
	if (m_shouldDeleteHeader)
		delete header;
}

void FrameContainer::Render(GUIRenderer* renderer) const
{
	Container::Render(renderer);
	renderer->PushViewport(pos+Vec2(leftMargin, topMargin), Vec2(size.x-leftMargin-rightMargin, headerSize),false);
	// Container header.
	renderer->SubmitRect(pos+Vec2(leftMargin, topMargin+headerSize-1), Vec2(size.x-leftMargin-rightMargin, 1), ColorUtils::GetMaterialColorAsHSV(0.5, 2), true);
	// Title
	header->Render(renderer, pos+Vec2(leftMargin, topMargin));
	renderer->PopViewport();
}

bool FrameContainer::CheckMove(const Vec2& mousePos)
{
	if (m_movable)
	{
		if (AABBUtils::PointInsideBox(mousePos, pos, Vec2(size.x, headerSize)))
		{
			m_moving = true;
		}
	}
	return m_moving;
}

void FrameContainer::Move(const Vec2& mousePos)
{
	pos = m_posOrigin - (m_clickPos - mousePos);
	MoveScreenClamp();
}

void FrameContainer::MoveScreenClamp()
{
	if (m_stayInsideWindow)
	{
		if (pos.x < 0)
			pos.x = 0;
		else if (pos.x > Window::GetWidth() - size.x)
			pos.x = Window::GetWidth() - size.x;
		if (pos.y < 0)
			pos.y = 0;
		else if (pos.y > Window::GetHeight() - size.y)
			pos.y = Window::GetHeight() - size.y;
	}
}

bool FrameContainer::OnPressed(const Greet::MousePressedEvent& event)
{
	if (Container::OnPressed(event))
	{
		if (event.GetButton() == GLFW_MOUSE_BUTTON_1)
		{
			if (!m_resizing)
			{
				CheckMove(event.GetPosition());
			}
		}
		return true;
	}
	return false;
}

void FrameContainer::OnReleased(const Greet::MouseReleasedEvent& event)
{
	Container::OnReleased(event);
	if (event.GetButton() == GLFW_MOUSE_BUTTON_1)
	{
		m_moving = false;
	}
}

void FrameContainer::OnMoved(const Greet::MouseMovedEvent& event)
{
	Container::OnMoved(event);
	if (m_moving)
	{
		Move(event.GetPosition());
	}
}
