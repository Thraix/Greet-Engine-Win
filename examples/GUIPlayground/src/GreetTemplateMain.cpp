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

	bool OnPressed(const KeyPressedEvent& e) override
	{
		return false;
	}

	bool OnReleased(const KeyReleasedEvent& e)  override
	{
		return false;
	}

	bool OnTyped(const KeyTypedEvent& e) override
	{
		return false;
	}

	bool OnMoved(const MouseMovedEvent& e) override
	{
		return false;
	}

	bool OnScroll(const MouseScrollEvent& e) override
	{
		return false;
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
