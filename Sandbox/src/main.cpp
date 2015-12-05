#include <ctime>

#include <greet.h>
#include <managers\atlasmanager.h>
#include <managers\gamestatemanager.h>
#include <managers\texturemanager.h>
#include <graphics\label.h>
#include <graphics\guis\panel.h>
#include <graphics\guis\textview.h>
#include <graphics\guis\button.h>
#include <graphics\renderable4poly.h>
#include <graphics\batchrenderer2d.h>
#include <graphics\shaders\shaderfactory.h>
#include <graphics\layers\box2dlayer.h>
#include <entity\entity.h>

using namespace greet;
using namespace graphics;

class Core : public greet::Greet
{
private:
	Layer* uilayer;
	Label* fps;
	Panel* m_gui;
	Renderable4Poly* m_poly1;
	Renderable2D* m_poly2;
	Box2DLayer* layer;

public:

public:
	Core()
	{

	}

	~Core()
	{
		delete uilayer;
		delete m_gui;
	}

	void init() override
	{
		createWindow("Best Game Ever", 960, 540);

		greet::managers::TextureManager::add(new Texture("res/textures/test.png", "test"));
		greet::managers::TextureManager::add(new Texture("res/textures/animation.png", "animation"));
		greet::managers::AtlasManager::add(new greet::graphics::Atlas("atlas32", 128, 32));
		greet::graphics::Atlas* atlas32 = greet::managers::AtlasManager::get("atlas32");


		atlas32->addTexture("animation", "res/textures/animation.png");
		atlas32->addTexture("animation2", "res/textures/animation.png");
		atlas32->addTexture("grass", "res/textures/test3.png");

		
		BatchRenderer2D *batch = new BatchRenderer2D();
		uilayer = new Layer(batch, ShaderFactory::DefaultShader(), math::mat3::orthographic(0.0f, (float)m_window->getWidth() / 2.0f, 0.0f, (float)m_window->getHeight() / 2.0f));
		fps = new Label("", "default", math::vec2(10, 0), 0xffff00ff, 16);
		uilayer->push(fps);
		m_poly2 = new Renderable2D(math::mat3::quad(200,200,50,50), 0xffffffff, atlas32->getSpriteFromSheet("animation",math::vec2(0,0), math::vec2(0.25, 0.25)));
		uilayer->push(m_poly2);
		m_window->setBackgroundColor(math::vec4(0.5f, 0.5f, 0.5f, 1.0f));
		m_gui = new Panel(new BatchRenderer2D(),ShaderFactory::DefaultShader(), math::mat3::orthographic(0.0f, (float)m_window->getWidth() / 2.0f, 0.0f, (float)m_window->getHeight() / 2.0f), math::vec2(10,10),math::vec2(120,100));
		
		m_gui->setBackgroundColor(0xff6666ff);

		TextView* tv = new TextView(math::vec2(10, 10), "default", 16, "textview", 0xffffffff);
		tv->setBackgroundColor(0xffff0000);
		tv->setForegroundColor(0xffff00ff);

		Button* button = new Button(math::vec2(10,36),math::vec2(100,20),"dank button");
		button->setBackgroundColor(0xffff00ff);
		button->setForegroundColor(0xff0000ff);

		button->setPressListener(&press);
		button->setReleaseListener(&release);

		m_gui->push(tv);
		m_gui->push(button);
		b2World* world = new b2World(b2Vec2(0,0));
		entity::Entity* e = new entity::Entity(math::vec2(200,200),math::vec2(50,50),world);
		e->m_body->SetAngularVelocity(1);
		layer = new Box2DLayer(new BatchRenderer2D(),ShaderFactory::DefaultShader(), math::mat3::orthographic(0.0f, (float)m_window->getWidth() / 2.0f, 0.0f, (float)m_window->getHeight() / 2.0f),world);
	}
	static void press(Button* button) { GREET_DEBUG("MAIN", "top kek press"); }
	static void release(Button* button) { GREET_DEBUG("MAIN", "top kek release"); }

	void tick() override
	{
		fps->setText(utils::getTime()+" | "+std::to_string(getFPS()) + " fps");
	}
	float frame = 0;
	bool toggle = false;
	void update(float timeElapsed) override
	{
		frame++;
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
		m_poly2->m_transform.init().translate(200,200).rotate(frame).translate(-25,-25).scale(50,50);
		m_gui->update(timeElapsed);
	}

	void render() override
	{
		//greet::managers::GameStateManager::render();
		m_gui->render();
		uilayer->render();
		layer->render();
	}

	void resize(int width, int height) override
	{
		uilayer->setProjectionMatrix(math::mat3::orthographic(0, (float)width/2.0f, 0, (float)height / 2.0f));
	}

	void joystickConnect(unsigned int joystick, bool connect) override
	{
		
	}

};

int main()
{
	Core game;
	game.start();
	return 0;
}