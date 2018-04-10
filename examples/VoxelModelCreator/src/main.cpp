#include <Greet.h>

#include <graphics/renderers/GUIRenderer.h>
#include <random>

#include "Grid.h"

using namespace Greet;
namespace vmc 
{
	class Core : public App, public KeyListener, public MouseListener, public OnClickListener
	{
	private:
		Layer* uilayer;
		Renderable2D* cursor;
		GUILayer* guilayer;
		Button* saveButton;
		Button* loadButton;
		Button* exportButton;
		TextBox* fileNameBox;

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
			TextureManager::Add(new Texture2D("res/textures/guimask.png", "guimask"));
			TextureManager::Add(new CubeMap("res/textures/skybox.png", "skybox"));
			FontManager::Add(new FontContainer("Anonymous Pro.ttf", "anonymous"));

			cursor = new Renderable2D(Vec2(0, 0), Vec2(32, 32), 0xffffffff, new Sprite(TextureManager::Get2D("cursor")), new Sprite(TextureManager::Get2D("mask")));
			uilayer = new Layer(new BatchRenderer(), ShaderFactory::DefaultShader(), Mat3::Orthographic(0.0f, (float)Window::GetWidth(), 0.0f, (float)Window::GetHeight()));
			uilayer->Add(cursor);
			guilayer = new GUILayer(new GUIRenderer(), Shader::FromFile("res/shaders/gui.shader"));
			ColorPicker* colorPicker = new ColorPicker(Vec2(0, 0), 200, 16, 20);
			fileNameBox = new TextBox(Vec2(0, 210), Vec2(200, 30), false);
			saveButton = new Button(Vec2(0, 250), Vec2(200, 30), "Save file");
			saveButton->AddOnClickListener(this);
			loadButton = new Button(Vec2(0, 290), Vec2(200, 30), "Load file");
			loadButton->AddOnClickListener(this);
			exportButton = new Button(Vec2(0, 330), Vec2(200, 30), "Load file");
			exportButton->AddOnClickListener(this);
			Frame* frame = new Frame(Vec2(0, 0), Vec2(0, 0), "Menu");
			fileNameBox->SetText("test.vox");
			frame->Add(colorPicker);
			frame->Add(fileNameBox);
			frame->Add(saveButton);
			frame->Add(loadButton);
			frame->Add(exportButton);
			frame->Pack();

			guilayer->Add(frame);

			grid = new Grid(colorPicker);
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
			guilayer->Update(elapsedTime);
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
			guilayer->Render();
		}

		void WindowResize(int width, int height) override
		{
			uilayer->SetProjectionMatrix(Mat3::Orthographic(0, width, 0, height));
		}

		void JoystickState(uint joy, bool connected) override
		{

		}

		void OnClick(GUI* gui)
		{
			if (gui == saveButton)
			{
				Log::Info("Saving...");
				grid->SaveModel(fileNameBox->GetText());
				Log::Info("Done!");
			}
			else if (gui == loadButton)
			{
				Log::Info("Loading...");
				grid->LoadModel(fileNameBox->GetText());
				Log::Info("Done!");
			}
			else if(gui == exportButton)
			{
				Log::Info("Exporting...");
				grid->ExportModel(fileNameBox->GetText());
				Log::Info("Done!");
			}
		}
	};
}
#include <fstream>
int main()
{
	vmc::Core game;
	game.Start();
}
