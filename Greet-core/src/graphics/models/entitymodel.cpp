#include "entitymodel.h"

namespace greet { namespace model {
	EntityModel::EntityModel(const MaterialModel& model, float x, float y, float z, float sx, float sy, float sz, float rx, float ry, float rz)
		: m_model(model), m_position(math::vec3(x,y,z)), m_scale(math::vec3(sx,sy,sz)), m_rotation(math::vec3(rx,ry,rz))
	{

	}

	EntityModel::EntityModel(const MaterialModel& model, math::vec3 position, math::vec3 scale, math::vec3 rotation)
		: m_model(model), m_position(position), m_scale(scale), m_rotation(rotation)
	{
	
	}

	void EntityModel::update(float timeElapsed)
	{
		
		if (m_hasChanged)
		{
			m_transformationMatrix = math::mat4::transformationMatrix(m_position, m_rotation, m_scale);
			m_hasChanged = false;
		}
	}
}}