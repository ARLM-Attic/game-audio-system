#pragma once
#include <Ogre.h>
namespace GAS
{

class GameAudioListener: public Ogre::SceneNode::Listener
{
public:
	GameAudioListener(Ogre::SceneNode *iSceneNode);
	~GameAudioListener(void);

	virtual void nodeUpdated (const Ogre::Node * iNode);
	virtual void nodeDestroyed (const Ogre::Node *iNode);
	virtual void nodeAttached (const Ogre::Node *iNode);
	virtual void nodeDetached (const Ogre::Node *iNode);
private:
	
	Ogre::SceneNode *mSceneNode;
};

}