#pragma once

#include <internal/greet_types.h>
#include <utils/utils.h>

#define GREET_ERROR_IMAGE_FORMAT	BIT(0)
#define GREET_ERROR_IMAGE_READ		BIT(1)
#define GREET_ERROR_IMAGE_BPP		BIT(2)
#define GREET_ERROR_IMAGE_CROP		BIT(3)
#define GREET_ERROR_GOBJ_FORMAT		BIT(4)
#define GREET_ERROR_GOBJ_READ		BIT(5)
#define GREET_ERROR_SHADER_VERTEX	BIT(6)
#define GREET_ERROR_SHADER_FRAGMENT	BIT(7)
#define GREET_ERROR_SHADER_GEOMETRY	BIT(8)

namespace greet { namespace utils { namespace ErrorHandle {

	static uint errorCode;
	static void setErrorCode(uint errorCode) { ErrorHandle::errorCode |= errorCode; };
	static uint getErrorCode() { return errorCode;  }
	static void resetErrorCode() { ErrorHandle::errorCode == 0; }
}}}