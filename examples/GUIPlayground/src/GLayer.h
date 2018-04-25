#pragma once

#include "Container.h"
#include <string>
#include <map>
#include <Greet.h>

class GLayer : public Greet::MouseListener, public Greet::KeyListener
{
private:
	static std::map<std::string, Container*> containers;
	static GLayer instance;
	Container* focused;

private:
	GLayer();
public:

	bool OnPressed(const Greet::MousePressedEvent& event) override;
	void OnReleased(const Greet::MouseReleasedEvent& event) override;
	void OnMoved(const Greet::MouseMovedEvent& event) override;
	bool OnPressed(const Greet::KeyPressedEvent& event) override;
	bool OnReleased(const Greet::KeyReleasedEvent& event) override;


	static void CreateInstance();
	static const GLayer& GetInstance();
	static void DestroyInstance();

	static void Render(Greet::GUIRenderer* renderer);
	static void Update(float timeElapsed);

	static void AddContainer(Container* container, const std::string& name);
	static Container* RemoveContainer(const std::string& name);
	static Container* RemoveContainer(Container* container);
	static Container* GetContainer(const std::string& name);

};