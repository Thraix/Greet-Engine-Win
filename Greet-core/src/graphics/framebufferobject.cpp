#include "framebufferobject.h"

namespace greet { namespace graphics{

	FrameBufferObject::FrameBufferObject(uint width, uint height)
		: m_width(width), m_height(height)
	{
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER,m_fbo);


		// Color buffer
		uint texId;
		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texId, 0);
		m_colorTexture = new Texture2D(texId,m_width,m_height,"");

		glGenRenderbuffers(1,&m_depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER,m_depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT,m_width,m_height);
		
		glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,m_depthBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBufferObject::~FrameBufferObject()
	{
		glDeleteFramebuffers(1, &m_fbo);
		delete m_colorTexture;
		glDeleteBuffers(1,&m_depthBuffer);
	}

	void FrameBufferObject::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER,m_fbo);
		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0,0,m_width,m_height);
	}

	void FrameBufferObject::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0,0,Window::getWidth(),Window::getHeight());
	}

}}