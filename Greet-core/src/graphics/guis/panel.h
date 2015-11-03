#pragma once

#include "gui.h"

namespace greet { namespace graphics {
	class Panel : public GUI
	{
	protected:
		Renderer2D* m_renderer;
		math::mat3 m_invProjectionMatrix;
		Shader* m_shader;
	public:
		Panel(Renderer2D* renderer, Shader* shader, math::mat3 projectionMatrix, math::vec2 pos, math::vec2 size);
		~Panel();
		void render() const;
		inline void setProjectionMatrix(math::mat3 projectionMatrix) { m_shader->setUniformMat3("pr_matrix", projectionMatrix); m_invProjectionMatrix = projectionMatrix.inverse(); }
		virtual void setUniforms() const {}
		inline Shader* getShader() const { return m_shader; }
		inline const math::mat3& getInvertedProjectionMatrix() { return m_invProjectionMatrix; }
	};
}}