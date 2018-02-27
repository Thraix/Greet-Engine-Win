#include <Greet.h>

#include <graphics/renderers/GUIRenderer.h>
#include "keyboardcontrol.h"
#include "tree.h"
#include <random>

using namespace Greet;

class Core : public App, public KeyListener, public MouseListener
{
private:
	Shader* blurShader;
	BatchRenderer3D* renderer3d;
	Material* modelMaterial;
	Material* terrainMaterial;
	Material* stallMaterial;
	KeyboardControl* movement;
	KeyboardControl* rotation;

	EntityModel* stall;
	EntityModel* dragon;
	EntityModel* grid;
	EntityModel* cube;
	EntityModel* tetrahedron;
	std::vector<EntityModel> models;
	FrameBufferObject* fbo;
	GUIRenderer* guirenderer;


	float progressFloat;

	TPCamera* camera;
	Layer* scene3d;
	Layer* uilayer;
	GUILayer* guilayer;
	Slider* slider;
	Slider* slider2;
	Frame* frame;
	Button* button;
	Label* fps;
	Renderable2D* cursor;
	Renderable2D* driverTest;
	Renderable2D* fboScene;

public:
	
	Core::~Core()
	{
		delete modelMaterial;
		delete stall;
		delete dragon;
		delete grid;
		delete cube;
		delete tetrahedron;
		delete renderer3d;
		delete uilayer;
		delete guilayer;
		delete movement;
		delete rotation;
	}

	void Init() override
	{
		Log::Info("Random UUID: ", UUID::GetInstance().GetUUID());
		EventDispatcher::AddKeyListener(DISPATCHER_GUI+1, *this);
		EventDispatcher::AddMouseListener(DISPATCHER_GUI + 1, *this);
		CreateWindow("Best Game Ever", 960, 540);
		SetFrameCap(144);
		TextureManager::Add(new Texture2D("res/textures/stallTexture.png", "stall"));
		TextureManager::Add(new Texture2D("res/textures/cursor.png", "cursor"));
		TextureManager::Add(new Texture2D("res/textures/mask.png", "mask"));
		TextureManager::Add(new Texture2D("res/textures/mask2.png", "mask2"));
		TextureManager::Add(new CubeMap("res/textures/skybox.png", "skybox"));
		TextureManager::Add(new Texture2D("res/textures/lens_flare1.png", "lensflare1"));
		TextureManager::Add(new Texture2D("res/textures/lens_flare2.png", "lensflare2"));
		TextureManager::Add(new Texture2D("res/textures/lens_flare3.png", "lensflare3"));
		TextureManager::Add(new Texture2D("res/textures/lens_flare4.png", "lensflare4"));
		FontManager::Add(new FontContainer("Anonymous Pro.ttf", "anonymous"));

		fbo = new FrameBufferObject(960,540);
		//camera = new TPCamera(vec3(-3.5, -7.8, 5.5), 18, 0.66, 38.5, 15, 80, 0, 0.8f); // Profile shot
		camera = new TPCamera(Vec3(0, 0, 0), 15, 0, 0, 15, 80, 0, 0.8f);
		Skybox* skybox = new Skybox(TextureManager::Get3D("skybox"));
		renderer3d = new BatchRenderer3D(Window::GetWidth(), Window::GetHeight(), camera,90,0.001f,1000.0f, skybox);

		Shader* modelShader = Shader::FromFile("res/shaders/3dshader.shader");
		Shader* terrainShader = Shader::FromFile("res/shaders/terrain.shader");
		Shader* stallShader = Shader::FromFile("res/shaders/3dshader.shader");
		blurShader = Shader::FromFile("res/shaders/default2dshader.vert","res/shaders/guassianblur.frag");

		modelMaterial = new Material(modelShader, NULL);
		stallMaterial = new Material(stallShader, TextureManager::Get("stall"));
		terrainMaterial = new Material(terrainShader, NULL);
		terrainMaterial->SetReflectivity(0.5f);
		terrainMaterial->SetShineDamper(5.0f);
		uint gridWidth = 999;
		uint gridLength = 999;
		float* noise = Noise::GenNoise(gridWidth+1, gridWidth + 1,5,64, 64,0.5f);
		//noise[0] = 10;
		MeshData* gridMesh = MeshFactory::LowPolyGrid(0, 0, 0, gridWidth+1, gridLength+1, gridWidth, gridLength, noise,1);
		RecalcGrid(gridMesh, gridWidth, gridLength);
		
		//gridMesh->setDefaultAttribute4f(MESH_COLORS_LOCATION, vec4(1.0f, 0.0f, 0.0f, 1.0f));
		//gridMesh->setEnableCulling(false);
		MaterialModel* gridModelMaterial = new MaterialModel(new Mesh(gridMesh), *terrainMaterial);
		grid = new EntityModel(*gridModelMaterial, Vec3(0, -20, 0), Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));
		delete gridMesh;

		MeshData* cubeMesh = MeshFactory::Cube(0,0,0,10,10,10);
		MaterialModel* cubeModelMaterial = new MaterialModel(new Mesh(cubeMesh), *modelMaterial);
		cube = new EntityModel(*cubeModelMaterial, Vec3(0,0,0), Vec3(1, 1, 1), Vec3(0, 0, 0));
		delete cubeMesh;

		MeshData* tetrahedronMesh = MeshFactory::Tetrahedron(0,0,0,10);
		MaterialModel* tetrahedronModelMaterial = new MaterialModel(new Mesh(tetrahedronMesh), *modelMaterial);
		tetrahedron = new EntityModel(*tetrahedronModelMaterial, Vec3(30, 0, 10), Vec3(1, 1, 1), Vec3(0, 0, 0));
		delete tetrahedronMesh;

		Mesh* stallMesh = ObjUtils::LoadObj("res/objs/stall.obj.gobj");
		stallMaterial->SetReflectivity(0.1)->SetShineDamper(1);
		MaterialModel* stallModelMaterial = new MaterialModel(stallMesh, *stallMaterial);
		stall = new EntityModel(*stallModelMaterial, Vec3(0.0f, 0.0f, -25), Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));

		Mesh* dragonMesh = ObjUtils::LoadObj("res/objs/dragon.obj.gobj");
		MaterialModel* dragonModelMaterial = new MaterialModel(dragonMesh, *modelMaterial);
		dragon = new EntityModel(*dragonModelMaterial, Vec3(10.0f, 0.0f, -25), Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));
		
		//Mesh* gridMesh = MeshFactory::cube(0,0,0,10,10,10);
		//gridMesh->setEnableCulling(false);
		//MaterialModel* gridModelMaterial = new MaterialModel(gridMesh, *modelMaterial);
		//grid = new EntityModel(*gridModelMaterial, vec3(0, 0, 0), vec3(1, 1, 1), vec3(0, 0, 0));

		//for (uint i = 0;i < 2000;i++)
		//{
		//	models.push_back(EntityModel(*modelModelMaterial, vec3(random()*100, random() * 100, random() * 100), vec3(1.0f, 1.0f, 1.0f), vec3(random() * 360, random() * 360, random() * 360)));
		//}

		Light* l = new Light(Vec3(0, 0,10), 0xffffffff);
		modelShader->Enable();
		l->SetToUniform(modelShader, "light");
		modelShader->Disable();
	
		delete l;

		uilayer = new Layer(new BatchRenderer(), ShaderFactory::DefaultShader(), Mat3::Orthographic(0.0f, (float)Window::GetWidth(), 0.0f, (float)Window::GetHeight()));
		uint colorPink = ColorUtils::Vec3ToColorHex(ColorUtils::GetMaterialColor(300 /360.0f, 3));
		fps = new Label("144 fps", Vec2(50, 300), "roboto", 72, ColorUtils::Vec3ToColorHex(ColorUtils::GetMaterialColor(120 / 360.0f, 9)));
		cursor = new Renderable2D(Vec2(0,0),Vec2(32,32),0xffffffff, new Sprite(TextureManager::Get2D("cursor")), new Sprite(TextureManager::Get2D("mask")));
		//drivers::DriverDispatcher::addDriver(new drivers::LinearDriver(driverTest->m_position.x, -20, 0.5f, true, new drivers::DriverAdapter()));
		guilayer = new GUILayer(new GUIRenderer(),Shader::FromFile("res/shaders/gui.shader"));
		std::vector<std::string> labels{ "Babymode", "Softcore",  "Easy", "Medium", "Hard", "Hardcore", "Expert" };
		slider = new Slider(Vec2(0, 0), Vec2(200, 30), 0, 255, 1);
		slider2 = new Slider(Vec2(0, 40), Vec2(200, 30), labels);
		slider2->SetValue(3);
		Slider* slider3 = new Slider(Vec2(0, 80), Vec2(200, 30), 0, 255, 1);
		slider3->SetRenderPercentage(true);
		slider3->SetSliderController(new SliderController(Vec2(0, 15), Vec2(30, 30)));
		TextBox* textBox = new TextBox(Vec2(0, 120), Vec2(200, 30), false);
		TextBox* textBoxPass = new TextBox(Vec2(0, 160), Vec2(200, 30), true);
		textBox->SetText("Text Box");
		progressFloat = 0;
		ProgressBar* progressBar = new ProgressBar(Vec2(0, 200), Vec2(200, 30),&progressFloat,0,1000);
		
		button = new Button(Vec2(10,300),Vec2(100,40),"Test");
		frame = new Frame(Vec2(10, 10), Vec2(500, 500),"GUI Frame");

		scene3d = new Layer(new BatchRenderer(),blurShader, Mat3::Orthographic(0.0f, (float)Window::GetWidth(), 0.0f, (float)Window::GetHeight()));
		fboScene = new Renderable2D(Vec2(0,0),Vec2(960,540),0xffffffff,new Sprite(fbo->GetColorTexture(GL_COLOR_ATTACHMENT0)),NULL);
		scene3d->Add(fboScene);

		uilayer->Add(fps);
		frame->Add(slider);
		frame->Add(slider2);
		frame->Add(slider3);
		frame->Add(button);
		frame->Add(textBox);
		frame->Add(textBoxPass);
		frame->Add(progressBar);
		guilayer->Add(frame);
		uilayer->Add(cursor);

		//drivers::DriverDispatcher::addDriver(new drivers::LinearDriver(frame->m_position.x, 100, 5, true, new drivers::DriverAdapter()));

		//renderer3d->submit(stall);
		//renderer3d->submit(dragon);
		renderer3d->Submit(grid);
		//renderer3d->submit(cube);
		//renderer3d->submit(tetrahedron);
		//for (uint i = 0;i < 2000;i++)
		//{
		//	renderer3d->submit(&models[i]);
		//}
		movement = new KeyboardControl(GLFW_KEY_D,GLFW_KEY_A,GLFW_KEY_S,GLFW_KEY_W,0.5f);
		rotation = new KeyboardControl(GLFW_KEY_DOWN,GLFW_KEY_UP,GLFW_KEY_RIGHT,GLFW_KEY_LEFT,2);
		//Tree t(renderer3d,0,0,0);
		uint pos = 0;
//		Log::info(JSONLoader::isNumber("0.1234s",pos));
		RenderEngine::AddLayer2d(uilayer, "uilayer");
		//RenderEngine::AddLayer2d(guilayer, "guilayer");
		//RenderEngine::AddLayer3d(new Layer3D(renderer3d), "3dWorld");
		guirenderer = new GUIRenderer();
		//guirenderer->PushMatrix(Mat3::Orthographic(0, Window::GetWidth(), 0, Window::GetHeight()));
		Log::Info(ColorUtils::HexToVec4(0xffaa0077));
	}

	void RecalcPositions(Vec3* vertex)
	{
		float y = vertex->y;
		if (y < 0.45)
		{
			y = 0.45f + Noise::PRNG(vertex->x, vertex->z)*0.01f;// + 0.03f*(rand() / (float)RAND_MAX - 0.5f);
		}
		else if (y < 0.48)
		{
			
		}
		else if (y < 0.58)
		{
			
		}
		else if (y < 0.65)
		{
			y = (pow(y - 0.58, 0.6) + 0.58);
		}
		else
		{
			y = (pow(y - 0.58, 0.6) + 0.58);
		}
		vertex->y = y * 20;
	}

	void RecalcColors(const Vec3& v1, const Vec3& v2, const Vec3& v3, uint* color)
	{
		float y = (v1.y + v2.y + v3.y) / 3.0f / 20.0f;
		if (y < 0.45+0.01f)
		{
			uint blue = (uint)(pow(1, 4.0f) * 255);
			blue = blue > 255 ? 255 : blue;
			*color = 0xff000000 | ((blue / 2) << 16) | ((uint)(blue * 0.9) << 8) | blue;
		}
		else if (y < 0.48)
		{
			*color = 0xffF0E5A5;
		}
		else if (y < 0.58)
		{
			*color = 0xff7CD663;
		}
		else if (y < pow(0.07, 0.6) + 0.58)
		{
			*color = 0xffB5B0A8;
		}
		else
		{
			*color = 0xeffDCF2F2;
		}
	}

	void RecalcGrid(MeshData* data, uint gridWidth, uint gridLength)
	{
		uint* colors = new uint[data->GetVertexCount()];
		Vec3* vertices = data->GetVertices();
		uint indexCount = data->GetIndexCount();
		uint* indices = data->GetIndices();
		Vec3* normals = (Vec3*)data->GetAttribute(ATTRIBUTE_NORMAL)->floats;
		for (int i = 0;i < indexCount;i+=3)
		{
			RecalcPositions(&vertices[indices[i]]);
		}
		uint index = MeshFactory::IndexGrid(gridWidth, gridLength - 1, gridWidth, gridLength);
		RecalcPositions(&vertices[MeshFactory::IndexGrid(gridWidth,gridLength-1,gridWidth,gridLength)]);
		index = MeshFactory::IndexGrid(0, gridLength, gridWidth, gridLength);
		RecalcPositions(&vertices[index]);
		for (int i = 0;i < indexCount;i += 3)
		{
			normals[indices[i]] = MeshFactory::CalculateNormal(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]);
			RecalcColors(vertices[indices[i]], vertices[indices[i+1]], vertices[indices[i+2]], &colors[indices[i]]);
		}
		data->AddAttribute(new AttributeData(ATTRIBUTE_COLOR, colors));
	}



	float Random()
	{
		return (float)((double)rand() / (RAND_MAX));
	}

	void Tick() override
	{
		std::string s = StringUtils::to_string(GetFPS()) + " fps | " + StringUtils::to_string(GetUPS())+ " ups";
		fps->text = s;
		Window::SetTitle("Best Game Ever | " + s);
	}

	float hue = 0;
	Vec3 velocityPos;
	Vec3 velocityNeg;

	void Update(float elapsedTime) override
	{
		guilayer->Update(elapsedTime);
		progressFloat++;
		if (progressFloat > 1000)
			progressFloat = 0;
		//fps->text = toString(slider->getValue());
#if 0 // FPCamera
		vec2 velocityY = movement->getVelocity();
		if (velocityY.lengthSQ() != 0)
		{
			velocityY = velocityY.rotate(camera->yaw);
			camera->position += vec3(velocityY.x, 0, velocityY.y);
		}
		camera->position.y += velocityPos.y - velocityNeg.y;
		vec2 rotationVec = rotation->getVelocity();
		camera->pitch += rotationVec.x;
		camera->yaw += rotationVec.y;
		if (Window::isJoystickConnected(0))
		{
			Joystick& joystick = Window::getJoystick(0);
			if (abs(joystick.getLeftStick().length()) > 0.2)
			{
				float r = toRadians(camera->yaw);
				vec2 rot = joystick.getLeftStick().rotateR(r)*0.2;
				camera->position += vec3(rot.x, 0.0, rot.y);
			}
			if (abs(joystick.getRightStick().x) > 0.2)
			{
				camera->pitch += joystick.getRightStick().x * 2;
			}
			if (abs(joystick.getRightStick().y) > 0.2)
			{
				camera->yaw += joystick.getRightStick().y * 2;
			}
			if (joystick.isButtonDown(GLFW_JOYSTICK_A))
			{
				camera->position.y += 0.2;
			}
			if (joystick.isButtonDown(GLFW_JOYSTICK_B))
			{
				camera->position.y -= 0.2;
			}
		}
#else

#endif
		//model->rotate(elapsedTime*100, elapsedTime * 100, elapsedTime * 100);
		//model->update(elapsedTime);
		//model2->update(elapsedTime);
		//lightSource->update(elapsedTime);
		//for (uint i = 0;i < 2000;i++)
		//{
		//	models[i].update(elapsedTime);
		//}
		hue += elapsedTime / 3.0f;
		while (hue >= 1)
			hue--;
		cursor->m_color = ColorUtils::Vec3ToColorHex(ColorUtils::HSVtoRGB(hue, 1, 1));
		//cursor->setPosition(vec2(p.x, p.y));
	}

	bool OnPressed(const KeyPressedEvent& e) override
	{
		if (e.GetButton() == GLFW_KEY_F5)
		{
			Shader* terrainShader = Shader::FromFile("res/shaders/terrain.vert", "res/shaders/terrain.frag");
			Shader* modelShader = Shader::FromFile("res/shaders/3dshader.vert", "res/shaders/3dshader.frag");
			modelMaterial->SetShader(modelShader);
			terrainMaterial->SetShader(terrainShader);
			Light* l = new Light(Vec3(25, 25, 12.5), 0xffffffff);

			modelShader->Enable();
			l->SetToUniform(modelShader, "light");
			modelShader->Disable();
			//terrainShader->enable();
			//l->setToUniform(terrainShader, "light");
			//terrainShader->disable();
			delete l;
		}
		if (e.GetButton() == GLFW_KEY_F1)
		{
			Log::Info("pos=", camera->GetPosition(), " height=", camera->GetHeight(), " distance=", camera->GetDistance(), ", rotation=", camera->GetRotation());
		}
		if (e.GetButton() == GLFW_KEY_F2)
		{
			camera->SetPosition(Vec3(-3.5, -7.8, 5.5));
			camera->SetDistance(18);
			camera->SetHeight(0.66);
			camera->SetRotation(38.5);
		}
		if (e.GetButton() == GLFW_KEY_F10)
		{
			Utils::Screenshot(Window::GetWidth(), Window::GetHeight());
		}
		if (e.GetButton() == GLFW_KEY_X)
		{
			Vec3 p = renderer3d->GetScreenCoordination(Vec3(0,0,0),Window::GetWidth(),Window::GetHeight());
		}
		movement->onInput(e.GetButton(),true);
		rotation->onInput(e.GetButton(),true);
		if (e.GetButton() == GLFW_KEY_LEFT_SHIFT)
		{
			velocityNeg.y = 0.2;
		}
		if (e.GetButton() == GLFW_KEY_SPACE)
		{
			velocityPos.y = 0.2;
		}
		return false;
	}

	bool OnReleased(const KeyReleasedEvent& e)  override
	{
		movement->onInput(e.GetButton(),false);
		rotation->onInput(e.GetButton(),false);
		if (e.GetButton() == GLFW_KEY_LEFT_SHIFT)
		{
			velocityNeg.y = 0;
		}
		if (e.GetButton() == GLFW_KEY_SPACE)
		{ 
			velocityPos.y = 0;
		}
		return false;
	}

	bool OnTyped(const KeyTypedEvent& e) override
	{
		return false;
	}

	bool OnPressed(const MousePressedEvent& e)  override
	{
		return false;
	}

	bool OnReleased(const MouseReleasedEvent& e) override
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
		return false;
	}

	bool screenshot = false;
	void Render() override
	{
		//guirenderer->SubmitString("test", Vec2(100, 100), FontManager::Get("roboto",24), 0xff00ff);
		//guirenderer->SubmitRect(Vec2(0, 0), Vec2(1, 1), 0xffffff00);
		guilayer->Render();
	}
	
	void WindowResize(int width, int height) override
	{
		//camera::Camera::getInstance()->getLayer(0)->setProjectionMatrix(mat3::orthographic(0, (float)width / 20.0f, 0, (float)height / 20.0f)*mat3::translate((width - 960) / 40.0f, (height - 540) / 40.0f));
		//camera::Camera::getInstance()->getLayer(1)->setProjectionMatrix(mat3::orthographic(0, (float)width / 20.0f, 0, (float)height / 20.0f)*mat3::translate((width - 960) / 40.0f, (height - 540) / 40.0f));
		//camera::Camera::getInstance()->getLayer(2)->setProjectionMatrix(mat3::orthographic(0, (float)width, 0, (float)height)*mat3::translate((width - 960) / 2, (height - 540) / 2));
		//camera::Camera::getInstance()->setViewport(0, 0, width, height* 9 / 16);
		uilayer->SetProjectionMatrix(Mat3::Orthographic(0,Window::GetWidth(),0,Window::GetHeight()));
	}

	void JoystickState(uint joy, bool connected) override
	{
		if (connected)
			Log::Info("Controller ", joy, " connected!");
		else
			Log::Info("Controller ", joy, " disconnected!");
	}
};

#include <fstream>
int main()
{
	/*
	uint pos = 0;
	uint lastPos = pos;
	JSONObject obj = JSONLoader::loadJSON("test.txt");
	Log::info("object1",obj.hasKey("object1") ? "true" : "false");
	Log::info("object1.string1", obj.getObject("object1").getValue("string1"));
	Log::info("object1.float", obj.getObject("object1").getValueAsFloat("float"));
	Log::info("object1.null", obj.getObject("object1").isNull("null") ? "true" : "false");
	Log::info("object1.true", obj.getObject("object1").getValueAsBool("true") ? "true" : "false");
	Log::info("object1.false", obj.getObject("object1").getValueAsBool("false") ? "true" : "false");
	Log::info("string2", obj.getValueAsFloat("string2"));
	std::ofstream file("save.txt");
	file << obj;
	file.close();
	system("pause");
	*/
	Core game;
	game.Start();
}
