#pragma once

#include <utils/log.h>
#include <FreeImage.h>
#include <iostream>
#include <greet_types.h>

namespace greet {namespace utils{
	inline BYTE* loadImage(const char* filepath, uint* width, uint* height, uint* bpp)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

		FIBITMAP *dib = nullptr;

		fif = FreeImage_GetFileType(filepath, 0);

		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filepath);

		if (fif == FIF_UNKNOWN)
		{
			GREET_ERROR("IMAGEUTILS","FreeImage file format is not supported: ", filepath);
			return nullptr;
		}

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filepath);
		if (!dib)
		{
			GREET_ERROR("IMAGEUTILS", "FreeImage file Cannot be read: ", filepath);
			return nullptr;
		}


		BYTE* bits = FreeImage_GetBits(dib);

		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		*bpp = FreeImage_GetBPP(dib);

		int size = *width* *height * *bpp / 8;
		BYTE* result = new BYTE[size];

		memcpy(result,bits,size);

		FreeImage_Unload(dib);
		return result;
	}
}}