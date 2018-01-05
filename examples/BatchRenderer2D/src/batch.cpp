#include <Greet.h>

#include <random>

#define RENDERABLES_WIDTH 120
#define RENDERABLES_HEIGHT 300

using namespace Greet;

class Core : public App
{
private:
	Shader* batchShader;
	BatchRenderer2D* batchRenderer2D;
	Renderable2D* renderable;
	Mat3 projectionMatrix;
	Renderable2D** renderables;

public:
	
	Core::~Core()
	{
		
	}

	void Init() override
	{
		CreateWindow("BatchRenderer2D test", 960, 540);
		SetFrameCap(0);

		TextureManager::Add(new Texture2D("res/textures/test.png","test"));

		batchShader = Shader::FromFile("res/shaders/test2dshader.shader");
		std::vector<AttributePointer> attributes;
		attributes.push_back(AttributePointer(0, 2, GL_FLOAT, false, sizeof(Renderable2DVertex), (const GLvoid*)offsetof(Renderable2DVertex, Renderable2DVertex::position)));
		attributes.push_back(AttributePointer(1, 2, GL_FLOAT, false, sizeof(Renderable2DVertex), (const GLvoid*)offsetof(Renderable2DVertex, Renderable2DVertex::texCoord)));
		attributes.push_back(AttributePointer(2, 1, GL_FLOAT, false, sizeof(Renderable2DVertex), (const GLvoid*)offsetof(Renderable2DVertex, Renderable2DVertex::texId)));
		attributes.push_back(AttributePointer(3, 4, GL_UNSIGNED_BYTE, true, sizeof(Renderable2DVertex), (const GLvoid*)offsetof(Renderable2DVertex, Renderable2DVertex::color)));
		batchRenderer2D = new BatchRenderer2D(attributes);
		projectionMatrix = Mat3::Orthographic(0,Window::GetWidth(),0,Window::GetHeight());
		renderable = new Renderable2D(Vec2(0, 0), Vec2(10, 10), TextureManager::Get2D("test"), Vec2(0,0), Vec2(0.5f,0.5f));

		float xScale = Window::GetWidth() / (float)RENDERABLES_WIDTH;
		float yScale = Window::GetHeight() / (float)RENDERABLES_HEIGHT;
		renderables = new Renderable2D*[RENDERABLES_WIDTH*RENDERABLES_HEIGHT];
		for (int y = 0;y < RENDERABLES_HEIGHT;y++)
		{
			for (int x = 0;x < RENDERABLES_WIDTH;x++)
			{
				uint r = rand() % 255;
				uint g = rand() % 255;
				uint b = rand() % 255;
				renderables[x+y*RENDERABLES_WIDTH] = new Renderable2D(Vec2(x*xScale, y*yScale), Vec2(xScale, yScale), TextureManager::Get2D("test"), 0xff000000 | (r << 16) | (g << 8) | b);
			}
		}
		
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
		batchShader->SetUniformMat3("projectionMatrix", projectionMatrix);
		batchRenderer2D->Begin();
		for (int i = 0;i<RENDERABLES_WIDTH*RENDERABLES_HEIGHT;i++)
			batchRenderer2D->Submit(renderables[i]);
		//batchRenderer2D->Submit(renderable);
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
