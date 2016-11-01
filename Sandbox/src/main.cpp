#include <greet.h>

#include "keyboardcontrol.h"
#include "tree.h"

using namespace greet;
using namespace graphics;
using namespace audio;
using namespace model;
using namespace utils;
using namespace event;

class Core : public greet::internal::App, public greet::event::KeyListener, public greet::event::MouseListener
{

private:
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

	Camera* camera;
	Layer<Renderable>* uilayer;
	GUILayer* guilayer;
	Slider* slider;
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

		uint error = glGetError();
		fbo = new FrameBufferObject(480,270);
		if ((error = glGetError()) != GL_NO_ERROR)
			LOG_INFO(error);
		camera = new Camera(math::vec3(0,0,0));
		Skybox* skybox = new Skybox((CubeMap*)TextureManager::get("skybox"));
		renderer3d = new BatchRenderer3D(Window::getWidth(), Window::getHeight(), *camera,70,0.001f,1000.0f, skybox);

		float* map = new float[101 * 101];
		for (int i = 0;i < 101 * 101;i++)
		{
			map[i] = rand() / (float)RAND_MAX;
		}


		Shader* modelShader = Shader::fromFile("res/shaders/3dshader.vert", "res/shaders/3dshader.frag");
		Shader* terrainShader = Shader::fromFile("res/shaders/terrain.geom", "res/shaders/terrain.vert", "res/shaders/terrain.frag");
		Shader* stallShader = Shader::fromFile("res/shaders/3dshader.vert", "res/shaders/3dshader.frag");
		m_geomShaderTest = Shader::fromFile("res/shaders/2dshader.geom","res/shaders/2dshader.vert", "res/shaders/2dshader.frag");

		modelMaterial = new Material(modelShader, NULL);
		stallMaterial = new Material(stallShader,TextureManager::get("stall"));
		terrainMaterial = new Material(terrainShader, NULL);
		terrainMaterial->setReflectivity(0.5f);
		terrainMaterial->setShineDamper(5.0f);
		float* noise = Noise::genNoise(500,500,5,64,64,0.5f);
		MeshData* gridMesh = model::MeshFactory::grid(0, 0, 0, 500, 500, 499, 499, noise,1);
		//gridMesh->setDefaultAttribute4f(MESH_COLORS_LOCATION, math::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		//gridMesh->setEnableCulling(false);
		MaterialModel* gridModelMaterial = new MaterialModel(new Mesh(gridMesh), *terrainMaterial);
		grid = new EntityModel(*gridModelMaterial, math::vec3(0, -20, 0), math::vec3(1.0f, 1.0f, 1.0f), math::vec3(0.0f, 0.0f, 0.0f));
		delete gridMesh;

		MeshData* cubeMesh = model::MeshFactory::cube(0,0,0,10,10,10);
		MaterialModel* cubeModelMaterial = new MaterialModel(new Mesh(cubeMesh), *modelMaterial);
		cube = new EntityModel(*cubeModelMaterial, math::vec3(20, 0, 0), math::vec3(1, 1, 1), math::vec3(0, 0, 0));
		delete cubeMesh;

		MeshData* tetrahedronMesh = model::MeshFactory::tetrahedron(0,0,0,10);
		MaterialModel* tetrahedronModelMaterial = new MaterialModel(new Mesh(tetrahedronMesh), *modelMaterial);
		tetrahedron = new EntityModel(*tetrahedronModelMaterial, math::vec3(30, 0, 10), math::vec3(1, 1, 1), math::vec3(0, 0, 0));
		delete tetrahedronMesh;

		Mesh* stallMesh = utils::loadObj("res/objs/stall.obj.gobj");
		stallMaterial->setReflectivity(0.1)->setShineDamper(1);
		MaterialModel* stallModelMaterial = new MaterialModel(stallMesh, *stallMaterial);
		stall = new EntityModel(*stallModelMaterial, math::vec3(0.0f, 0.0f, -25), math::vec3(1.0f, 1.0f, 1.0f), math::vec3(0.0f, 0.0f, 0.0f));

		Mesh* dragonMesh = utils::loadObj("res/objs/dragon.obj.gobj");
		MaterialModel* dragonModelMaterial = new MaterialModel(dragonMesh, *modelMaterial);
		dragon = new EntityModel(*dragonModelMaterial, math::vec3(10.0f, 0.0f, -25), math::vec3(1.0f, 1.0f, 1.0f), math::vec3(0.0f, 0.0f, 0.0f));
		
		//Mesh* gridMesh = model::MeshFactory::cube(0,0,0,10,10,10);
		//gridMesh->setEnableCulling(false);
		//MaterialModel* gridModelMaterial = new MaterialModel(gridMesh, *modelMaterial);
		//grid = new EntityModel(*gridModelMaterial, math::vec3(0, 0, 0), math::vec3(1, 1, 1), math::vec3(0, 0, 0));

		//for (uint i = 0;i < 2000;i++)
		//{
		//	models.push_back(EntityModel(*modelModelMaterial, math::vec3(random()*100, random() * 100, random() * 100), math::vec3(1.0f, 1.0f, 1.0f), math::vec3(random() * 360, random() * 360, random() * 360)));
		//}

		Light* l = new Light(math::vec3(25, 25,12.5), 0xffffffff);
		modelShader->enable();
		l->setToUniform(modelShader, "light");
		modelShader->disable();
		terrainShader->enable();
		l->setToUniform(terrainShader, "light");
		terrainShader->disable();
	
		delete l;
		FontManager::add(new FontContainer("Anonymous Pro.ttf", "anonymous"));

		uilayer = new Layer<Renderable>(new BatchRenderer(), ShaderFactory::DefaultShader(), math::mat3::orthographic(0.0f, (float)Window::getWidth(), 0.0f, (float)Window::getHeight()));
		uint colorPink = ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(300 /360.0f, 3));
		fps = new Label("144 fps", math::vec2(50, 300), "anonymous", 72, ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 9)));
		cursor = new Renderable2D(math::vec2(0,0),math::vec2(32,32),0xffffffff, new Sprite(TextureManager::get2D("cursor")), new Sprite(TextureManager::get2D("mask")));
		//drivers::DriverDispatcher::addDriver(new drivers::LinearDriver(driverTest->m_position.x, -20, 0.5f, true, new drivers::DriverAdapter()));
		guilayer = new GUILayer(new BatchRenderer(),ShaderFactory::DefaultShader());
		slider = new Slider(math::vec2(10,100),math::vec2(200,30),0,255,1);
		button = new Button(math::vec2(10,120+30),math::vec2(100,40),"Test");
		frame = new Frame(math::vec2(10, 10), math::vec2(500, 500),"GUI Frame");
		fboScene = new Renderable2D(math::vec2(0,0),math::vec2(320,180),0xffffffff,new Sprite(fbo->getColorTexture()),NULL);
		//uilayer->add(fps);
		frame->add(slider);
		frame->add(button);
		guilayer->add(frame);
		uilayer->add(fboScene);
		uilayer->add(cursor);

		//drivers::DriverDispatcher::addDriver(new drivers::LinearDriver(frame->m_position.x, 100, 5, true, new drivers::DriverAdapter()));

		renderer3d->submit(stall);
		//renderer3d->submit(dragon);
		renderer3d->submit(grid);
		renderer3d->submit(cube);
		renderer3d->submit(tetrahedron);
		//for (uint i = 0;i < 2000;i++)
		//{
		//	renderer3d->submit(&models[i]);
		//}
		movement = new KeyboardControl(GLFW_KEY_D,GLFW_KEY_A,GLFW_KEY_S,GLFW_KEY_W,0.5f);
		rotation = new KeyboardControl(GLFW_KEY_DOWN,GLFW_KEY_UP,GLFW_KEY_RIGHT,GLFW_KEY_LEFT,2);
		//Tree t(renderer3d,0,0,0);
	}

	float random()
	{
		return (float)((double)rand() / (RAND_MAX));
	}

	void tick()
	{
		std::string s = utils::toString(getFPS()) + " fps";
		fps->text = s;
		Window::setTitle("Best Game Ever | " + s);
	}

	float hue = 0;
	math::vec3 velocityPos;
	math::vec3 velocityNeg;

	void update(float elapsedTime)
	{
		//fps->text = utils::toString(slider->getValue());
		math::vec2 velocityY = movement->getVelocity();
		if (velocityY.lengthSQ() != 0)
		{
			velocityY = velocityY.rotate(camera->yaw);
			camera->position += math::vec3(velocityY.x, 0, velocityY.y);
		}
		camera->position.y += velocityPos.y - velocityNeg.y;
		math::vec2 rotationVec = rotation->getVelocity();
		camera->pitch += rotationVec.x;
		camera->yaw += rotationVec.y;
		if (Window::isJoystickConnected(0))
		{
			input::Joystick& joystick = Window::getJoystick(0);
			if (abs(joystick.getLeftStick().length()) > 0.2)
			{
				float r = math::toRadians(camera->yaw);
				math::vec2 rot = joystick.getLeftStick().rotateR(r)*0.2;
				camera->position += math::vec3(rot.x, 0.0, rot.y);
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
		//model->rotate(elapsedTime*100, elapsedTime * 100, elapsedTime * 100);
		//model->update(elapsedTime);
		//model2->update(elapsedTime);
		//lightSource->update(elapsedTime);
		//for (uint i = 0;i < 2000;i++)
		//{
		//	models[i].update(elapsedTime);
		//}
		uilayer->update(elapsedTime);
		guilayer->update(elapsedTime);
		hue += elapsedTime / 3.0f;
		while (hue >= 1)
			hue--;
		cursor->m_color = ColorUtils::vec3ToColorHex(ColorUtils::HSVtoRGB(hue, 1, 1));
		//cursor->setPosition(math::vec2(p.x, p.y));
	}

	bool onPressed(const KeyPressedEvent& e) override
	{
		if (e.getButton() == GLFW_KEY_F5)
		{
			Shader* terrainShader = Shader::fromFile("res/shaders/terrain.geom", "res/shaders/terrain.vert", "res/shaders/terrain.frag");
			Shader* modelShader = Shader::fromFile("res/shaders/3dshader.vert", "res/shaders/3dshader.frag");
			modelMaterial->setShader(modelShader);
			terrainMaterial->setShader(terrainShader);
			Light* l = new Light(math::vec3(25, 25, 12.5), 0xffffffff);
			modelShader->enable();
			l->setToUniform(modelShader, "light");
			modelShader->disable();
			Light* l2 = new Light(math::vec3(0, 100, 0), 0xffffffff);
			terrainShader->enable();
			l2->setToUniform(terrainShader, "light");
			terrainShader->disable();
			delete l;
			delete l2;
		}
		if (e.getButton() == GLFW_KEY_F10)
		{
			utils::screenshot(Window::getWidth(), Window::getHeight());
		}
		if (e.getButton() == GLFW_KEY_X)
		{
			math::vec3 p = renderer3d->getScreenCoordination(math::vec3(0,0,0),Window::getWidth(),Window::getHeight());
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
		cursor->setPosition(math::vec2(e.getX(), e.getY()));

		return false;
	}
	bool screenshot = false;
	void render()
	{
		fbo->bind();
		renderer3d->begin();
		renderer3d->flush();
		renderer3d->end();
		fbo->unbind();

		renderer3d->begin();
		renderer3d->flush();
		renderer3d->end();
		//guilayer->render();
		uilayer->render();
	}
	
	void windowResize(int width, int height) override
	{
		//camera::Camera::getInstance()->getLayer(0)->setProjectionMatrix(math::mat3::orthographic(0, (float)width / 20.0f, 0, (float)height / 20.0f)*math::mat3::translate((width - 960) / 40.0f, (height - 540) / 40.0f));
		//camera::Camera::getInstance()->getLayer(1)->setProjectionMatrix(math::mat3::orthographic(0, (float)width / 20.0f, 0, (float)height / 20.0f)*math::mat3::translate((width - 960) / 40.0f, (height - 540) / 40.0f));
		//camera::Camera::getInstance()->getLayer(2)->setProjectionMatrix(math::mat3::orthographic(0, (float)width, 0, (float)height)*math::mat3::translate((width - 960) / 2, (height - 540) / 2));
		//camera::Camera::getInstance()->setViewport(0, 0, width, height* 9 / 16);
		uilayer->setProjectionMatrix(math::mat3::orthographic(0,Window::getWidth(),0,Window::getHeight()));
	}
};

int main()
{
	Core game;
	game.start();
}
