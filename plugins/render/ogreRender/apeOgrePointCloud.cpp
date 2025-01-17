#include "apeOgrePointCloud.h"

ape::OgrePointCloud::OgrePointCloud(const std::string& name, const std::string& resourcegroup, const int numpoints, float *parray, float *carray, float boundigSphereRadius,
	ape::NodeWeakPtr headNode, ape::NodeWeakPtr pointCloudNode, float pointSize, bool pointScale,
	float pointScaleOffset, float unitScaleDistance, float scaleFactor)
{
	mRenderSystemForVertex = Ogre::Root::getSingleton().getRenderSystem();
	mMesh = Ogre::MeshManager::getSingleton().createManual(name + "Mesh", resourcegroup);
	mSubMesh = mMesh->createSubMesh();
	mMesh->sharedVertexData = new Ogre::VertexData();
	mMesh->sharedVertexData->vertexCount = numpoints;
	Ogre::VertexDeclaration* decl = mMesh->sharedVertexData->vertexDeclaration;
	decl->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
	mVbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(decl->getVertexSize(0), mMesh->sharedVertexData->vertexCount,
		Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);
	mVbuf->writeData(0, mVbuf->getSizeInBytes(), parray, true);
	if (carray != NULL)
	{
		decl->addElement(1, 0, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
		mCbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR), mMesh->sharedVertexData->vertexCount,
			Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);
		Ogre::RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
		Ogre::RGBA *colours = new Ogre::RGBA[numpoints];
		for (int i = 0, k = 0; i < numpoints * 3, k < numpoints; i += 3, k++)
		{
			Ogre::ColourValue color(carray[i], carray[i + 1], carray[i + 2]);
			rs->convertColourValue(color, &colours[k]);
		}
		mCbuf->writeData(0, mCbuf->getSizeInBytes(), colours, true);
		delete[] colours;
	}
	Ogre::VertexBufferBinding* bind = mMesh->sharedVertexData->vertexBufferBinding;
	bind->setBinding(0, mVbuf);
	if (carray != NULL)
	{
		bind->setBinding(1, mCbuf);
	}
	mSubMesh->useSharedVertices = true;
	mSubMesh->operationType = Ogre::RenderOperation::OT_POINT_LIST;
	mMesh->_setBounds(Ogre::AxisAlignedBox(Ogre::Vector3(-boundigSphereRadius, -boundigSphereRadius, -boundigSphereRadius), Ogre::Vector3(boundigSphereRadius, boundigSphereRadius, boundigSphereRadius)), true);
	//msh->_setBoundingSphereRadius(boundigSphereRadius);
	mMesh->load();
	mMaterial = Ogre::MaterialManager::getSingletonPtr()->getByName(name + "Material");
	mPointSize = pointSize;
	mMaterial->setPointSize(mPointSize);
	mPointScale = pointScale;
	mPointScaleOffset = pointScaleOffset;
	mUnitScaleDistance = unitScaleDistance;
	mScaleFactor = scaleFactor;
	mHeadNode = headNode;
	mPointCloudNode = pointCloudNode;
}

ape::OgrePointCloud::~OgrePointCloud()
{

}

void ape::OgrePointCloud::updateVertexPositions(int size, float *points)
{
	float *pPArray = static_cast<float*>(mVbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
	for (int i = 0; i < size * 3; i += 3)
	{
		pPArray[i] = points[i];
		pPArray[i + 1] = points[i + 1];
		pPArray[i + 2] = points[i + 2];
	}
	if (mPointScale)
	{
		if (auto headNode = mHeadNode.lock())
		{
			if (auto pointCloudNode = mPointCloudNode.lock())
			{
				ape::Vector3 pointScalePosition = pointCloudNode->getPosition() - ape::Vector3(0, 0, mPointScaleOffset);
				ape::Vector3 headNodePositionInPointScalePosition = headNode->getDerivedPosition() - pointScalePosition;
				float scale = mScaleFactor * (mUnitScaleDistance / headNodePositionInPointScalePosition.z);
				mMaterial->setPointSize(scale);
			}
		}
	}
	mVbuf->unlock();
}

void ape::OgrePointCloud::updateVertexColours(int size, float *colours)
{
	Ogre::RGBA *colorArrayBuffer = static_cast<Ogre::RGBA*>(mCbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
	int j = 0;
	for (int i = 0; i < size * 3; i += 3)
	{
		Ogre::ColourValue color = Ogre::ColourValue(colours[i], colours[i + 1], colours[i + 2]);
		mRenderSystemForVertex->convertColourValue(color, &colorArrayBuffer[j++]);
	}
	mCbuf->unlock();
}