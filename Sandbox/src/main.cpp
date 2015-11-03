#include <ctime>

#include <greet.h>
#include <managers\atlasmanager.h>
#include <managers\gamestatemanager.h>
#include <managers\texturemanager.h>
#include <graphics\label.h>
#include "game.h"
#include <graphics\guis\panel.h>
#include <graphics\guis\textview.h>
#include <graphics\guis\button.h>

using namespace greet;
using namespace graphics;

class Core : public greet::Greet
{
private:
	Layer* uilayer;
	Label* fps;
	Panel* m_gui;
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

		BatchRenderer2D *batch = new BatchRenderer2D();
		uilayer = new Layer(batch, ShaderFactory::LEDShader(), math::mat3::orthographic(0.0f, (float)m_window->getWidth() / 2.0f, 0.0f, (float)m_window->getHeight() / 2.0f));

		fps = new Label("", "default", math::vec2(10, 0), 0xffff00ff, 16);
		uilayer->push(fps);
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
		greet::managers::GameStateManager::set(new Game(2));

	}
	static void press(Button* button) { GREET_DEBUG("MAIN", "top kek press"); }
	static void release(Button* button) { GREET_DEBUG("MAIN", "top kek release"); }

	void tick() override
	{
		fps->setText(utils::getTime()+" | "+std::to_string(getFPS()) + " fps");
	}

	bool toggle = false;
	void update(float timeElapsed) override
	{
		greet::managers::GameStateManager::update(timeElapsed);
		m_gui->update(timeElapsed);
	}

	void render() override
	{
		//greet::managers::GameStateManager::render();
		//uilayer->render();
		m_gui->render();
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