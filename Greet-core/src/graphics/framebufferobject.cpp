#include "framebufferobject.h"

namespace greet { namespace graphics{

	FrameBufferObject::FrameBufferObject()
	{
		glGenFramebuffers(1, &m_fbo);
		glGenTextures(1, &m_colorTexture);
		
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,);
	}

	FrameBufferObject::~FrameBufferObject()
	{
		glDeleteFramebuffers(1, &m_fbo);

	}

	void FrameBufferObject::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER,m_fbo);
	}

	void FrameBufferObject::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}}