/*MIT License

Copyright (c) 2018 MTA SZTAKI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef APE_COLOR_H
#define APE_COLOR_H

#include <sstream>
#include <vector>
#include <fstream>

namespace ape
{
	struct Color
	{
		float r, g, b, a;

		Color() :
			r(0.0f), g(0.0f), b(0.0f), a(1.0f)
		{}

		Color(float _r, float _g, float _b, float _a = 1.0f) :
			r(_r), g(_g), b(_b), a(_a)
		{}

		std::string toString() const
		{
			std::ostringstream buff;
			buff << "Color(" << r << ", " << g << ", " << b << ", " << a << ")";
			return buff.str();
		}

		std::string toJsonString() const
		{
			std::ostringstream buff;
			buff << "{ ";
			buff << "\"r\": " << r << ", ";
			buff << "\"g\": " << g << ", ";
			buff << "\"b\": " << b << ", ";
			buff << "\"a\": " << a;
			buff << " }";
			return buff.str();
		}

		float getR()
		{
			return r;
		}

		float getG()
		{
			return g;
		}

		float getB()
		{
			return b;
		}

		float getA()
		{
			return a;
		}

		void write(std::ofstream& fileStreamOut, bool writeSize = true)
		{
			if (writeSize)
			{
				long sizeInBytes = 16;
				fileStreamOut.write(reinterpret_cast<char*>(&sizeInBytes), sizeof(long));
			}
			fileStreamOut.write(reinterpret_cast<char*>(&r), sizeof(float));
			fileStreamOut.write(reinterpret_cast<char*>(&g), sizeof(float));
			fileStreamOut.write(reinterpret_cast<char*>(&b), sizeof(float));
			fileStreamOut.write(reinterpret_cast<char*>(&a), sizeof(float));
		}

		void read(std::ifstream& fileStreamIn)
		{
			fileStreamIn.read(reinterpret_cast<char*>(&r), sizeof(float));
			fileStreamIn.read(reinterpret_cast<char*>(&g), sizeof(float));
			fileStreamIn.read(reinterpret_cast<char*>(&b), sizeof(float));
			fileStreamIn.read(reinterpret_cast<char*>(&a), sizeof(float));
		}

	};

	typedef std::vector < ape::Color > ColorVector;
}

#endif
