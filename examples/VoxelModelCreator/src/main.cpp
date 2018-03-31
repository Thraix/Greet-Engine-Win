#include <Greet.h>

#include <graphics/renderers/GUIRenderer.h>
#include <random>

#include "Grid.h"

using namespace Greet;
namespace vmc 
{
	class Core : public App, public KeyListener, public MouseListener
	{
	private:
		Layer* uilayer;
		Renderable2D* cursor;

		Grid* grid;

	public:

		Core::~Core()
		{
		}

		void Init() override
		{
			EventDispatcher::AddKeyListener(DISPATCHER_GUI + 1, *this);
			EventDispatcher::AddMouseListener(DISPATCHER_GUI + 1, *this);
			CreateWindow("Voxel Model Creator", 960, 540);
			SetFrameCap(144);

			// Load Textures and Fonts.
			TextureManager::Add(new Texture2D("res/textures/cursor.png", "cursor"));
			TextureManager::Add(new Texture2D("res/textures/mask.png", "mask"));
			TextureManager::Add(new CubeMap("res/textures/skybox.png", "skybox"));
			FontManager::Add(new FontContainer("Anonymous Pro.ttf", "anonymous"));

			grid = new Grid();
			cursor = new Renderable2D(Vec2(0, 0), Vec2(32, 32), 0xffffffff, new Sprite(TextureManager::Get2D("cursor")), new Sprite(TextureManager::Get2D("mask")));
			uilayer = new Layer(new BatchRenderer(), ShaderFactory::DefaultShader(), Mat3::Orthographic(0.0f, (float)Window::GetWidth(), 0.0f, (float)Window::GetHeight()));
			uilayer->Add(cursor);

			RenderEngine::AddLayer2d(uilayer, "uilayer");
		}

		void Tick() override
		{
			std::string s = StringUtils::to_string(GetFPS()) + " fps | " + StringUtils::to_string(GetUPS()) + " ups";
			Window::SetTitle("Best Game Ever | " + s);
		}
		float d = 0;
		void Update(float elapsedTime) override
		{
			grid->Update(elapsedTime);
		}

		bool OnPressed(const KeyPressedEvent& e) override
		{
			if (e.GetButton() == GLFW_KEY_F10)
			{
				Utils::Screenshot(Window::GetWidth(), Window::GetHeight());
			}
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
			cursor->SetPosition(Vec2(e.GetX(), e.GetY()));
			return false;
		}

		bool OnScroll(const MouseScrollEvent& e) override
		{
			d -= e.GetScroll();
			return false;
		}

		bool screenshot = false;
		void Render() override
		{
			grid->Render();
		}

		void WindowResize(int width, int height) override
		{
			uilayer->SetProjectionMatrix(Mat3::Orthographic(0, width, 0, height));
		}

		void JoystickState(uint joy, bool connected) override
		{

		}
	};
}
#include <fstream>
int main()
{
	vmc::Core game;
	game.Start();
}
