#include "font.h"

namespace greet{ namespace graphics{

	Font::Font(const std::string& filename, const std::string& name)
	: m_name(name)
	{
		std::string png_file = "res/fonts/" + filename + "/font.png";
		std::string glyph_file = "res/fonts/" + filename + "/font.glyph";
		uint bpp;
		uint width, height;
		BYTE* bits = utils::loadImage(png_file.c_str(), &width, &height, &bpp);
		m_width = width;
		m_height = height;

		if (!checkValid(bpp,filename))
			return;

		m_glyphSizes = 1.0f / 16.0f;
		m_texture = new Texture(png_file.c_str(),"font_"+name);

		std::string file = readFile(glyph_file,bits);

		if (!loadFont(file, filename))
		{
			destroy();
		}
	}

	bool Font::checkValid(uint bpp, std::string filename)
	{
		if (bpp != 32)
		{
			GREET_ERROR("FONT", "Invalid file. No alpha channel: ", filename.c_str());
			return false;
		}
		else if (m_width != m_height)
		{
			GREET_ERROR("FONT", "Invalid file. Height != Width: ", filename.c_str());
			return false;
		}
		else if (m_width / 16 <= 0)
		{
			GREET_ERROR("FONT", "Invalid file. Size must contain 16x16 glyphs: ", filename.c_str());
			return false;
		}
		return true;
	}

	std::string Font::readFile(std::string filename, BYTE* bits)
	{
		if (!utils::file_exists(filename.c_str()))
		{
			return generateGlyphs(filename, bits, m_width, m_height);
		}
		else
		{
			return utils::read_file(filename.c_str());
		}
	}

	bool Font::loadFont(std::string file, std::string filename)
	{
		int lastIndex = 0;
		int index = file.find("\n", 0);
		std::string s;
		std::vector<float> data;

		// Load font data
		s = file.substr(lastIndex, index - lastIndex);
		data = getData(s);

		m_capY = data[1] * 16.0f / m_height;
		m_capHeight = data[3] * 16.0f / m_height;
		lastIndex = index + 1;
		if (index == UINT_MAX)
		{
			GREET_ERROR("FONT", "Invalid file. Not enough data for glyphs: ", filename.c_str());
			return false;
		}
		index = file.find("\n", index + 1);
		data.clear();
		for (int k = 0; k < 256; k++)
		{
			s = file.substr(lastIndex, index - lastIndex);

			int i = s.find("=");

			int ii = i + 1;
			int ii2 = s.find(",", i);

			std::string ss;


			data = getData(s);

			m_glyphCoords.push_back(new Glyph(math::vec2(data[0], data[1]), math::vec2(data[2], data[3]), getCoordOfGlyph(k), m_width / 16.0f, k));

			lastIndex = index + 1;
			if (index == UINT_MAX)
			{
				GREET_ERROR("FONT", "Invalid file. Not enough data for glyphs: ", filename.c_str(), " ", k);
				return false;
			}
			index = file.find("\n", index + 1);
		}
		return true;
	}

	std::vector<float> Font::getData(std::string s)
	{
		std::vector<float> f;

		int i = s.find("=");

		int ii = i + 1;
		int ii2 = s.find(",", i);

		std::string ss;
		while (ii2 != std::string::npos)
		{
			ss = s.substr(ii, ii2 - ii);
			f.push_back((float)atoi(ss.c_str()));
			ii = ii2 + 1;
			ii2 = s.find(",", ii);
		}
		return f;
	}

	std::string Font::generateGlyphs(const std::string& glyph_file, BYTE* bits, int width, int height)
	{
		std::string write = "font=0,0,"+std::to_string(width/ 16)+","+std::to_string(height / 16)+",\n";
		int linesize = width * 4;
		int glyphsrow = 16;
		int glyphsize = width / glyphsrow;
		int lg = linesize*glyphsize;
		int gg = glyphsize*glyphsize;
		int gp = glyphsize * 4;
		for (int y = 0; y < glyphsrow; y++)
		{
			for (int x = 0; x < glyphsrow; x++)
			{
				int xPos = glyphsize, yPos = glyphsize, xPos2 = 0, yPos2 = 0;
				for (int yy = 0; yy < glyphsize; yy++)
				{
					for (int xx = 0; xx < glyphsize; xx++)
					{
						int imageX = x * glyphsrow + xx;
						int imageY = height - 1 - (y * glyphsrow + yy);
						if ((int)bits[(imageX + imageY * width) * 4 + FI_RGBA_ALPHA] == 255)
						{
							if (xx < xPos)
							{
								xPos = xx;
							}
							if (yy < yPos)
							{
								yPos = yy;
							}
							if (xx > xPos2)
							{
								xPos2 = xx;
							}

							if (yy > yPos2)
							{
								yPos2 = yy;
							}
						}
					}
				}
				int i = x + y * 16;
				if (i == (unsigned char)' ')
				{
					xPos = 0;
					yPos = 0;
					xPos2 = width / 16 / 4;
					xPos2 = height / 16 / 4;
				}

				write += utils::dec_to_hex(i,2);
				write += "=";
				write += std::to_string(xPos);
				write += ',';
				write += std::to_string(yPos);
				write += ',';
				write += std::to_string(xPos2 + 1);
				write += ',';
				write += std::to_string(yPos2 + 1);
				write += ',';
				write += '\n';
			}
		}
		utils::write_file(glyph_file.c_str(),write);
		return write;
	}

	Font::~Font()
	{
		destroy();
	}

	void Font::destroy()
	{
		delete m_texture;
		for (int i = 0; i < m_glyphCoords.size(); i++)
			delete m_glyphCoords[i];
	}
}}