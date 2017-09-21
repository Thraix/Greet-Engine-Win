#pragma once



// Coordinates in the texture file
//
//                               u3
//  |----------------------------|
//  |                         u2 |
//  |-------------------------|  |
//  |      u1                 |  |
//  |------|                  |  |______________________
//  |   u0 |                  |  |  |      |     |     |
//  |---|  |                  |  |  |      |     |     |
//  |   | _|__________________|_ |__|_ v0  |     |     |
//  |    /                      \          |     |     |
//  |   /   __________________   \_________|_ v1 |     |
//  |   |  |                  |  |               |     |
//  |   |  |                  |  |               |     |
//  |   |  |                  |  |               |     |
//  |   |  |                  |  |               |     |
//  |   |  |                  |  |               |     |
//  |   |  |                  |  |               |     |
//  |   |  |                  |  |               |     |
//  |   |  |__________________|  |_______________|_ v2 |
//  |   \                        /                     |
//  |    \______________________/______________________|_ v3




#include <math/maths.h>
#include <graphics/renderable.h>
#include <internal/Greet_types.h>
#include <graphics/textures/texturemanager.h>

namespace Greet{
	struct BorderData
	{
		Texture* texture;
		uint borderSize;
		vec2 uv0;
		vec2 uv1;
		vec2 uv2;
		vec2 uv3;

		BorderData(const std::string& texturename, const uint& borderSize, const vec2& uv0, const vec2& uv1, const vec2& uv2, const vec2& uv3)
		: texture(TextureManager::get(texturename)), borderSize(borderSize), uv0(uv0), uv1(uv1), uv2(uv2), uv3(uv3)
		{

		}
		~BorderData()
		{

		}

		static BorderData* getDefaultBorderData()
		{
			return new BorderData("frame",5,vec2(0.0f,0.0f),vec2(5.0f/16.0f,5.0f/16.0f),vec2(11.0f/16.0f,11.0f/16.0f),vec2(1.0f,1.0f));
		}
	};

	class Border : public Renderable
	{
	private:
		vec2 m_size;
		vec2 m_position;
		BorderData* data;
		uint m_color;
	public:
		Border(const vec2& position,const vec2& size, const std::string& texturename, const uint& borderSize, const vec2& uv0, const vec2& uv1, const vec2& uv2, const vec2& uv3);
		Border(const vec2& position,const vec2& size, BorderData* data);
		virtual ~Border();
		void submit(Renderer2D* renderer) const override;
		bool update(float timeElapsed) override;
		void setPosition(const vec2& position) override;
		inline const vec2& getPosition() const override {return m_position; }
		void setSize(const vec2& size);
		inline const vec2& getSize() const override {return m_size;}
		void setColor(uint color) override { m_color = color; }
		uint getColor() const override { return m_color; }
	};

}
