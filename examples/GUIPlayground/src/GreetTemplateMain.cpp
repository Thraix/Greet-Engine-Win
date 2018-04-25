#include <Greet.h>

using namespace Greet;

class Core : public App, public KeyListener, public MouseListener, public OnClickListener
{
private:

public:

	Core::~Core()
	{

	}

	void Init() override
	{
		CreateWindow("GreetTemplateMain", 960, 540);
		SetFrameCap(144);

	}
	void Tick() override
	{
		std::string s = StringUtils::to_string(GetFPS()) + " fps | " + StringUtils::to_string(GetUPS()) + " ups";
		Window::SetTitle("GreetTemplateMain | " + s);
	}

	void Update(float elapsedTime) override
	{

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

	void Render() override
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
