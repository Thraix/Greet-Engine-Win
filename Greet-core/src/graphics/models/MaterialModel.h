#pragma once

#include <graphics/models/Material.h>
#include <graphics/models/mesh.h>

namespace greet { namespace model { 

	class MaterialModel
	{
	private:
		static uint s_current_id;
		uint m_id;
		const Material& m_material;
		Mesh* m_mesh;
	public:
		MaterialModel(Mesh* mesh, const Material& material);
		virtual ~MaterialModel();

		inline const Material& getMaterial() const { return m_material; }
		inline const Mesh& getMesh() const { return *m_mesh; }
		bool operator < (const MaterialModel & rhs)
		{
			uint idl = getMaterial().getTexture().getTexID();
			uint idr = rhs.getMaterial().getTexture().getTexID();
			if (idl < idr) { return true; }
			if (idl > idr) { return false; }
			return (idl < idr);
		}

		inline uint getId() const { return m_id; }

		bool operator==(const MaterialModel& second) const;
	};
}}