#include "framebufferobject.h"

namespace Greet {

	FrameBufferObject::FrameBufferObject(uint width, uint height)
		: m_width(width), m_height(height)
	{
		glGenFramebuffers(1, &m_fbo);


		// Color buffer
		//attachDepthTexture();
		AttachColorTexture(GL_COLOR_ATTACHMENT0);

		//return;
		glBindFramebuffer(GL_FRAMEBUFFER,m_fbo);
		glGenRenderbuffers(1,&m_depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER,m_depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT,m_width,m_height);
		
		glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,m_depthBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBufferObject::~FrameBufferObject()
	{
		glDeleteFramebuffers(1, &m_fbo);
		glDeleteBuffers(1,&m_depthBuffer);
		for (auto it = m_colorTextures.begin();it != m_colorTextures.end();it++)
		{
			delete it->second;
		}
		m_colorTextures.clear();
		delete m_depthTexture;
	}

	void FrameBufferObject::AttachColorTexture(uint attachmentId)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		if (attachmentId < GL_COLOR_ATTACHMENT0 || attachmentId > GL_COLOR_ATTACHMENT15)
		{
			Log::Error("Color attachment is out of range: ",attachmentId);
			return;
		}
		if (m_colorTextures.find(attachmentId) != m_colorTextures.end())
		{
			Log::Error("The given attachment is already in use: ", attachmentId);
		}
		uint texId;
		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentId, GL_TEXTURE_2D, texId, 0);
		m_colorTextures.emplace(attachmentId,new Texture2D(texId,m_width,m_height,""));
		uint size = m_colorTextures.size();
		uint* colorBuffers = new uint[size];
		uint i = 0;
		for (auto it = m_colorTextures.begin();it != m_colorTextures.end();it++)
			colorBuffers[i++] = it->first;
		glDrawBuffers(size,colorBuffers);
		delete colorBuffers;
		glBindFramebuffer(GL_FRAMEBUFFER,0);
	}

	void FrameBufferObject::AttachDepthTexture()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		uint texId;
		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D,GL_DEPTH_TEXTURE_MODE,GL_INTENSITY);
		m_depthTexture = new Texture2D(texId,m_width,m_height,"");
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texId, 0);
		glBindFramebuffer(GL_FRAMEBUFFER,0);
	}

	void FrameBufferObject::Bind()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER,m_fbo);
		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0,0,m_width,m_height);
	}

	void FrameBufferObject::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0,0,Window::GetWidth(),Window::GetHeight());
	}

	Texture2D* FrameBufferObject::GetColorTexture(uint attachmentId) const 
	{ 
		auto it = m_colorTextures.find(attachmentId);
		if (it != m_colorTextures.end())
			return it->second;
		Log::Error("There is no Texture with the given attachmentId: ",attachmentId);
		return m_colorTextures.begin()->second;
	}
}