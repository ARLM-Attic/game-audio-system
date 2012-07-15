#include "GameAudioListener.h"
#include <al.h>

#include "GameAudioWrapper.h"
using namespace GAS;

GameAudioListener::GameAudioListener(Ogre::SceneNode *iSceneNode)
	:mSceneNode(iSceneNode)
{
	mSceneNode->setListener(this);

}


GameAudioListener::~GameAudioListener(void)
{
}


void GameAudioListener::nodeUpdated (const Ogre::Node * iNode)
{
	int x = 5;
	const Ogre::Vector3 & pos = iNode->getPosition();

	GameAudioWrapper::getSingleton().SetListenerPosition(pos.x, pos.y, pos.z);
	
}
void GameAudioListener::nodeDestroyed (const Ogre::Node *iNode)
{
}
void GameAudioListener::nodeAttached (const Ogre::Node *iNode)
{
}
void GameAudioListener::nodeDetached (const Ogre::Node *iNode)
{
}