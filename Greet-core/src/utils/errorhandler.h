#pragma once

#include <internal/Greet_types.h>
#include <utils/utils.h>

#define Greet_ERROR_IMAGE_FORMAT	BIT(0)
#define Greet_ERROR_IMAGE_READ		BIT(1)
#define Greet_ERROR_IMAGE_BPP		BIT(2)
#define Greet_ERROR_IMAGE_CROP		BIT(3)
#define Greet_ERROR_GOBJ_FORMAT		BIT(4)
#define Greet_ERROR_GOBJ_READ		BIT(5)
#define Greet_ERROR_SHADER_VERTEX	BIT(6)
#define Greet_ERROR_SHADER_FRAGMENT	BIT(7)
#define Greet_ERROR_SHADER_GEOMETRY	BIT(8)
#define Greet_ERROR_MESH_LOCATION	BIT(8)
#define Greet_ERROR_MANAGER_ADD		BIT(9)
#define Greet_ERROR_MANAGER_GET		BIT(10)
#define Greet_ERROR_MANAGER_REMOVE	BIT(11)

namespace Greet { namespace ErrorHandle {

	static ulong errorCode;
	static void setErrorCode(ulong errorCode) { ErrorHandle::errorCode |= errorCode; };
	static ulong getErrorCode() { return errorCode;  }
	static void resetErrorCode() { ErrorHandle::errorCode = 0; }
}}