#pragma once

#include "Container.h"
#include <string>
#include <map>
#include <Greet.h>

class GLayer : public Greet::MouseListener, public Greet::KeyListener, public Greet::WindowResizeListener
{
private:
	static std::map<std::string, Container*> containers;
	static GLayer* instance;
	Container* m_focused;
	Greet::GUIRenderer* m_renderer;
	Greet::Shader m_shader;

private:
	GLayer(Greet::GUIRenderer* renderer, const Greet::Shader& shader);
public:

	bool OnPressed(const Greet::MousePressedEvent& event) override;
	void OnReleased(const Greet::MouseReleasedEvent& event) override;
	void OnMoved(const Greet::MouseMovedEvent& event) override;
	void OnPressed(const Greet::KeyPressedEvent& event) override;
	void OnReleased(const Greet::KeyReleasedEvent& event) override;
	void WindowResize(int width, int height) override;


	static void CreateInstance(Greet::GUIRenderer* renderer, const Greet::Shader& shader);
	static GLayer* GetInstance();
	static void DestroyInstance();

	static void Render();
	static void Update(float timeElapsed);

	static void AddContainer(Container* container, const std::string& name);
	static Container* RemoveContainer(const std::string& name);
	static Container* RemoveContainer(Container* container);
	static Container* GetContainer(const std::string& name);

};