#pragma once

#include <logging/log.h>
#include <internal/Greetgl.h>
#include <iostream>
#include <internal/Greet_types.h>
#include <graphics/textures/imagefactory.h>
#include <fstream>
#include <utils/errorhandler.h>

namespace Greet { namespace ImageUtils {
	
	inline void printImage(BYTE* bits, uint width, uint height, uint bpp)
	{
		bpp = bpp >> 3;
		for (uint y = 0;y<height;y++)
		{
			BYTE* pixel = (BYTE*)bits;
			for (uint x = 0;x<width;x++)
			{
				std::string s = "pixel(" + StringUtils::toString(x) + "," + StringUtils::toString(y) + ")";
				s += "(" + StringUtils::toString((uint)pixel[FI_RGBA_RED]) + ",";
				s += StringUtils::toString((uint)pixel[FI_RGBA_GREEN]) + ",";
				s += StringUtils::toString((uint)pixel[FI_RGBA_BLUE]) + ")";
				pixel += bpp;
				Log::info(s);
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
			Log::error("FreeImage file format is not supported or file not exist: ", filepath);
			ErrorHandle::setErrorCode(Greet_ERROR_IMAGE_FORMAT);
			return ImageFactory::getBadFormatImage(width,height,bpp);
		}

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filepath);
		if (!dib)
		{
			Log::error("FreeImage file Cannot be read: ", filepath);
			ErrorHandle::setErrorCode(Greet_ERROR_IMAGE_READ);
			return ImageFactory::getCantReadImage(width,height,bpp);
		}


		BYTE* bits = FreeImage_GetBits(dib);

		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		*bpp = FreeImage_GetBPP(dib);
		if (*bpp != 24 && *bpp != 32)
		{
			Log::error("Bits per pixel is not valid (24 or 32): ", filepath);
			ErrorHandle::setErrorCode(Greet_ERROR_IMAGE_BPP);
			delete[] bits;
			return ImageFactory::getBadBPPImage(width,height,bpp);
		}

		//printImage(bits,*width, *height, *bpp);
		//return ImageFactory::getBadBPPImage(width, height, bpp);

		int size = (*width) * (*height) * (*bpp >> 3);
		BYTE* result = new BYTE[size];
		memcpy(result,bits,size);
		FreeImage_Unload(dib);
		//delete[] bits;
		return result;
	}

	inline BYTE* cropImage(const BYTE* bits,  uint width,  uint height,  uint bpp,  uint cx,  uint cy,  uint cwidth,  uint cheight)
	{
		if (cx >= width || cy >= height || cx + cwidth > width || cy + cheight > height)
		{
			Log::error("Invalid bounds when cropping image. ", cx, ", ", cy, ", ", cwidth, ", ", cheight);
			ErrorHandle::setErrorCode(Greet_ERROR_IMAGE_CROP);
			return ImageFactory::getCropErrorImage(&width,&height,&bpp);
		}
		cy = height - cheight - cy;
		bpp = bpp >> 3;
		BYTE* result = new BYTE[cwidth*cheight*bpp];
		bits += (cx+cy*width)*bpp;
		for (uint y = 0;y < cheight;y++)
		{
			memcpy(result, bits, cwidth*bpp);
			bits += width*bpp;
			result += cwidth*bpp;
		}
		result -= cwidth*bpp*cheight;
		bits -= width*bpp*cheight;
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
