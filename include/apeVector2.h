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

#ifndef APE_VECTOR2_H
#define APE_VECTOR2_H

#include <fstream>
#include <vector>

namespace ape
{
	struct Vector2
	{
		float x, y;

		Vector2() :
			x(0.0f), y(0.0f)
		{}

		Vector2(float _x, float _y) :
			x(_x), y(_y)
		{}

		Vector2 operator * (const Vector2& rhs) const
		{
			return Vector2(
				x * rhs.x,
				y * rhs.y);
		}

		std::string toString() const
		{
			std::ostringstream buff;
			buff << x << ", " << y;
			return buff.str();
		}

		std::string toJsonString() const
		{
			std::ostringstream buff;
			buff << "{ ";
			buff << "\"x\": " << x << ", ";
			buff << "\"y\": " << y;
			buff << " }";
			return buff.str();
		}

		std::vector<float> toVector() const
		{
			std::vector<float> vec{ x, y };
			return vec;
		}

		void write(std::ofstream& fileStreamOut, bool writeSize = true)
		{
			if (writeSize)
			{
				long sizeInBytes = 8;
				fileStreamOut.write(reinterpret_cast<char*>(&sizeInBytes), sizeof(long));
			}
			fileStreamOut.write(reinterpret_cast<char*>(&x), sizeof(float));
			fileStreamOut.write(reinterpret_cast<char*>(&y), sizeof(float));
		}

		void read(std::ifstream& fileStreamIn)
		{
			fileStreamIn.read(reinterpret_cast<char*>(&x), sizeof(float));
			fileStreamIn.read(reinterpret_cast<char*>(&y), sizeof(float));
		}
	};
}

#endif
