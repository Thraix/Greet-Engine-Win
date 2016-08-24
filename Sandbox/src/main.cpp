#if 0

#include <camera\camera.h>
#include <internal\app.h>
#include <entity\entity.h>
#include <graphics\gui\frame.h>
#include <graphics\gui\panel.h>
#include <graphics\atlas\atlasmanager.h>
#include <graphics\renderers/batchrenderer.h>
#include <graphics\shaders\shaderfactory.h>
#include <graphics\layers\box2dlayer.h>
//#include <graphics/renderers/renderer3d.h>
//#include <graphics/models/mesh.h>


using namespace greet;
using namespace graphics;
using namespace audio;
//using namespace model;

class Core : public greet::internal::App
{
private:
	entity::Entity* e;
	entity::Entity* e2;
	b2World* world;
	Label* fps;
	Label* fps2;
	Frame* frame;
	//Renderer3D* renderer3d;
	//Mesh* mesh;
public:

public:
	Core()
		:App()
	{

	}

	~Core()
	{
		camera::Camera::destroyCamera();
		delete world;
	}

	void init() override
	{
		createWindow("Best Game Ever", 960, 540);
		camera::Camera::initCamera(m_window);
		setFrameCap(144);
		LOG_INFO(getFrameCap());
		FontManager::add(new Font("Anonymous Pro.ttf", "anonymous", 72));
		Layer* uilayer = new Layer(new BatchRenderer(), ShaderFactory::DefaultShader(),math::mat3::orthographic(0.0f, (float)m_window->getWidth(), 0.0f, (float)m_window->getHeight()));
		frame = new Frame(math::vec2(10, 10), math::vec2(370, 400), "Console");
		Panel* panel = new Panel(math::vec2(-0, -0), frame->getContentSize());
		panel->setBackgroundColor(0xff777777);
		frame->add(panel);
		fps2 = new Label("fps", math::vec2(15, 65), "anonymous", 72, 0xff000000);
		fps = new Label("fps", math::vec2(10, 60), "anonymous", 72, 0xffff00ff);
		panel->add(fps2);
		panel->add(fps);
		uilayer->add(frame);
		//renderer3d = new Renderer3D();
		//LOG_INFO(math::vec2(10,20));

		TextureManager::add(new Texture("res/textures/test.png", "test"));
		TextureManager::add(new Texture("res/textures/animation.png", "animation"));
		AtlasManager::add(new Atlas("atlas32", 128, 32));
		Atlas* atlas32 = AtlasManager::get("atlas32");

		atlas32->addTexture("animation", "res/textures/animation.png");
		atlas32->addTexture("animation2", "res/textures/animation.png");
		atlas32->addTexture("grass", "res/textures/test3.png");


		m_window->setBackgroundColor(math::vec4(0.5f, 0.5f, 0.5f, 1.0f));


		world = new b2World(b2Vec2(0, 0));
		e = new entity::Entity(math::vec2(20, 20), math::vec2(5, 5), 0xffff00ff, world);
		e2 = new entity::Entity(math::vec2(10, 10), math::vec2(5, 5), 0xffff00ff, world);
		//e->m_body->SetAngularVelocity(60);
		Layer* gamelayer = new Layer(new BatchRenderer(), ShaderFactory::DefaultShader(), math::mat3::orthographic(0.0f, (float)m_window->getWidth() / 20.0f, 0.0f, (float)m_window->getHeight() / 20.0f));
		gamelayer->add(e);
		gamelayer->add(e2);

		Layer* layer = new Box2DLayer(ShaderFactory::DefaultShader(), math::mat3::orthographic(0.0f, (float)m_window->getWidth() / 20.0f, 0.0f, (float)m_window->getHeight() / 20.0f), world);
		createPoly(gamelayer, 15, 15, 6, 5, 0xff00ffff);

		createBody(gamelayer, 0, -1, (float)m_window->getWidth() / 20.0f, 1, 0xff00ffff);
		createBody(gamelayer, 0, (float)m_window->getHeight() / 20.0f, (float)m_window->getWidth() / 20.0f, 1, 0xff00ffff);
		createBody(gamelayer, -1, 0, 1, (float)m_window->getHeight() / 20.0f, 0xff00ffff);
		createBody(gamelayer, (float)m_window->getWidth() / 20.0f, 0, 1, (float)m_window->getHeight() / 20.0f, 0xff00ffff);

		camera::Camera::getInstance()->addLayer(gamelayer, 0);
		camera::Camera::getInstance()->addLayer(layer, 1);
		camera::Camera::getInstance()->addLayer(uilayer, 2);
		//camera::Camera::getInstance()->setViewport(0, 0, 1280, 1280*9/16);


		//float vertices[12] = {		-0.5f,  0.5f, 0.0f,
		//							-0.5f, -0.5f, 0.0f,
		//							 0.5f, -0.5f, 0.0f,
		//							 0.5f,  0.5f, 0.0f
		//							};

		//uint indices[6] = { 0,1,3,3,1,2 };

		//mesh = new Mesh(vertices, 12,indices,6);
	}

	void createBody(Layer* layer, float x, float y, float width, float height, uint color)
	{
		b2BodyDef def;
		def.type = b2_staticBody;
		def.position.Set(x, y);
		def.userData = this;
		b2Body* m_body = world->CreateBody(&def);
		b2PolygonShape shape;
		b2Vec2 vecs[4];
		vecs[0] = b2Vec2(0, 0);
		vecs[1] = b2Vec2(0, height);
		vecs[2] = b2Vec2(width, height);
		vecs[3] = b2Vec2(width, 0);

		shape.Set(vecs, 4);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 100.0f;
		fixtureDef.friction = 93.0f;
		m_body->CreateFixture(&fixtureDef);
		layer->add(new RenderablePoly(math::vec2(x, y), math::b2Vec2ToVec2(vecs, 4), 4, color));
		uint bpp, width2, height2;
			
	}

	void createPoly(Layer* layer, float x, float y, uint vertex, uint size, uint color)
	{
		b2BodyDef def;
		def.type = b2_staticBody;
		def.position.Set(x, y);
		def.userData = this;
		b2Body* m_body = world->CreateBody(&def);
		b2PolygonShape shape;
		b2Vec2* vecs = math::getPoly(vertex, size, true);
		shape.Set(vecs, vertex);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 100.0f;
		fixtureDef.friction = 93.0f;
		m_body->CreateFixture(&fixtureDef);
		layer->add(new RenderablePoly(math::vec2(x, y), math::b2Vec2ToVec2(vecs, vertex), vertex, color));
	}

	void tick() override
	{
		std::string s = utils::toString(getFPS()) + " fps";
		fps->text = s;
		fps2->text = s;
	}

	bool toggle = false;
	math::vec2 offset;
	bool press = false;
	void update(float timeElapsed) override
	{
		float dx = 0, dy = 0;
		if (Window::isKeyDown(GLFW_KEY_A))
		{
			dx--;
		}
		if (Window::isKeyDown(GLFW_KEY_D))
		{
			dx++;
		}
		if (Window::isKeyDown(GLFW_KEY_W))
		{
			dy--;
		}
		if (Window::isKeyDown(GLFW_KEY_S))
		{
			dy++;
		}

		if (Window::isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{
			math::vec2 mouse = Window::getMousePos(camera::Camera::getInstance()->getLayer(2)->getProjectionMatrix());
			press = frame->isInside(mouse);
			if (press)
				offset = mouse - frame->getPosition();
		}
		if (Window::isMouseButtonDown(GLFW_MOUSE_BUTTON_1))
		{
			math::vec2 mouse = Window::getMousePos(camera::Camera::getInstance()->getLayer(2)->getProjectionMatrix());
			if (press)
				frame->setPosition(mouse - offset);
		}

		e2->m_body->SetLinearVelocity(b2Vec2(dx * 10, dy * 10));
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
		world->Step(timeElapsed, velocityIterations, positionIterations);
		e->update(timeElapsed);
		e2->update(timeElapsed);

		camera::Camera::getInstance()->update(timeElapsed);
	}

	void render() override
	{
		//greet::managers::GameStateManager::render();
		camera::Camera::getInstance()->render();
		//renderer3d->submit(mesh);
	}

	void windowResize(int width, int height) override
	{
		camera::Camera::getInstance()->getLayer(0)->setProjectionMatrix(math::mat3::orthographic(0, (float)width / 20.0f, 0, (float)height / 20.0f)*math::mat3::translate((width - 960) / 40.0f, (height - 540) / 40.0f));
		camera::Camera::getInstance()->getLayer(1)->setProjectionMatrix(math::mat3::orthographic(0, (float)width / 20.0f, 0, (float)height / 20.0f)*math::mat3::translate((width - 960) / 40.0f, (height - 540) / 40.0f));
		camera::Camera::getInstance()->getLayer(2)->setProjectionMatrix(math::mat3::orthographic(0, (float)width, 0, (float)height)*math::mat3::translate((width - 960) / 2, (height - 540) / 2));
		//camera::Camera::getInstance()->setViewport(0, 0, width, height* 9 / 16);
	}

	void joystickState(unsigned int joystick, bool connect) override
	{

	}

};

void game()
{
}

int main()
{
	Core game;
	game.start();
	return 0;
}

#else

#include <internal\app.h>
#include <entity\entity.h>
#include <graphics\gui\frame.h>
#include <graphics\gui\panel.h>
#include <graphics\gui\slider.h>
#include <graphics\gui\button.h>
#include <graphics\atlas\atlasmanager.h>
#include <graphics\renderers/batchrenderer.h>
#include <graphics\shaders\shaderfactory.h>
#include <graphics\layers\box2dlayer.h>
#include <graphics/renderers/batchrenderer3d.h>
#include <graphics/renderers/renderer3d.h>
#include <graphics/models/EntityModel.h>
#include <graphics/models/camera.h>
#include <utils/colorutils.h>
#include <utils/objutils.h>
#include <math/math_func.h>
#include <graphics/models/light.h>
#include <event/keylistener.h>
#include <event/mouselistener.h>

#include <utils/dialogbox.h>
#include <drivers/driverdispatcher.h>
#include <drivers/lineardriver.h>
#include <drivers/driveradapter.h>

#include <graphics/layers/guilayer.h>

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
	Material* lightSourceMaterial;
	EntityModel* lightSource;

	Material* modelMaterial;
	EntityModel* model;

	Material* modelMaterial2;
	EntityModel* model2;

	std::vector<EntityModel> models;

	Camera* camera;
	Layer<Renderable>* uilayer;
	GUILayer* guilayer;
	Slider* slider;
	Frame* frame;
	Button* button;
	Label* fps;
	Renderable2D* cursor;
	Renderable2D* driverTest;


public:

	Core::~Core()
	{
		delete modelMaterial;
		delete model;
		delete modelMaterial2;
		delete model2;
		delete renderer3d;
		delete uilayer;
		delete guilayer;
	}

	void init()
	{
		EventDispatcher::addKeyListener(DISPATCHER_GUI+1, *this);
		EventDispatcher::addMouseListener(DISPATCHER_GUI + 1, *this);
		createWindow("Best Game Ever", 960, 540);
		setFrameCap(144);
		TextureManager::add(new Texture("res/textures/skybox.png", "skybox"));
		TextureManager::add(new Texture("res/textures/stallTexture.png", "stall"));
		TextureManager::add(new Texture("res/textures/cursor.png", "cursor"));
		TextureManager::add(new Texture("res/textures/mask.png", "mask"));
		TextureManager::add(new Texture("res/textures/mask2.png", "mask2"));

		camera = new Camera(math::vec3(0,0,0));
		renderer3d = new BatchRenderer3D(Window::getWidth(), Window::getHeight(), *camera,70,0.1f,100.0f);

		Shader* modelShader = new Shader("res/shaders/3dshader.vert", "res/shaders/3dshader.frag");
		Shader* lightSourceShader = new Shader("res/shaders/3dshader.vert", "res/shaders/3dshader.frag");
		Shader* modelShader2 = new Shader("res/shaders/3dshader.vert", "res/shaders/3dshader.frag");

		Mesh* lightSourceMesh = utils::loadObj("res/objs/cube.obj.gobj");
		lightSourceMaterial = new Material(lightSourceShader, TextureManager::get("skybox"));
		MaterialModel* lightSourceModelMaterial = new MaterialModel(lightSourceMesh, *lightSourceMaterial);
		lightSource = new EntityModel(*lightSourceModelMaterial, math::vec3(25, 25, 12.5), math::vec3(1.0f, 1.0f, 1.0f), math::vec3(0.0f, 0.0f, 0.0f));

		Mesh* modelMesh = utils::loadObj("res/objs/stall.obj.gobj");
		modelMaterial = new Material(modelShader, TextureManager::get("stall"));
		modelMaterial->setReflectivity(0.1)->setShineDamper(1);
		MaterialModel* modelModelMaterial = new MaterialModel(modelMesh, *modelMaterial);
		model = new EntityModel(*modelModelMaterial, math::vec3(0.0f, 0.0f, -25), math::vec3(1.0f, 1.0f, 1.0f), math::vec3(0.0f, 0.0f, 0.0f));

		Mesh* modelMesh2 = utils::loadObj("res/objs/dragon.obj.gobj");
		modelMaterial2 = new Material(modelShader2, NULL);
		MaterialModel* modelModelMaterial2 = new MaterialModel(modelMesh2, *modelMaterial2);
		model2 = new EntityModel(*modelModelMaterial2, math::vec3(10.0f, 0.0f, -25), math::vec3(1.0f, 1.0f, 1.0f), math::vec3(0.0f, 0.0f, 0.0f));

		for (uint i = 0;i < 2000;i++)
		{
			models.push_back(EntityModel(*modelModelMaterial, math::vec3(random()*100, random() * 100, random() * 100), math::vec3(1.0f, 1.0f, 1.0f), math::vec3(random() * 360, random() * 360, random() * 360)));
		}

		Light* l = new Light(math::vec3(25, 25,12.5), 0xffffffff);
		modelShader->enable();
		l->setToUniform(modelShader, "light");
		modelShader->disable();
		modelShader2->enable();
		l->setToUniform(modelShader2, "light");
		modelShader2->disable();
		delete l;

		FontManager::add(new Font("Anonymous Pro.ttf", "anonymous", 72));

		uilayer = new Layer<Renderable>(new BatchRenderer(), ShaderFactory::DefaultShader(), math::mat3::orthographic(0.0f, (float)Window::getWidth(), 0.0f, (float)Window::getHeight()));
		uint colorPink = ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(300 /360.0f, 3));
		fps = new Label("144 fps", math::vec2(50, 300), "anonymous", 72, ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 9)));
		cursor = new Renderable2D(math::vec2(0,0),math::vec2(32,32),0xffffffff,new Sprite(TextureManager::get("cursor")->getTexID(),32,32, math::vec2(0, 0), math::vec2(1, 1)), new Sprite(TextureManager::get("mask")->getTexID(),256,256,math::vec2(0,0),math::vec2(1,1)));
		//drivers::DriverDispatcher::addDriver(new drivers::LinearDriver(driverTest->m_position.x, -20, 0.5f, true, new drivers::DriverAdapter()));

		guilayer = new GUILayer(new BatchRenderer(),ShaderFactory::DefaultShader());
		slider = new Slider(math::vec2(10,100),math::vec2(200,30),0,255,1);
		button = new Button(math::vec2(10,120+30),math::vec2(100,40),"Test");
		frame = new Frame(math::vec2(10, 10), math::vec2(500, 500),"GUI Frame");
		uilayer->add(fps);
		frame->add(slider);
		frame->add(button);
		guilayer->add(frame);

		uilayer->add(cursor);
		//drivers::DriverDispatcher::addDriver(new drivers::LinearDriver(frame->m_position.x, 100, 5, true, new drivers::DriverAdapter()));

		renderer3d->submit(model);
		renderer3d->submit(model2);
		renderer3d->submit(lightSource);
		//for (uint i = 0;i < 2000;i++)
		//{
		//	renderer3d->submit(&models[i]);
		//}
	}

	float random()
	{
		return (float)((double)rand() / (RAND_MAX));
	}

	void tick()
	{
		std::string s = utils::toString(getFPS()) + " fps";
		fps->text = s;
	}

	float hue = 0;

	void update(float elapsedTime)
	{
		//fps->text = utils::toString(slider->getValue());
		if(Window::isJoystickConnected(0))
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
		model->update(elapsedTime);
		model2->update(elapsedTime);
		lightSource->update(elapsedTime);
		for (uint i = 0;i < 2000;i++)
		{
			models[i].update(elapsedTime);
		}
		uilayer->update(elapsedTime);
		guilayer->update(elapsedTime);
		hue += elapsedTime / 3.0f;
		while (hue >= 1)
			hue--;
		cursor->m_color = ColorUtils::vec3ToColorHex(ColorUtils::HSVtoRGB(hue, 1, 1));
	}

	bool onPressed(const KeyPressedEvent& e) const override
	{
		if (e.getButton() == GLFW_KEY_F5)
		{
			Shader* modelShader = new Shader("res/shaders/3dshader.vert", "res/shaders/3dshader.frag");
			Shader* modelShader2 = new Shader("res/shaders/3dshader.vert", "res/shaders/3dshader.frag");
			modelMaterial->setShader(modelShader);
			modelMaterial2->setShader(modelShader2);
			Light* l = new Light(math::vec3(25, 25, 12.5), 0xffffffff);
			modelShader->enable();
			l->setToUniform(modelShader, "light");
			modelShader->disable();
			modelShader2->enable();
			l->setToUniform(modelShader2, "light");
			modelShader2->disable();
			delete l;
		}
		return false;
	}

	bool onReleased(const KeyReleasedEvent& e)  const override
	{
		return false;
	}

	bool onPressed(const MousePressedEvent& e) const  override
	{
		return false;
	}

	bool onReleased(const MouseReleasedEvent& e)  const  override
	{
		return false;
	}

	bool onMoved(const MouseMovedEvent& e)  const override
	{
		cursor->setPosition(math::vec2(e.getX(), e.getY()));

		return false;
	}

	void render()
	{
		renderer3d->begin();
		renderer3d->flush();
		renderer3d->end();
		guilayer->render();
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
#endif
