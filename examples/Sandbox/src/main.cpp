#include <Greet.h>

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
	Shader* m_geomShaderTest;
	std::vector<EntityModel> models;
	FrameBufferObject* fbo;


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

	void init()
	{
		EventDispatcher::addKeyListener(DISPATCHER_GUI+1, *this);
		EventDispatcher::addMouseListener(DISPATCHER_GUI + 1, *this);
		createWindow("Best Game Ever", 960, 540);
		setFrameCap(144);
		TextureManager::add(new Texture2D("res/textures/stallTexture.png", "stall"));
		TextureManager::add(new Texture2D("res/textures/cursor.png", "cursor"));
		TextureManager::add(new Texture2D("res/textures/mask.png", "mask"));
		TextureManager::add(new Texture2D("res/textures/mask2.png", "mask2"));
		TextureManager::add(new CubeMap("res/textures/skybox.png", "skybox"));
		TextureManager::add(new Texture2D("res/textures/lens_flare1.png", "lensflare1"));
		TextureManager::add(new Texture2D("res/textures/lens_flare2.png", "lensflare2"));
		TextureManager::add(new Texture2D("res/textures/lens_flare3.png", "lensflare3"));
		TextureManager::add(new Texture2D("res/textures/lens_flare4.png", "lensflare4"));
		FontManager::add(new FontContainer("Anonymous Pro.ttf", "anonymous"));

		fbo = new FrameBufferObject(960,540);
		//camera = new TPCamera(vec3(-3.5, -7.8, 5.5), 18, 0.66, 38.5, 15, 80, 0, 0.8f); // Profile shot
		camera = new TPCamera(vec3(0, 0, 0), 15, 0, 0, 15, 80, 0, 0.8f);
		Skybox* skybox = new Skybox((CubeMap*)TextureManager::get("skybox"));
		renderer3d = new BatchRenderer3D(Window::getWidth(), Window::getHeight(), camera,90,0.001f,1000.0f, skybox);


		Shader* modelShader = Shader::fromFile("res/shaders/3dshader.vert", "res/shaders/3dshader.frag");
		Shader* terrainShader = Shader::fromFile("res/shaders/terrain.vert", "res/shaders/terrain.frag");
		Shader* stallShader = Shader::fromFile("res/shaders/3dshader.vert", "res/shaders/3dshader.frag");
		blurShader = Shader::fromFile("res/shaders/default2dshader.vert","res/shaders/guassianblur.frag");
		m_geomShaderTest = Shader::fromFile("res/shaders/2dshader.geom","res/shaders/2dshader.vert", "res/shaders/2dshader.frag");

		modelMaterial = new Material(modelShader, NULL);
		stallMaterial = new Material(stallShader,TextureManager::get("stall"));
		terrainMaterial = new Material(terrainShader, NULL);
		terrainMaterial->setReflectivity(0.5f);
		terrainMaterial->setShineDamper(5.0f);
		uint gridWidth = 999;
		uint gridLength = 999;
		float* noise = Noise::genNoise(gridWidth+1, gridWidth + 1,5,64, 64,0.5f);
		noise[0] = 10;
		MeshData* gridMesh = MeshFactory::lowPolyGrid(0, 0, 0, gridWidth+1, gridLength+1, gridWidth, gridLength, noise,1);
		recalcGrid(gridMesh, gridWidth, gridLength);
		
		//gridMesh->setDefaultAttribute4f(MESH_COLORS_LOCATION, vec4(1.0f, 0.0f, 0.0f, 1.0f));
		//gridMesh->setEnableCulling(false);
		MaterialModel* gridModelMaterial = new MaterialModel(new Mesh(gridMesh), *terrainMaterial);
		grid = new EntityModel(*gridModelMaterial, vec3(0, -20, 0), vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f));
		delete gridMesh;

		MeshData* cubeMesh = MeshFactory::cube(0,0,0,10,10,10);
		MaterialModel* cubeModelMaterial = new MaterialModel(new Mesh(cubeMesh), *modelMaterial);
		cube = new EntityModel(*cubeModelMaterial, vec3(0,0,0), vec3(1, 1, 1), vec3(0, 0, 0));
		delete cubeMesh;

		MeshData* tetrahedronMesh = MeshFactory::tetrahedron(0,0,0,10);
		MaterialModel* tetrahedronModelMaterial = new MaterialModel(new Mesh(tetrahedronMesh), *modelMaterial);
		tetrahedron = new EntityModel(*tetrahedronModelMaterial, vec3(30, 0, 10), vec3(1, 1, 1), vec3(0, 0, 0));
		delete tetrahedronMesh;

		Mesh* stallMesh = ObjUtils::loadObj("res/objs/stall.obj.gobj");
		stallMaterial->setReflectivity(0.1)->setShineDamper(1);
		MaterialModel* stallModelMaterial = new MaterialModel(stallMesh, *stallMaterial);
		stall = new EntityModel(*stallModelMaterial, vec3(0.0f, 0.0f, -25), vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f));

		Mesh* dragonMesh = ObjUtils::loadObj("res/objs/dragon.obj.gobj");
		MaterialModel* dragonModelMaterial = new MaterialModel(dragonMesh, *modelMaterial);
		dragon = new EntityModel(*dragonModelMaterial, vec3(10.0f, 0.0f, -25), vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f));
		
		//Mesh* gridMesh = MeshFactory::cube(0,0,0,10,10,10);
		//gridMesh->setEnableCulling(false);
		//MaterialModel* gridModelMaterial = new MaterialModel(gridMesh, *modelMaterial);
		//grid = new EntityModel(*gridModelMaterial, vec3(0, 0, 0), vec3(1, 1, 1), vec3(0, 0, 0));

		//for (uint i = 0;i < 2000;i++)
		//{
		//	models.push_back(EntityModel(*modelModelMaterial, vec3(random()*100, random() * 100, random() * 100), vec3(1.0f, 1.0f, 1.0f), vec3(random() * 360, random() * 360, random() * 360)));
		//}

		Light* l = new Light(vec3(0, 0,10), 0xffffffff);
		modelShader->enable();
		l->setToUniform(modelShader, "light");
		modelShader->disable();
	
		delete l;

		uilayer = new Layer(new BatchRenderer(), ShaderFactory::DefaultShader(), mat3::orthographic(0.0f, (float)Window::getWidth(), 0.0f, (float)Window::getHeight()));
		uint colorPink = ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(300 /360.0f, 3));
		fps = new Label("144 fps", vec2(50, 300), "roboto", 72, ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 9)));
		cursor = new Renderable2D(vec2(0,0),vec2(32,32),0xffffffff, new Sprite(TextureManager::get2D("cursor")), new Sprite(TextureManager::get2D("mask")));
		//drivers::DriverDispatcher::addDriver(new drivers::LinearDriver(driverTest->m_position.x, -20, 0.5f, true, new drivers::DriverAdapter()));
		guilayer = new GUILayer(new BatchRenderer(),ShaderFactory::DefaultShader());
		std::vector<std::string> labels{ "Babymode", "Softcore",  "Easy", "Medium", "Hard", "Hardcore", "Expert" };
		slider = new Slider(vec2(0, 0), vec2(200, 30), 0, 255, 1);
		slider2 = new Slider(vec2(0, 40), vec2(200, 30), labels);
		slider2->setValue(3);
		Slider* slider3 = new Slider(vec2(0, 80), vec2(200, 30), 0, 255, 1);
		slider3->setRenderPercentage(true);
		slider3->setSliderController(new SliderController(vec2(0, 15), vec2(30, 30)));
		TextBox* textBox = new TextBox(vec2(0, 120), vec2(200, 30));
		textBox->setText("Text Box");
		progressFloat = 0;
		ProgressBar* progressBar = new ProgressBar(vec2(0, 160), vec2(200, 30),&progressFloat,0,1000);
		
		button = new Button(vec2(10,300),vec2(100,40),"Test");
		frame = new Frame(vec2(10, 10), vec2(500, 500),"GUI Frame");

		scene3d = new Layer(new BatchRenderer(),blurShader, mat3::orthographic(0.0f, (float)Window::getWidth(), 0.0f, (float)Window::getHeight()));
		fboScene = new Renderable2D(vec2(0,0),vec2(960,540),0xffffffff,new Sprite(fbo->getColorTexture(GL_COLOR_ATTACHMENT0)),NULL);
		scene3d->add(fboScene);

		uilayer->add(fps);
		frame->add(slider);
		frame->add(slider2);
		frame->add(slider3);
		frame->add(button);
		frame->add(textBox);
		frame->add(progressBar);
		guilayer->add(frame);
		uilayer->add(cursor);

		//drivers::DriverDispatcher::addDriver(new drivers::LinearDriver(frame->m_position.x, 100, 5, true, new drivers::DriverAdapter()));

		//renderer3d->submit(stall);
		//renderer3d->submit(dragon);
		renderer3d->submit(grid);
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
		RenderEngine::add_layer2d(uilayer, "uilayer");
		RenderEngine::add_layer2d(guilayer, "guilayer");
		RenderEngine::add_layer3d(new Layer3D(renderer3d), "3dWorld");
	}

	void recalcPositions(vec3* vertex)
	{
		float y = vertex->y;
		if (y < 0.45)
		{
			y = 0.45f + Noise::prng(vertex->x, vertex->z)*0.01f;// + 0.03f*(rand() / (float)RAND_MAX - 0.5f);
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

	void recalcColors(const vec3& v1, const vec3& v2, const vec3& v3, uint* color)
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

	void recalcGrid(MeshData* data, uint gridWidth, uint gridLength)
	{
		uint* colors = new uint[data->getVertexCount()];
		vec3* vertices = data->getVertices();
		uint indexCount = data->getIndexCount();
		uint* indices = data->getIndices();
		vec3* normals = (vec3*)data->getAttribute(ATTRIBUTE_NORMAL)->floats;
		for (int i = 0;i < indexCount;i+=3)
		{
			recalcPositions(&vertices[indices[i]]);
		}
		uint index = MeshFactory::indexGrid(gridWidth, gridLength - 1, gridWidth, gridLength);
		recalcPositions(&vertices[MeshFactory::indexGrid(gridWidth,gridLength-1,gridWidth,gridLength)]);
		index = MeshFactory::indexGrid(0, gridLength, gridWidth, gridLength);
		recalcPositions(&vertices[index]);
		for (int i = 0;i < indexCount;i += 3)
		{
			normals[indices[i]] = MeshFactory::calculateNormal(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]);
			recalcColors(vertices[indices[i]], vertices[indices[i+1]], vertices[indices[i+2]], &colors[indices[i]]);
		}
		data->addAttribute(new AttributeData(ATTRIBUTE_COLOR, colors));
	}



	float random()
	{
		return (float)((double)rand() / (RAND_MAX));
	}

	void tick()
	{
		std::string s = StringUtils::toString(getFPS()) + " fps | " + StringUtils::toString(getUPS())+ " ups";
		fps->text = s;
		Window::setTitle("Best Game Ever | " + s);
	}

	float hue = 0;
	vec3 velocityPos;
	vec3 velocityNeg;

	void update(float elapsedTime)
	{
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
		cursor->m_color = ColorUtils::vec3ToColorHex(ColorUtils::HSVtoRGB(hue, 1, 1));
		//cursor->setPosition(vec2(p.x, p.y));
	}

	bool onPressed(const KeyPressedEvent& e) override
	{
		if (e.getButton() == GLFW_KEY_F5)
		{
			Shader* terrainShader = Shader::fromFile("res/shaders/terrain.vert", "res/shaders/terrain.frag");
			Shader* modelShader = Shader::fromFile("res/shaders/3dshader.vert", "res/shaders/3dshader.frag");
			modelMaterial->setShader(modelShader);
			terrainMaterial->setShader(terrainShader);
			Light* l = new Light(vec3(25, 25, 12.5), 0xffffffff);

			modelShader->enable();
			l->setToUniform(modelShader, "light");
			modelShader->disable();
			//terrainShader->enable();
			//l->setToUniform(terrainShader, "light");
			//terrainShader->disable();
			delete l;
		}
		if (e.getButton() == GLFW_KEY_F1)
		{
			Log::info("pos=", camera->getPosition(), " height=", camera->getHeight(), " distance=", camera->getDistance(), ", rotation=", camera->getRotation());
		}
		if (e.getButton() == GLFW_KEY_F2)
		{
			camera->setPosition(vec3(-3.5, -7.8, 5.5));
			camera->setDistance(18);
			camera->setHeight(0.66);
			camera->setRotation(38.5);
		}
		if (e.getButton() == GLFW_KEY_F10)
		{
			Utils::screenshot(Window::getWidth(), Window::getHeight());
		}
		if (e.getButton() == GLFW_KEY_X)
		{
			vec3 p = renderer3d->getScreenCoordination(vec3(0,0,0),Window::getWidth(),Window::getHeight());
		}
		movement->onInput(e.getButton(),true);
		rotation->onInput(e.getButton(),true);
		if (e.getButton() == GLFW_KEY_LEFT_SHIFT)
		{
			velocityNeg.y = 0.2;
		}
		if (e.getButton() == GLFW_KEY_SPACE)
		{
			velocityPos.y = 0.2;
		}
		return false;
	}

	bool onReleased(const KeyReleasedEvent& e)  override
	{
		movement->onInput(e.getButton(),false);
		rotation->onInput(e.getButton(),false);
		if (e.getButton() == GLFW_KEY_LEFT_SHIFT)
		{
			velocityNeg.y = 0;
		}
		if (e.getButton() == GLFW_KEY_SPACE)
		{ 
			velocityPos.y = 0;
		}
		return false;
	}

	bool onTyped(const KeyTypedEvent& e) override
	{
		return false;
	}

	bool onPressed(const MousePressedEvent& e)  override
	{
		return false;
	}

	bool onReleased(const MouseReleasedEvent& e) override
	{
		return false;
	}

	bool onMoved(const MouseMovedEvent& e) override
	{
		cursor->setPosition(vec2(e.getX(), e.getY()));
		return false;
	}

	bool onScroll(const MouseScrollEvent& e) override
	{
		return false;
	}

	bool screenshot = false;
	void render()
	{
		
	}
	
	void windowResize(int width, int height) override
	{
		//camera::Camera::getInstance()->getLayer(0)->setProjectionMatrix(mat3::orthographic(0, (float)width / 20.0f, 0, (float)height / 20.0f)*mat3::translate((width - 960) / 40.0f, (height - 540) / 40.0f));
		//camera::Camera::getInstance()->getLayer(1)->setProjectionMatrix(mat3::orthographic(0, (float)width / 20.0f, 0, (float)height / 20.0f)*mat3::translate((width - 960) / 40.0f, (height - 540) / 40.0f));
		//camera::Camera::getInstance()->getLayer(2)->setProjectionMatrix(mat3::orthographic(0, (float)width, 0, (float)height)*mat3::translate((width - 960) / 2, (height - 540) / 2));
		//camera::Camera::getInstance()->setViewport(0, 0, width, height* 9 / 16);
		uilayer->setProjectionMatrix(mat3::orthographic(0,Window::getWidth(),0,Window::getHeight()));
	}
};
#include <fstream>
int main()
{
	/*uint pos = 0;
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
	game.start();
}
