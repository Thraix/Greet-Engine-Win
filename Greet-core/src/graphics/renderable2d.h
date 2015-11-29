#pragma once

#include <cstddef>
#include <math/maths.h>
#include <graphics/buffers/buffer.h>
#include <graphics/buffers/indexbuffer.h>
#include <graphics/buffers/vertexarray.h>
#include <graphics/shaders/shader.h>
#include "texture.h"
#include "renderable.h"
#include <greet_types.h>
#include "sprite.h"

namespace greet{ namespace graphics{

	struct VertexData
	{
		math::vec2 vertex;
		math::vec2 texCoord;
		float texID;
		uint color;
		math::vec2 selfVertex;
	};

	class Renderable2D : public Renderable
	{
	public:
		uint m_color;
		math::Transform m_transform;
	protected:
		Sprite* m_sprite;
	protected:

	public:
		Renderable2D(math::Transform transform, uint color, Sprite* sprite)
			: m_transform(transform), m_color(color), m_sprite(sprite)
		{	

		}
		Renderable2D()
			: m_transform(math::Transform()), m_color(0xffffffff), m_sprite(new Sprite())
		{

		}

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
			return m_sprite->update(timeElapsed); 
		}

		inline uint getTexID() const { return m_sprite==NULL ? 0 : m_sprite->getTextureID(); }
		inline uint getColor() const { return m_color; }
		inline const math::vec2& getTexPos() const { return m_sprite==NULL ? math::vec2(0,0) : m_sprite->getTexPos(); }
		inline const math::vec2& getTexSize() const { return m_sprite == NULL ? math::vec2(1, 1) : m_sprite->getTexSize(); }
		inline const math::Transform& getTransform() const { return m_transform; }
		inline Sprite& getSprite() const { return *m_sprite; }
	};
}}