#pragma once

#include <logging/logger.h>
#include <internal/greetgl.h>
#include <internal/greet_types.h>
#include <utils/imageutils.h>
#include <FreeImage.h>
#include <internal/greet_types.h>

namespace greet { namespace graphics{
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

}}
