#pragma once

#include <math\maths.h>
#include <greet_types.h>
#include "renderable.h"
#include "sprite.h"

namespace greet {namespace graphics {

	class Renderable4Poly : public Renderable
	{
	public:
		uint m_color;
	protected:
		Sprite* m_sprite;
		math::vec2 m_ul;
		math::vec2 m_ur;
		math::vec2 m_dr;
		math::vec2 m_dl;

	public:
		Renderable4Poly(const math::vec2& ul, const math::vec2& ur, const math::vec2& dr, const math::vec2& dl, const uint color, Sprite* sprite)
			: m_ul(ul), m_ur(ur), m_dr(dr), m_dl(dl), m_color(color), m_sprite(sprite)
		{

		}

		Renderable4Poly()
			: m_ul(math::vec2(0,0)), m_ur(math::vec2(0, 0)), m_dr(math::vec2(0, 0)), m_dl(math::vec2(0, 0)), m_color(0xffffffff), m_sprite(new Sprite())
		{

		}
		~Renderable4Poly()
		{
			delete m_sprite;
		}
		void submit(Renderer2D* renderer) const override
		{
			if (render)
				renderer->submit(this);
		}

		bool update(float timeElapsed) override
		{
			return m_sprite->update(timeElapsed);
		}

		inline uint getTexID() const { return m_sprite == NULL ? 0 : m_sprite->getTextureID(); }
		inline uint getColor() const { return m_color; }
		inline const math::vec2& getTexPos() const { return m_sprite == NULL ? math::vec2(0, 0) : m_sprite->getTexPos(); }
		inline const math::vec2& getTexSize() const { return m_sprite == NULL ? math::vec2(1, 1) : m_sprite->getTexSize(); }
		inline const math::vec2& getUL() const { return m_ul; }
		inline const math::vec2& getUR() const { return m_ur; }
		inline const math::vec2& getDR() const { return m_dr; }
		inline const math::vec2& getDL() const { return m_dl; }

		inline void setUL(const math::vec2& ul) { m_ul = ul; }
		inline void setUR(const math::vec2& ur) { m_ur = ur; }
		inline void setDR(const math::vec2& dr) { m_dr = dr; }
		inline void setDL(const math::vec2& dl) { m_dl = dl; }
		inline Sprite& getSprite() const { return *m_sprite; }
	};

}}