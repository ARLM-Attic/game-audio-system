#include "GameAudioObject.h"
#include <al.h>

#include "GameAudioWrapper.h"

using namespace GAS;
GameAudioObject::GameAudioObject(Ogre::SceneNode *iSceneNode,int iSoundId)
	:mSceneNode(iSceneNode)
	,mSoundId(iSoundId)
{
	mSceneNode->setListener(this);
}


GameAudioObject::~GameAudioObject(void)
{
}

void GameAudioObject::nodeUpdated (const Ogre::Node * iNode)
{
	int x = 5;
	const Ogre::Vector3 & pos = iNode->getPosition();

	GameAudioWrapper::getSingleton().SetSourcePosition(mSoundId,pos.x, pos.y, pos.z);
	
}
void GameAudioObject::nodeDestroyed (const Ogre::Node *iNode)
{
}
void GameAudioObject::nodeAttached (const Ogre::Node *iNode)
{
}
void GameAudioObject::nodeDetached (const Ogre::Node *iNode)
{
}
