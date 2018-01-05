#include <Greet.h>

#include <random>

using namespace Greet;

class Core : public App
{
private:
	Shader* batchShader;
	BatchRenderer2D<RenderableSquare>* batchRenderer2D;
	RenderableSquare* renderable;

public:
	
	Core::~Core()
	{
		
	}

	void Init() override
	{
		CreateWindow("BatchRenderer2D test", 960, 540);
		SetFrameCap(144);

		TextureManager::Add(new Texture2D("res/textures/test.png","test"));

		batchShader = Shader::FromFile("res/shaders/test2dshader.shader");
		batchRenderer2D = new BatchRenderer2D<RenderableSquare>();
		renderable = new RenderableSquare(Vec2(-0.5, 0.5), Vec2(1, -1), TextureManager::Get2D("test"), Vec2(0,0), Vec2(0.5f,0.5f));
	}

	void Tick() override
	{
		std::string s = StringUtils::to_string(GetFPS()) + " fps | " + StringUtils::to_string(GetUPS())+ " ups";
		Window::SetTitle("BatchRenderer2D test | " + s);
	}

	void Update(float elapsedTime) override
	{
		
	}

	void Render() override
	{
		batchShader->Enable();
		batchRenderer2D->Begin();
		batchRenderer2D->Submit(renderable);
		batchRenderer2D->End();
		batchRenderer2D->Draw();
		batchShader->Disable();
	}
	
	void WindowResize(int width, int height) override
	{

	}
};

#include <fstream>
int main()
{
	Core game;
	game.Start();
}
