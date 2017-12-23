#pragma once

#include <internal/GreetGL.h>
#include <internal/GreetTypes.h>

namespace Greet
{

	class AttributePointer
	{
	public:
		uint location;
		uint index;
		uint size;
		uint type;
		bool normalized;
		int stride;
		const void* pointer;

	public:
		AttributePointer(uint location, uint index, uint size, uint type, bool normalized, int stride, const void* pointer)
			: location(location), index(index), size(size),type(type),normalized(normalized), stride(stride), pointer(pointer)
		{
			
		}

		void SetPointer() const
		{
			GLCall(glEnableVertexAttribArray(location));
			GLCall(glVertexAttribPointer(index, size, type, normalized, stride, pointer));
			GLCall(glDisableVertexAttribArray(location));
		}
	};
}