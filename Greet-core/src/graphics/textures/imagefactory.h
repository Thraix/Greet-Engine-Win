#pragma once
#include <logging/log.h>
#include <FreeImage.h>
#include <internal/Greet_types.h>
#include <utils/utils.h>

namespace Greet { namespace ImageFactory {
		BYTE* getBadFormatImage(uint* width, uint* height, uint* bpp);
		BYTE* getBadBPPImage(uint* width, uint* height, uint* bpp);
		BYTE* getCantReadImage(uint* width, uint* height, uint* bpp);
		BYTE* getCropErrorImage(uint* width, uint* height, uint* bpp);
		BYTE* getErrorImage(uint* width, uint* height, uint* bpp, uint lightColor, uint darkColor);
		BYTE* getFrameImage(uint* width, uint* height, uint* bpp);
}}