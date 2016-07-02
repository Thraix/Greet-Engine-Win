#pragma once

#include <graphics\texture.h>
#include <math/maths.h>
#include <graphics\sprite.h>

namespace greet { namespace graphics{
	class Animation
	{
	private:
		Texture* m_texture;
		math::vec2 m_texPos;
		math::vec2 m_texSize;
		math::vec2 m_add;
		int m_image;
		int m_images;
		bool m_horizontalRead;
		float m_frameTime;
		float m_frameTimer;
	public:
		uint m_color;

	public:
		Animation(std::string texture_name, math::vec2 texPos, math::vec2 texSize, float frameTimer, int images, bool horizontalRead);
		Animation(Texture* texture, math::vec2 texPos, math::vec2 texSize, float frameTimer, int images, bool horizontalRead);
		Animation(uint color);
		~Animation();

		bool update(float elapsedTime);

		void setTexCoords(math::vec2 texPos, math::vec2 texSize);
		void setTexSize(math::vec2 texPos);
		void setTexPos(math::vec2 texSize);
		
		inline const math::vec2& getTexPos() const { return m_texPos+m_add*m_image; }
		inline const math::vec2& getTexSize() const { return m_texSize; }
		inline Texture* getTexture() const { return m_texture; }
	};
}}