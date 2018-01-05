#pragma once

#include <graphics/renderers/BatchRenderer2D.h>

namespace Greet 
{

	class Renderable
	{
		friend class BatchRenderer2D;
	public:
		bool render = true;
	public:
		virtual int GetVertexSize() const = 0;
		virtual void Begin(BatchRenderer2D* renderer) const {};
		virtual void Submit(BatchRenderer2D* renderer) const;
		virtual void End(BatchRenderer2D* renderer) const {};

		virtual bool Update(float timeElapsed) { return false; }
		bool IsValidVertex(BatchRenderer2D* renderer) const;
	protected:
		virtual void Draw(BatchRenderer2D* renderer) const = 0;

	};
}