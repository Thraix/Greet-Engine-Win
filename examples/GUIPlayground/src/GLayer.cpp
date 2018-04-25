#include "GLayer.h"

std::map<std::string, Container*> GLayer::containers;
GLayer GLayer::instance;

using namespace Greet;

GLayer::GLayer()
{
	focused = NULL;
	EventDispatcher::AddKeyListener(100, *this);
	EventDispatcher::AddMouseListener(100, *this);
}

bool GLayer::OnPressed(const Greet::MousePressedEvent& event)
{
	if (focused != NULL)
	{
		focused->OnFocused();
		focused = NULL;
	}

	for (auto it = containers.rbegin(); it != containers.rend(); ++it)
	{
		if (it->second->OnPressed(event))
		{
			if (it->second != focused)
			{
				focused->OnUnfocused();
			}
			focused = it->second;
			return;
		}
	}
	if (focused != NULL)
	{
		focused->OnUnfocused();
		focused = NULL;
	}
}

void GLayer::OnReleased(const Greet::MouseReleasedEvent& event)
{
	if (focused != NULL)
		focused->OnReleased(event);
}

void GLayer::OnMoved(const Greet::MouseMovedEvent& event)
{
	for (auto it = containers.begin(); it != containers.end(); ++it)
	{
		it->second->OnMoved(event);
	}
}

bool GLayer::OnPressed(const Greet::KeyPressedEvent& event)
{
	if (focused != NULL)
		focused->OnPressed(event);
}

bool GLayer::OnReleased(const Greet::KeyReleasedEvent& event)
{
	if (focused != NULL)
		focused->OnReleased(event);
}

void GLayer::CreateInstance()
{
	instance = GLayer();
}

const GLayer& GLayer::GetInstance()
{
	return instance;
}

void GLayer::DestroyInstance()
{
	// destroy something?
}

void GLayer::Render(GUIRenderer* renderer)
{
	for (auto it = containers.begin(); it != containers.end(); ++it)
	{
		it->second->Render(renderer);
	}
}

void GLayer::Update(float timeElapsed)
{
	for (auto it = containers.begin(); it != containers.end(); ++it)
	{
		it->second->Update(timeElapsed);
	}
}

void GLayer::AddContainer(Container* container, const std::string& name)
{
	if (container == NULL)
	{
		Greet::Log::Warning("Cannot add NULL to containers");
		return;
	}
	containers.emplace(name, container);
}

Container* GLayer::RemoveContainer(const std::string& name)
{
	auto it = containers.find(name);
	containers.erase(it);
	return it->second;	
}

Container* GLayer::RemoveContainer(Container* container)
{
	for (auto it = containers.begin(); it != containers.end();++it)
	{
		if (it->second == container)
		{
			containers.erase(it);
			return container;
		}
	}
	return NULL;
}

Container* GLayer::GetContainer(const std::string& name)
{
	auto it = containers.find(name);
	if (it == containers.end())
		return NULL;
	return it->second;
}
