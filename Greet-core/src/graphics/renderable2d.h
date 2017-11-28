#pragma once

#include <cstddef>
#include <math/Maths.h>
#include <graphics/buffers/Buffer.h>
#include <graphics/buffers/IndexBuffer.h>
#include <graphics/buffers/VertexArray.h>
#include <graphics/shaders/Shader.h>
#include <graphics/textures/Texture.h>
#include "Renderable.h"
#include <internal/GreetTypes.h>
#include "Sprite.h"

namespace Greet{

	struct VertexData
	{
		vec2 vertex;
		vec2 texCoord;
		float texID;
		uint color;
		vec2 maskTexCoord;
		float maskTexID;
	};

	class Renderable2D : public Renderable
	{
	public:
		uint m_color;
		vec2 m_position;
		vec2 m_size;
	protected:
		Sprite* m_sprite;
		Sprite* m_mask;
	protected:

	public:
		Renderable2D(const vec2& position,const vec2& size, uint color, Sprite* sprite, Sprite* mask)
			: m_position(position),m_size(size), m_color(color), m_sprite(sprite), m_mask(mask)
		{	

		}
		
		Renderable2D()
			: m_position(vec2(0, 0)), m_size(vec2(1, 1)), m_color(0xffffffff), m_sprite(new Sprite()), m_mask(new Sprite())
		{

		}
		
		void setColor(uint color) override { m_color = color; }
		inline uint getColor() const override { return m_color;}
		void setPosition(const vec2& position) override { m_position = position; }
		inline const vec2& getPosition() const override { return m_position;}
		void setSize(const vec2& size) override { m_size = size; }
		inline const vec2& getSize() const override { return m_size;}

		virtual ~Renderable2D()
		{
			delete m_sprite;
		}

		virtual void submit(Renderer2D* renderer) const override
		{
			if (render)
				renderer->submit(this);
		}

		virtual bool update(float timeElapsed) override 
		{ 
			if(m_sprite)
				return m_sprite->update(timeElapsed); 
			return false;
		}

		inline uint getTexID() const { return m_sprite == NULL ? 0 : m_sprite->getTextureID(); }
		inline uint getMaskTexID() const { return m_mask == NULL ? 0 : m_mask->getTextureID(); }
		inline const vec2& getTexPos() const { return m_sprite == NULL ? vec2(0, 0) : m_sprite->getTexPos(); }
		inline const vec2& getTexSize() const { return m_sprite == NULL ? vec2(1, 1) : m_sprite->getTexSize(); }
		inline const vec2& getMaskTexPos() const { return m_mask == NULL ? vec2(0, 0) : m_mask->getTexPos(); }
		inline const vec2& getMaskTexSize() const { return m_mask == NULL ? vec2(1, 1) : m_mask->getTexSize(); }
		inline Sprite& getSprite() const { return *m_sprite; }
		inline Sprite& getMask() const { return *m_mask; }
	};
}
