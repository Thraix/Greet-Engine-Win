#include <graphics/gui/border.h>


namespace greet { namespace graphics {

	Border::Border(const math::vec2& position,const math::vec2& size, const std::string& texturename, const uint& borderSize, const math::vec2& uv0, const math::vec2& uv1, const math::vec2& uv2, const math::vec2& uv3)
	: m_position(position), m_size(size), m_color(0xffffffff), data(new BorderData(texturename,borderSize,uv0,uv1,uv2,uv2))
	{

	}

	Border::Border(const math::vec2& position, const math::vec2& size, BorderData* data)
	: m_position(position), m_size(size), m_color(0xffffffff), data(data)
	{

	}

	Border::~Border()
	{
		delete data;
	}

	void Border::submit(Renderer2D* renderer) const
	{

		math::vec2 borderSize(data->borderSize,data->borderSize);
		math::vec2 size(m_size-data->borderSize*2);
		// TODO: fix these errors
		// 0,0
		//renderer->submit(m_position,borderSize,data->texture->getTexID(),data->uv0,data->uv1-data->uv0,0xffffffff);
		// 1,0
		//renderer->submit(math::vec2(m_position.x+data->borderSize,m_position.y),math::vec2(size.x,borderSize.y),data->texture->getTexID(),math::vec2(data->uv1.x,data->uv0.y),math::vec2(data->uv2.x-data->uv1.x,data->uv1.y-data->uv0.y),0xffffffff);
		// 2,0
		//renderer->submit(math::vec2(m_position.x+size.x+borderSize.x,m_position.y),borderSize,data->texture->getTexID(),math::vec2(data->uv2.x,data->uv0.y),math::vec2(data->uv3.x-data->uv2.x,data->uv1.y-data->uv0.y),0xffffffff);
		// 0,1
		//renderer->submit(math::vec2(m_position.x,m_position.y+data->borderSize),math::vec2(data->borderSize,size.y),data->texture->getTexID(),math::vec2(data->uv0.x,data->uv1.x),math::vec2(data->uv1.x-data->uv0.x,data->uv2.x-data->uv1.x),0xffffffff);
		// 1,1
		//renderer->submit(math::vec2(m_position.x+data->borderSize,m_position.y+data->borderSize),math::vec2(size.x,size.y),data->texture->getTexID(),math::vec2(data->uv1.x,data->uv1.y),math::vec2(data->uv2.x-data->uv1.x,data->uv2.y-data->uv1.y),0xffffffff);
		// 2,1
		//renderer->submit(math::vec2(m_position.x+size.x+borderSize.x,m_position.y+data->borderSize),math::vec2(data->borderSize,size.y),data->texture->getTexID(),math::vec2(data->uv2.x,data->uv1.y),math::vec2(data->uv3.x-data->uv2.x,data->uv2.y-data->uv1.y),0xffffffff);
		// 0,2
		//renderer->submit(math::vec2(m_position.x,m_position.y+size.y+borderSize.y),borderSize,data->texture->getTexID(),math::vec2(data->uv0.x,data->uv2.x),math::vec2(data->uv1.x-data->uv0.x,data->uv3.x-data->uv2.x),0xffffffff);
		// 1,2
		//renderer->submit(math::vec2(m_position.x+data->borderSize,m_position.y+size.y+borderSize.y),math::vec2(size.x,borderSize.y),data->texture->getTexID(),math::vec2(data->uv1.x,data->uv2.y),math::vec2(data->uv2.x-data->uv1.x,data->uv3.y-data->uv2.y),0xffffffff);
		// 2,2
		//renderer->submit(math::vec2(m_position.x+size.x+borderSize.x,m_position.y+size.y+borderSize.y),borderSize,data->texture->getTexID(),math::vec2(data->uv2.x,data->uv2.y),math::vec2(data->uv3.x-data->uv2.x,data->uv3.y-data->uv2.y),0xffffffff);
	}

	bool Border::update(float timeElapsed)
	{
		return false;
	}

	void Border::setPosition(const math::vec2& position)
	{
		m_position = position;
	}

	void Border::setSize(const math::vec2& size)
	{
		m_size = size;
	}

}}
