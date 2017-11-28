#pragma once

#include <logging/Log.h>
#include <internal/GreetGL.h>
#include <internal/GreetTypes.h>
#include <utils/ImageUtils.h>
#include <FreeImage.h>
#include <internal/GreetTypes.h>

namespace Greet {
	class Texture
	{
	protected:
		uint m_texId;
		uint m_textureType;
		std::string m_name;
	public:
		Texture(const std::string& name, uint textureType);
		Texture(uint texId, const std::string& name, uint textureType);
		virtual ~Texture();
		virtual void enable() const;
		virtual void disable() const;

		inline uint getTexId() const { return m_texId; }
		inline const std::string& getName() const { return m_name; }
	protected:
		inline void setTexId(uint texId) { m_texId = texId; }
	};

}
