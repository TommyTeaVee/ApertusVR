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

#ifndef APE_ICLONEGEOMETRY_H
#define APE_ICLONEGEOMETRY_H

#include <string>
#include <vector>
#include "ape.h"
#include "apeGeometry.h"
#include "apeEntity.h"
#include "apeVector3.h"
#include "apeINode.h"

namespace ape
{
	
	class ICloneGeometry : public Geometry
	{
	protected:
		ICloneGeometry(std::string name) : Geometry(name, Entity::GEOMETRY_CLONE) {}

		virtual ~ICloneGeometry() {}

	public:
		virtual void setSourceGeometry(ape::GeometryWeakPtr sourceGeometry) = 0;

		virtual void setSourceGeometryGroupName(std::string groupGeometryName) = 0;

		virtual void setParentNode(ape::NodeWeakPtr parentNode) = 0;

		virtual ape::GeometryWeakPtr getSourceGeometry() = 0;

		virtual std::string getSourceGeometryName() = 0;

		virtual std::string getSourceGeometryGroupName() = 0;

	};
}

#endif // !APE_ICLONEGEOMETRY_H
