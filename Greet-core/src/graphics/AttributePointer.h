#pragma once

#include <internal/GreetGL.h>
#include <internal/GreetTypes.h>

namespace Greet
{

	class AttributePointer
	{
	public:
		uint index;
		uint size;
		uint type;
		bool normalized;
		int stride;
		const void* pointer;

	public:
		AttributePointer(uint index, uint size, uint type, bool normalized, int stride, const void* pointer)
			: index(index), size(size),type(type),normalized(normalized), stride(stride), pointer(pointer)
		{
			
		}

		void SetPointer() const
		{
			GLCall(glEnableVertexAttribArray(index));
			GLCall(glVertexAttribPointer(index, size, type, normalized, stride, pointer));
			//GLCall(glDisableVertexAttribArray(location));
		}
	};
}