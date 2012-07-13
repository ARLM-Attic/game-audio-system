#pragma once

#include <Ogre.h>

namespace GAS
{
class GameAudioObject: public Ogre::SceneNode::Listener
{
public:
	GameAudioObject(Ogre::SceneNode *iSceneNode);
	~GameAudioObject(void);
	virtual void nodeUpdated (const Ogre::Node * iNode);
	virtual void nodeDestroyed (const Ogre::Node *iNode);
	virtual void nodeAttached (const Ogre::Node *iNode);
	virtual void nodeDetached (const Ogre::Node *iNode);

private:
	int mSoundId;
	//Ogre::SceneNode::Listener mListener;
	Ogre::SceneNode *mSceneNode;
};

}