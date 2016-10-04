#pragma once

#include <logging/logger.h>
#include <internal/greetgl.h>
#include <iostream>
#include <internal/greet_types.h>
#include <graphics/textures/imagefactory.h>
#include <fstream>
#include <utils/errorhandler.h>

namespace greet {namespace utils{
	
	inline void printImage(BYTE* bits, uint width, uint height, uint bpp)
	{
		bpp = bpp >> 3;
		for (uint y = 0;y<height;y++)
		{
			BYTE* pixel = (BYTE*)bits;
			for (uint x = 0;x<width;x++)
			{
				std::string s = "pixel(" + utils::toString(x) + "," + utils::toString(y) + ")";
				s += "(" + utils::toString((uint)pixel[FI_RGBA_RED]) + ",";
				s += utils::toString((uint)pixel[FI_RGBA_GREEN]) + ",";
				s += utils::toString((uint)pixel[FI_RGBA_BLUE]) + ")";
				pixel += bpp;
				LOG_INFO(s);
			}
			bits += bpp*width;
		}
	}

	inline BYTE* flipImage(BYTE*& bits, uint width, uint height, uint bpp)
	{
		bpp = bpp >> 3;
		BYTE* result = new BYTE[width*height*bpp];
		result += bpp*width*height;
		BYTE* row = (BYTE*)bits;
		for (uint y = 0;y < height;y++)
		{
			for (uint x = 0;x < width;x++)
			{
				result -= bpp;
				memcpy(result,row,bpp);

				row += bpp;
			}
		}

		delete[] bits;
		bits = result;
		return bits;
	}

	inline BYTE* loadImage(const char* filepath, uint* width, uint* height, uint* bpp)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

		FIBITMAP *dib = nullptr;

		fif = FreeImage_GetFileType(filepath, 0);

		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filepath);

		if (fif == FIF_UNKNOWN)
		{
			LOG_ERROR("IMAGEUTILS","FreeImage file format is not supported or file not exist:", filepath);
			ErrorHandle::setErrorCode(GREET_ERROR_IMAGE_FORMAT);
			return graphics::ImageFactory::getBadFormatImage(width,height,bpp);
		}

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filepath);
		if (!dib)
		{
			LOG_ERROR("IMAGEUTILS", "FreeImage file Cannot be read:", filepath);
			ErrorHandle::setErrorCode(GREET_ERROR_IMAGE_READ);
			return graphics::ImageFactory::getCantReadImage(width,height,bpp);
		}


		BYTE* bits = FreeImage_GetBits(dib);

		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		*bpp = FreeImage_GetBPP(dib);
		if (*bpp != 24 && *bpp != 32)
		{
			LOG_ERROR("IMAGEUTILS", "Bits per pixel is not valid (24 or 32):", filepath);
			ErrorHandle::setErrorCode(GREET_ERROR_IMAGE_BPP);
			delete[] bits;
			return graphics::ImageFactory::getBadBPPImage(width,height,bpp);
		}

		//printImage(bits,*width, *height, *bpp);
		//return graphics::ImageFactory::getBadBPPImage(width, height, bpp);

		int size = (*width) * (*height) * (*bpp >> 3);
		BYTE* result = new BYTE[size];
		memcpy(result,bits,size);
		FreeImage_Unload(dib);
		//delete[] bits;
		return result;
	}

	inline void saveImageBytes(const char* filepath, const char* output)
	{
		uint width,height,bpp;
		BYTE* bits = loadImage(filepath,&width,&height,&bpp);

		std::ofstream fout;
		fout.open(output, std::ios_base::binary | std::ios_base::out);
		fout.write((char*) &bits, width*height*bpp/8);

		fout.close();
	}
}}
