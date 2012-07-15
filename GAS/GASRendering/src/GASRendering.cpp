/*
-----------------------------------------------------------------------------
Filename:    GASRendering.cpp
-----------------------------------------------------------------------------


This source file is generated by the
   ___                   _              __    __ _                  _ 
  /___\__ _ _ __ ___    /_\  _ __  _ __/ / /\ \ (_)______ _ _ __ __| |
 //  // _` | '__/ _ \  //_\\| '_ \| '_ \ \/  \/ / |_  / _` | '__/ _` |
/ \_// (_| | | |  __/ /  _  \ |_) | |_) \  /\  /| |/ / (_| | | | (_| |
\___/ \__, |_|  \___| \_/ \_/ .__/| .__/ \/  \/ |_/___\__,_|_|  \__,_|
      |___/                 |_|   |_|                                 
      Ogre 1.7.x Application Wizard for VC10 (July 2011)
      http://code.google.com/p/ogreappwizards/
-----------------------------------------------------------------------------
*/

#include "GASRendering.h"
#include "SoundSourceDescriptor.h"

//-------------------------------------------------------------------------------------
GASRendering::GASRendering(void)
	:mSpeak1MovingLeft(false)
	,mSpeak1MovingFwd(false)
	,mSpeak1MovingRight(false)
	,mSpeak1MovingBack(false)
	,mSpeak2MovingLeft(false)
	,mSpeak2MovingFwd(false)
	,mSpeak2MovingRight(false)
	,mSpeak2MovingBack(false)
	,mListenerMovingLeft(false)
	,mListenerMovingFwd(false)
	,mListenerMovingRight(false)
	,mListenerMovingBack(false)
{
}
//-------------------------------------------------------------------------------------
GASRendering::~GASRendering(void)
{
}

void GASRendering::CreateGui()
{
	Ogre::Real widgetW = 220.0f;
	Ogre::Real boxW = 70.0f;

	//--------------------- SPEAKER 1 GUI ------------------------------
	mSpeaker1Label = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "Speaker1Label", "Speaker 1", widgetW);
	mSpeaker1PlayButton = mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "Speaker1Play", "Play", widgetW);
	mSpeaker1PauseButton = mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "Speaker1Pause", "Pause", widgetW);
	mSpeaker1StopButton = mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "Speaker1Stop", "Stop", widgetW);
	
	mSpeaker1PitchSlider = mTrayMgr->createThickSlider(OgreBites::TL_TOPLEFT,"Speaker1Pitch", "Pitch", widgetW, boxW, 0.0f, 1.0f ,50);
	mSpeaker1PitchSlider->setValue (GAS::GameAudioWrapper::getSingleton().GetPitch(mSpeaker1->GetSoundId()));
	
	mSpeaker1GainSlider = mTrayMgr->createThickSlider(OgreBites::TL_TOPLEFT,"Speaker1Gain", "Gain", widgetW, boxW, 0.0f, 1.0f ,50);
	mSpeaker1GainSlider->setValue (GAS::GameAudioWrapper::getSingleton().GetGain(mSpeaker1->GetSoundId()));
	
	mSpeaker1LoopCheckbox = mTrayMgr->createCheckBox(OgreBites::TL_TOPLEFT,"Speaker1Loop","Loop", widgetW);
	
	mSpeaker1RolloffSlider = mTrayMgr->createThickSlider(OgreBites::TL_TOPLEFT,"Speaker1Rolloff", "Rolloff", widgetW, boxW, 0.0f, 1.0f ,50);
	mSpeaker1RolloffSlider->setValue (GAS::GameAudioWrapper::getSingleton().GetFloatProperty(mSpeaker1->GetSoundId(),AL_ROLLOFF_FACTOR));
	
	mSpeaker1ReferenceDistanceSlider = mTrayMgr->createThickSlider(OgreBites::TL_TOPLEFT,"Speaker1ReferenceDistance", "Reference Distance", widgetW, boxW, 0.0f, 600.0f ,50);
	mSpeaker1ReferenceDistanceSlider->setValue (GAS::GameAudioWrapper::getSingleton().GetFloatProperty(mSpeaker1->GetSoundId(),AL_REFERENCE_DISTANCE));
	
	
	//workaround for empty tray bug..to be removed at first update
	mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "Empty", "WorkAround", widgetW);
	
	mSpeaker2Label = mTrayMgr->createLabel(OgreBites::TL_TOPRIGHT, "Speaker2Label", "Speaker 2", widgetW);
	mSpeaker2PlayButton = mTrayMgr->createButton(OgreBites::TL_TOPRIGHT, "Speaker2Play", "Play", widgetW);
	mSpeaker2PauseButton = mTrayMgr->createButton(OgreBites::TL_TOPRIGHT, "Speaker2Pause", "Pause", widgetW);
	mSpeaker2StopButton = mTrayMgr->createButton(OgreBites::TL_TOPRIGHT, "Speaker2Stop", "Stop", widgetW);
	
	mSpeaker2PitchSlider = mTrayMgr->createThickSlider(OgreBites::TL_TOPRIGHT,"Speaker2Pitch", "Pitch", widgetW, boxW, 0.0f, 1.0f ,50);
	mSpeaker2PitchSlider->setValue (GAS::GameAudioWrapper::getSingleton().GetPitch(mSpeaker2->GetSoundId()));
	
	mSpeaker2GainSlider = mTrayMgr->createThickSlider(OgreBites::TL_TOPRIGHT,"Speaker2Gain", "Gain", widgetW, boxW, 0.0f, 1.0f ,50);
	mSpeaker2GainSlider->setValue (GAS::GameAudioWrapper::getSingleton().GetGain(mSpeaker2->GetSoundId()));
	
	mSpeaker2LoopCheckbox = mTrayMgr->createCheckBox(OgreBites::TL_TOPRIGHT,"Speaker2Loop","Loop",widgetW);

	mSpeaker2RolloffSlider = mTrayMgr->createThickSlider(OgreBites::TL_TOPRIGHT,"Speaker2Rolloff", "Rolloff", widgetW, boxW, 0.0f, 1.0f ,50);
	mSpeaker2RolloffSlider->setValue (GAS::GameAudioWrapper::getSingleton().GetFloatProperty(mSpeaker2->GetSoundId(),AL_ROLLOFF_FACTOR));
	
	mSpeaker2ReferenceDistanceSlider = mTrayMgr->createThickSlider(OgreBites::TL_TOPRIGHT,"Speaker2ReferenceDistance", "Reference Distance", widgetW, boxW, 0.0f, 600.0f ,50);
	mSpeaker2ReferenceDistanceSlider->setValue (GAS::GameAudioWrapper::getSingleton().GetFloatProperty(mSpeaker2->GetSoundId(),AL_REFERENCE_DISTANCE));
	
	mSelectObjectLayer = mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT, "ObjectSelectionLabel", "Select Object", widgetW);
	mSelectSpeakear1Checkbox = mTrayMgr->createCheckBox(OgreBites::TL_BOTTOMLEFT,"SelectSpeaker1","Speaker1",widgetW);
	mSelectSpeakear2Checkbox = mTrayMgr->createCheckBox(OgreBites::TL_BOTTOMLEFT,"SelectSpeaker2","Speaker2",widgetW);
	mSelectListenerCheckbox = mTrayMgr->createCheckBox(OgreBites::TL_BOTTOMLEFT,"SelectListener","Listener",widgetW);
	
}
//-------------------------------------------------------------------------------------
void GASRendering::createScene(void)
{
   
	
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("Floor", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 1000, 1000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	
	Ogre::Entity *planeEnt = mSceneMgr->createEntity("FloorEntity","Floor");

	Ogre::SceneNode* node = mSceneMgr->createSceneNode("Floor");
	mSceneMgr->getRootSceneNode()->addChild(node);
	node->attachObject(planeEnt);
	planeEnt->setMaterialName("Examples/Rockwall");
    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // Create a light
    Ogre::Light* l = mSceneMgr->createLight("MainLight");
    l->setPosition(20,80,50);

	//SPEAKER1 MODEL
	mSpeaker1Node = mSceneMgr->createSceneNode("Speaker1");
	mSceneMgr->getRootSceneNode()->addChild(mSpeaker1Node);
	Ogre::Entity* model = mSceneMgr->createEntity("Speaker1_ent","cube.mesh");

	Ogre::Real delta = Ogre::Math::Abs (model->getBoundingBox().getMinimum().y);

	mSpeaker1Node->attachObject(model);
	mSpeaker1Node->setPosition(Ogre::Vector3(-20.0f, 0.2f * delta, 0.0f));
	mSpeaker1Node->setScale(Ogre::Vector3::UNIT_SCALE * 0.2f);
	//SPEAKER2 MODEL
	mSpeaker2Node = mSceneMgr->createSceneNode("Speaker2");
	mSceneMgr->getRootSceneNode()->addChild(mSpeaker2Node);
	Ogre::Entity* model2 = mSceneMgr->createEntity("Speaker2_ent","cube.mesh");
	mSpeaker2Node->attachObject(model2);
	mSpeaker2Node->setPosition(Ogre::Vector3(20.0f, 0.2f * delta, 0.0f));
	mSpeaker2Node->setScale(Ogre::Vector3::UNIT_SCALE * 0.2f);


	//LISTENER
	mListenerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* ent = mSceneMgr->createEntity("Sinbad", "Sinbad.mesh");
	mListenerNode->attachObject(ent);
	mListenerNode->scale(Ogre::Vector3::UNIT_SCALE * 5.0f);
	Ogre::Real h = Ogre::Math::Abs (ent->getBoundingBox().getMinimum().y);//.getHalfSize().y;
	mListenerNode->translate(Ogre::Vector3 (0.0f,h * 5.0f,0.0f));

	mSinbadAnimation = ent->getAnimationState("Dance");
	mSinbadAnimation->setEnabled(true);

	new GAS::GameAudioWrapper();

	GAS::DefualtSoundSourceDescriptor desc;
	unsigned int id2 = GAS::GameAudioWrapper::getSingleton().CreateSource(std::string("Media/sounds/beat2_mono"), std::string("ogg"),desc);
	unsigned int id = GAS::GameAudioWrapper::getSingleton().CreateSource(std::string("Media/sounds/beat_mono"), std::string("ogg"),desc);

	mSpeaker1 = new GAS::GameAudioObject(mSpeaker1Node, id);
	mSpeaker2 = new GAS::GameAudioObject(mSpeaker2Node, id2);
	mListener = new GAS::GameAudioListener(mListenerNode);

	
	//mRoot->renderOneFrame();
	CreateGui();
	
    
	
}

// OIS::KeyListener
bool GASRendering::keyPressed( const OIS::KeyEvent &arg )
{
	BaseApplication::keyPressed(arg);
	if (mSelectSpeakear1Checkbox->isChecked())
	{
		if (arg.key == OIS::KC_J)
		{
			mSpeak1MovingLeft = true;
		
		}else if (arg.key == OIS::KC_L)
		{
			mSpeak1MovingRight = true;
		
		}else if (arg.key == OIS::KC_I)   
		{
			mSpeak1MovingFwd = true;
		}else if (arg.key == OIS::KC_K)   
		{
			mSpeak1MovingBack = true;
		}
	}else if (mSelectSpeakear2Checkbox->isChecked())
	{
	
		if (arg.key == OIS::KC_J)
		{
			mSpeak2MovingLeft = true;
		
		}else if (arg.key == OIS::KC_L)
		{
			mSpeak2MovingRight = true;
		
		}else if (arg.key == OIS::KC_I)   
		{
			mSpeak2MovingFwd = true;
		}else if (arg.key == OIS::KC_K)   
		{
			mSpeak2MovingBack = true;
		}
	}else if (mSelectListenerCheckbox->isChecked())
	{
	
		if (arg.key == OIS::KC_J)
		{
			mListenerMovingLeft = true;
		
		}else if (arg.key == OIS::KC_L)
		{
			mListenerMovingRight = true;
		
		}else if (arg.key == OIS::KC_I)   
		{
			mListenerMovingFwd = true;
		}else if (arg.key == OIS::KC_K)   
		{
			mListenerMovingBack = true;
		}
	}
	return true;
}
bool GASRendering::keyReleased( const OIS::KeyEvent &arg )
{
	BaseApplication::keyReleased(arg);

	
	if (mSelectSpeakear1Checkbox->isChecked())
	{
	
		if (arg.key == OIS::KC_J)
		{
			mSpeak1MovingLeft = false;
		
		}else if (arg.key == OIS::KC_L)
		{
			mSpeak1MovingRight = false;
		
		}else if (arg.key == OIS::KC_I)   
		{
			mSpeak1MovingFwd = false;
		}else if (arg.key == OIS::KC_K)   
		{
			mSpeak1MovingBack = false;
		}
	}else if (mSelectSpeakear2Checkbox->isChecked())
	{
	
		if (arg.key == OIS::KC_J)
		{
			mSpeak2MovingLeft = false;
		
		}else if (arg.key == OIS::KC_L)
		{
			mSpeak2MovingRight = false;
		
		}else if (arg.key == OIS::KC_I)   
		{
			mSpeak2MovingFwd = false;
		}else if (arg.key == OIS::KC_K)   
		{
			mSpeak2MovingBack = false;
		}
	}else if (mSelectListenerCheckbox->isChecked())
	{
	
		if (arg.key == OIS::KC_J)
		{
			mListenerMovingLeft = false;
		
		}else if (arg.key == OIS::KC_L)
		{
			mListenerMovingRight = false;
		
		}else if (arg.key == OIS::KC_I)   
		{
			mListenerMovingFwd = false;
		}else if (arg.key == OIS::KC_K)   
		{
			mListenerMovingBack = false;
		}
	}
	
	return true;
}

static bool guiCreated = false;
//-------------------------------------------------------------------------------------
bool GASRendering::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if (!guiCreated)
	{
		mTrayMgr->destroyWidget("Empty");
		guiCreated = true;
	}
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;
    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

	mSinbadAnimation->addTime(evt.timeSinceLastFrame);

	Ogre::Vector3 traslationSpeak1(0.0f,0.0f,0.0f);
	Ogre::Vector3 traslationSpeak2(0.0f,0.0f,0.0f);
	Ogre::Vector3 traslationListener(0.0f,0.0f,0.0f);
	
	float delta = 50.0f;
	bool modifiedSpeak1 = false;
	bool modifiedSpeak2 = false;
	bool modifiedListener = false;
	
	if (mSpeak1MovingBack)
	{
		traslationSpeak1 += Ogre::Vector3::UNIT_Z * delta * evt.timeSinceLastFrame;
		modifiedSpeak1 = true;
	}
    if (mSpeak1MovingFwd)
	{
		traslationSpeak1 += -Ogre::Vector3::UNIT_Z * delta * evt.timeSinceLastFrame;
		modifiedSpeak1 = true;
	}
    if (mSpeak1MovingLeft)
	{
		traslationSpeak1 += -Ogre::Vector3::UNIT_X * delta * evt.timeSinceLastFrame;
		modifiedSpeak1 = true;
	}
    if (mSpeak1MovingRight)
	{
		traslationSpeak1 += Ogre::Vector3::UNIT_X * delta * evt.timeSinceLastFrame;
		modifiedSpeak1 = true;
	}
    //-------------------
	if (mSpeak2MovingBack)
	{
		traslationSpeak2 += Ogre::Vector3::UNIT_Z * delta * evt.timeSinceLastFrame;
		modifiedSpeak2 = true;
	}
    if (mSpeak2MovingFwd)
	{
		traslationSpeak2 += -Ogre::Vector3::UNIT_Z * delta * evt.timeSinceLastFrame;
		modifiedSpeak2 = true;
	}
    if (mSpeak2MovingLeft)
	{
		traslationSpeak2 += -Ogre::Vector3::UNIT_X * delta * evt.timeSinceLastFrame;
		modifiedSpeak2 = true;
	}
    if (mSpeak2MovingRight)
	{
		traslationSpeak2 += Ogre::Vector3::UNIT_X * delta * evt.timeSinceLastFrame;
		modifiedSpeak2 = true;
	}
	//-------------------------------
	if (mListenerMovingBack)
	{
		traslationListener += Ogre::Vector3::UNIT_Z * delta * evt.timeSinceLastFrame;
		modifiedListener = true;
	}
    if (mListenerMovingFwd)
	{
		traslationListener += -Ogre::Vector3::UNIT_Z * delta * evt.timeSinceLastFrame;
		modifiedListener = true;
	}
    if (mListenerMovingLeft)
	{
		traslationListener += -Ogre::Vector3::UNIT_X * delta * evt.timeSinceLastFrame;
		modifiedListener = true;
	}
    if (mListenerMovingRight)
	{
		traslationListener += Ogre::Vector3::UNIT_X * delta * evt.timeSinceLastFrame;
		modifiedListener = true;
	}
	
	if (modifiedSpeak1)
		mSpeaker1Node->translate(traslationSpeak1);
	if (modifiedSpeak2)
		mSpeaker2Node->translate(traslationSpeak2);
	if (modifiedListener)
		mListenerNode->translate(traslationListener);

	mTrayMgr->frameRenderingQueued(evt);

    if (!mTrayMgr->isDialogVisible())
    {
        mCameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
	//	mTrayMgr->showAll();
        //if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
        //{
        //    mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
        //    mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
        //    mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
        //    mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
        //    mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
        //    mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
        //    mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        //}
    }

    return true;
}




void GASRendering::buttonHit(OgreBites::Button* button)
{
	if (button->getName() == "Speaker1Play")
	{		
		
		GAS::GameAudioWrapper::getSingleton().Play(mSpeaker1->GetSoundId(),mSpeaker1LoopCheckbox->isChecked());
	}else if(button->getName() == "Speaker2Play")
	{
		GAS::GameAudioWrapper::getSingleton().Play(mSpeaker2->GetSoundId(),mSpeaker2LoopCheckbox->isChecked());
	}else if(button->getName() == "Speaker1Stop")
	{
		GAS::GameAudioWrapper::getSingleton().Stop(mSpeaker1->GetSoundId());
	}else if(button->getName() == "Speaker2Stop")
	{
		GAS::GameAudioWrapper::getSingleton().Stop(mSpeaker2->GetSoundId());
	}else if(button->getName() == "Speaker1Pause")
	{
		GAS::GameAudioWrapper::getSingleton().Pause(mSpeaker1->GetSoundId());
	}else if(button->getName() == "Speaker2Pause")
	{
		GAS::GameAudioWrapper::getSingleton().Pause(mSpeaker2->GetSoundId());
	}
}
void GASRendering::sliderMoved(OgreBites::Slider* slider)
{
	if (slider->getName() == "Speaker1Pitch")
	{
		GAS::GameAudioWrapper::getSingleton().SetPitch(mSpeaker1->GetSoundId(), slider->getValue());
	}else if (slider->getName() == "Speaker2Pitch")
	{
		GAS::GameAudioWrapper::getSingleton().SetPitch(mSpeaker2->GetSoundId(), slider->getValue());
	}else if (slider->getName() == "Speaker1Gain")
	{
		GAS::GameAudioWrapper::getSingleton().SetGain(mSpeaker1->GetSoundId(), slider->getValue());
	}else if (slider->getName() == "Speaker2Gain")
	{
		GAS::GameAudioWrapper::getSingleton().SetGain(mSpeaker2->GetSoundId(), slider->getValue());
	}else if (slider->getName() == "Speaker1Rolloff")
	{
		GAS::GameAudioWrapper::getSingleton().SetFloatProperty(mSpeaker1->GetSoundId(), AL_ROLLOFF_FACTOR,slider->getValue());
	}else if (slider->getName() == "Speaker2Rolloff")
	{
		GAS::GameAudioWrapper::getSingleton().SetFloatProperty(mSpeaker2->GetSoundId(), AL_ROLLOFF_FACTOR,slider->getValue());
	}else if (slider->getName() == "Speaker1ReferenceDistance")
	{
		GAS::GameAudioWrapper::getSingleton().SetFloatProperty(mSpeaker1->GetSoundId(), AL_REFERENCE_DISTANCE,slider->getValue());
	}else if (slider->getName() == "Speaker2ReferenceDistance")
	{
		GAS::GameAudioWrapper::getSingleton().SetFloatProperty(mSpeaker2->GetSoundId(), AL_REFERENCE_DISTANCE,slider->getValue());
	}     
	
}
void GASRendering::checkBoxToggled(OgreBites::CheckBox* box)
{
	if (box->getName() == "SelectSpeaker1")
	{
		if (box->isChecked())
		{
			mSelectSpeakear2Checkbox->setChecked(false,false);
			mSelectListenerCheckbox->setChecked(false,false);
		}
	}else if (box->getName() == "SelectSpeaker2")
	{
		if (box->isChecked())
		{
			mSelectSpeakear1Checkbox->setChecked(false,false);
			mSelectListenerCheckbox->setChecked(false,false);
		}
	}else if (box->getName() == "SelectListener")
	{
		if (box->isChecked())
		{
			mSelectSpeakear1Checkbox->setChecked(false,false);
			mSelectSpeakear2Checkbox->setChecked(false,false);
		}
	}else if (box->getName() == "Speaker1Loop")
	{
		GAS::GameAudioWrapper::getSingleton().SetLoop(mSpeaker1->GetSoundId(), box->isChecked());
	}else if (box->getName() == "Speaker2Loop")
	{
		GAS::GameAudioWrapper::getSingleton().SetLoop(mSpeaker2->GetSoundId(), box->isChecked());
	}
	
}






//---------------------------------- MAIN ------------------------------------------


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        GASRendering app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
