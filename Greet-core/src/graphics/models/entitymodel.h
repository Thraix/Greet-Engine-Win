#pragma once

#include <graphics/models/MaterialModel.h>
namespace greet { namespace model {


	class EntityModel {
	private:
		const MaterialModel& m_model;
	private:
		math::vec3 m_position;
		math::vec3 m_scale;
		math::vec3 m_rotation;
		math::mat4 m_transformationMatrix;
		bool m_hasChanged;
	public:
		EntityModel(const MaterialModel& model, float x, float y, float z, float sx, float sy, float sz, float rx, float ry, float rz);
		EntityModel(const MaterialModel& model, math::vec3 position, math::vec3 scale, math::vec3 rotation);
		
		inline const MaterialModel& getMaterialModel() const { return m_model; }
		inline const math::mat4& getTransformationMatrix() const { return m_transformationMatrix; }
		void update(float timeElapsed);

		void move(float dx, float dy, float dz) { m_position.x += dx;m_position.y = dy; m_position.z = dz; m_hasChanged = true; }
		void scale(float x, float y, float z) { m_scale.x += x;m_scale.y += y; m_scale.z += z; m_hasChanged = true; }
		void rotate(float x, float y, float z) { m_rotation.x += x;m_rotation.y += y; m_rotation.z += z; m_hasChanged = true; }
	};
}}