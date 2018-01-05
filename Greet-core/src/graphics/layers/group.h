#pragma once

#include <graphics/renderables/Renderable2D.h>

#define __PRETTY_FUNCTION__ __func__
namespace Greet {
	class Group : public Renderable
	{
	protected:
		std::vector<Renderable*> m_renderables;
		Mat3 m_transformationMatrix;
	public:
		bool enable;
	public:
		Group(const Vec2& position);
		Group(const Mat3& transform);
		virtual ~Group();
		virtual void Add(Renderable* renderable);
		virtual void Remove(Renderable* renderable);
		virtual bool Update(float timeElapsed) override;
		virtual void Begin(BatchRenderer2D* renderer) const override;
		virtual void Submit(BatchRenderer2D* renderer) const override;
		virtual void End(BatchRenderer2D* renderer) const override;
		virtual void Draw(BatchRenderer2D* renderer) const override;
		virtual int GetVertexSize() const override { return sizeof(Renderable2DVertex); };

		void SetEnable(bool enable) { Group::enable = enable;}
		void SetTransformationMatrix(Mat3 transformationMatrix) {m_transformationMatrix = transformationMatrix;}
	};

}
