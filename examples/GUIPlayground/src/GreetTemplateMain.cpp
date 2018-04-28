#include <Greet.h>
#include "GLayer.h"
#include "FrameContainer.h"

using namespace Greet;

class Core : public App, public KeyListener, public MouseListener, public OnClickListener
{
private:
	Content* content;
	Container* container;
public:

	Core::~Core()
	{
		GLayer::DestroyInstance();
		delete container;
		delete content;
	}

	void Init() override
	{
		CreateWindow("GreetTemplateMain", 960, 540);
		SetFrameCap(144);
		FontManager::Add(new FontContainer("res/fonts/Anonymous Pro.ttf","anonymous"));
		GLayer::CreateInstance(new GUIRenderer(), Shader::FromFile("res/shaders/gui.shader"));
		content = new Content();
		content->SetMargins(0, 0, 0, 0);
		content->AddContent(new Label("test1", FontManager::Get("anonymous", 24), Vec4(1, 1, 1, 1)));
		content->AddContent(new Label("test2", FontManager::Get("anonymous", 12), Vec4(1, 1, 1, 1)));
		container = new FrameContainer(Vec2(50, 50), Vec2(200, 200), content, "Debugjahsdflkjashdflkajshdflaksjdhf");
		GLayer::AddContainer(container, "Debug");
	}

	void Tick() override
	{
		std::string s = StringUtils::to_string(GetFPS()) + " fps | " + StringUtils::to_string(GetUPS()) + " ups";
		Window::SetTitle("GreetTemplateMain | " + s);
	}

	void Update(float elapsedTime) override
	{
		GLayer::Update(elapsedTime);
	}

	void Render() override
	{
		GLayer::Render();
	}

	void OnPressed(const KeyPressedEvent& e) override
	{
	}

	void OnReleased(const KeyReleasedEvent& e)  override
	{
	}

	void OnTyped(const KeyTypedEvent& e) override
	{
	}

	void OnMoved(const MouseMovedEvent& e) override
	{
	}

	void OnScroll(const MouseScrollEvent& e) override
	{

	}

	void WindowResize(int width, int height) override
	{
	}

	void JoystickState(uint joy, bool connected) override
	{

	}

	void OnClick(GUI* gui)
	{

	}
};

int main()
{
	Core game;
	game.Start();
}