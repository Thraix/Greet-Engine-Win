#include <Greet.h>

#include <graphics/renderers/GUIRenderer.h>
#include <random>

using namespace Greet;

class Core : public App, public KeyListener, public MouseListener
{
private:
	BatchRenderer3D* renderer3d;
	Layer* uilayer;

	Mat3 orthographic;
	GUIRenderer* guirenderer;

	TPCamera* camera;
	Renderable2D* cursor;

	EntityModel * cursor3d;

public:
	
	Core::~Core()
	{
		delete renderer3d;
	}

	void Init() override
	{
		EventDispatcher::AddKeyListener(DISPATCHER_GUI+1, *this);
		EventDispatcher::AddMouseListener(DISPATCHER_GUI + 1, *this);
		CreateWindow("Voxel Model Creator", 960, 540);
		SetFrameCap(144);

		// Load Textures and Fonts.
		TextureManager::Add(new Texture2D("res/textures/cursor.png", "cursor"));
		TextureManager::Add(new Texture2D("res/textures/mask.png", "mask"));
		TextureManager::Add(new CubeMap("res/textures/skybox.png", "skybox"));
		FontManager::Add(new FontContainer("Anonymous Pro.ttf", "anonymous"));

		Shader* shader = Shader::FromFile("res/shaders/3dshader.shader");
		Material* material = new Material(shader, NULL);
		MeshData* meshData = MeshFactory::Cube(0, 0, 0, 1, 1, 1);
		uint colors[8];

		colors[0] = 0xff000000;
		colors[1] = 0xff00ff00;
		colors[2] = 0xff00ffff;
		colors[3] = 0xff0000ff;
					
		colors[4] = 0xffff0000;
		colors[5] = 0xffffff00;
		colors[6] = 0xffffffff;
		colors[7] = 0xffff00ff;
		meshData->AddAttribute(new AttributeData(ATTRIBUTE_COLOR, colors));
		Mesh* mesh = new Mesh(meshData);
		mesh->SetEnableCulling(false);
		MaterialModel* materialModel = new MaterialModel(mesh, *material);

		cursor3d = new EntityModel(*materialModel, Vec3(0, 0, 0), Vec3(1.0f, 1.0f, 1.0f), Vec3(0, 0, 0));
		orthographic = Mat3::Orthographic(0.0f, (float)Window::GetWidth(), 0.0f, (float)Window::GetHeight());
		uilayer = new Layer(new BatchRenderer(), ShaderFactory::DefaultShader(), orthographic);
		cursor = new Renderable2D(Vec2(0, 0), Vec2(32, 32), 0xffffffff, new Sprite(TextureManager::Get2D("cursor")), new Sprite(TextureManager::Get2D("mask")));
		uilayer->Add(cursor);

		camera = new TPCamera(Vec3(0, 0, 0), 15, 0, 0, 15, 80, 0, 0.8f);
		Skybox* skybox = new Skybox(TextureManager::Get3D("skybox"));
		renderer3d = new BatchRenderer3D(Window::GetWidth(), Window::GetHeight(), camera,90,0.1f,1000.0f, skybox);
		renderer3d->Submit(cursor3d);

		guirenderer = new GUIRenderer();

		RenderEngine::AddLayer2d(uilayer, "uilayer");
		RenderEngine::AddLayer3d(new Layer3D(renderer3d), "3dlayer");
	}

	void Tick() override
	{
		std::string s = StringUtils::to_string(GetFPS()) + " fps | " + StringUtils::to_string(GetUPS())+ " ups";
		Window::SetTitle("Best Game Ever | " + s);
	}
	float d = 0;
	void Update(float elapsedTime) override
	{
		Vec3 near, direction;
		renderer3d->GetWorldCoordination(Window::GetMousePos(), &near, &direction);
		cursor3d->SetPosition(near+direction * d* 0.001f);
		cursor3d->Update(elapsedTime);
	}

	bool OnPressed(const KeyPressedEvent& e) override
	{
		if (e.GetButton() == GLFW_KEY_F10)
		{
			Utils::Screenshot(Window::GetWidth(), Window::GetHeight());
		}
		if (e.GetButton() == GLFW_KEY_X)
		{
			Vec3 p = renderer3d->GetScreenCoordination(Vec3(0,0,0),Window::GetWidth(),Window::GetHeight());
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
		
	}
	
	void WindowResize(int width, int height) override
	{
		uilayer->SetProjectionMatrix(Mat3::Orthographic(0,width,0,height));
	}

	void JoystickState(uint joy, bool connected) override
	{

	}
};

#include <fstream>
int main()
{
	Core game;
	game.Start();
}
