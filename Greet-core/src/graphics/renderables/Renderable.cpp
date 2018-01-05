#include "Renderable.h"

#include <graphics/renderers/BatchRenderer2D.h>

namespace Greet
{
	bool Renderable::IsValidVertex(BatchRenderer2D* renderer) const 
	{
		return renderer->GetVertexSize() == GetVertexSize();
	}

	void Renderable::Submit(BatchRenderer2D* renderer) const
	{
		if (render)
			renderer->Submit(this);
	}


}