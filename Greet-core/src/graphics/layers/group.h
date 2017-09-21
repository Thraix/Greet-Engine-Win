#pragma once

#include <graphics/renderable2d.h>
#define __PRETTY_FUNCTION__ __func__
namespace Greet {
	class Group : public Renderable
	{
	protected:
		std::vector<Renderable*> m_renderables;
		mat3 m_transformationMatrix;
	public:
		bool enable;
	public:
		Group(const vec2& position);
		Group(const mat3& transform);
		virtual ~Group();
		virtual void add(Renderable* renderable);
		virtual bool update(float timeElapsed);
		virtual void begin(Renderer2D* renderer) const override;
		virtual void submit(Renderer2D* renderer) const override;
		virtual void end(Renderer2D* renderer) const override;

		void setEnable(bool enable) { Group::enable = enable;}
		void setTransformationMatrix(mat3 transformationMatrix) {m_transformationMatrix = transformationMatrix;}

		void setColor(uint color) override { Log::warning("THIS DOES NOTHING",__PRETTY_FUNCTION__); }
		inline uint getColor() const override { Log::warning("THIS DOES NOTHING",__PRETTY_FUNCTION__);return 0xffffffff;}
		void setPosition(const vec2& position) override { Log::warning("THIS DOES NOTHING",__PRETTY_FUNCTION__); }
		inline const vec2& getPosition() const override { Log::warning("THIS DOES NOTHING",__PRETTY_FUNCTION__);return vec2(0,0);}
		void setSize(const vec2& size) override { Log::warning("THIS DOES NOTHING",__PRETTY_FUNCTION__); }
		inline const vec2& getSize() const override { Log::warning("THIS DOES NOTHING",__PRETTY_FUNCTION__);return vec2(1,1);}
	};

}
