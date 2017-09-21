#include "entitymodel.h"

namespace Greet {
	EntityModel::EntityModel(const MaterialModel& model, float x, float y, float z, float sx, float sy, float sz, float rx, float ry, float rz)
		: m_model(model), m_position(vec3(x,y,z)), m_scale(vec3(sx,sy,sz)), m_rotation(vec3(rx,ry,rz))
	{
		updateTransformation();
	}

	EntityModel::EntityModel(const MaterialModel& model, vec3 position, vec3 scale, vec3 rotation)
		: m_model(model), m_position(position), m_scale(scale), m_rotation(rotation)
	{
		updateTransformation();
	}

	void EntityModel::update(float timeElapsed)
	{
		
		if (m_hasChanged)
		{
			updateTransformation();
		}
	}

	void EntityModel::updateTransformation()
	{
		m_transformationMatrix = mat4::transformationMatrix(m_position, m_rotation, m_scale);
		m_hasChanged = false;
	}
}