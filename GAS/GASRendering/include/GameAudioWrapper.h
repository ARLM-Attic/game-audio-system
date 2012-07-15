#pragma once


#include <eaxac3.h>
//#include <eaxac3.h>
#include <eax.h>
#include <al.h>
#include <alc.h>

#include <string>
#include <bitset>
#include <unordered_map>
#include <Ogre.h>

#include "SoundSourceDescriptor.h"

namespace GAS
{

class GameAudioWrapper : public Ogre::Singleton<GameAudioWrapper>
{
public:
	GameAudioWrapper(void);
	~GameAudioWrapper(void);

	void LoadSound(const std::string& iFileName, const std::string& iFormat);
	int CreateSource(const std::string& iFileName,const  std::string& iFormat,const SoundSourceDescriptor& iDesc);
	bool IsFormatSupported(const std::string& iFormat) const;
	bool IsLoadedSound(const std::string& iSoundName)const;

	//--------------------------------------------------
	bool Play(int iSoundId,bool iLoop = false, bool iForceRestart = true)const;
	bool Stop(int iSoundId)const;
	bool Pause(int iSoundId)const;
	bool Resume(int iSoundId)const;

	bool PauseAll()const;
	bool StopAll()const;
	bool ResumeAll()const;

	void SetPitch(int iSourceId, ALfloat iVal);
	void SetGain(int iSourceId, ALfloat iVal);
	ALfloat GetPitch(int iSourceId)const;
	ALfloat GetGain(int iSourceId)const;

	ALfloat GetFloatProperty(int iSourceId, ALenum iProp)const;
	//--------------------------------------------------
	void SetListenerPosition(const ALfloat iX,const ALfloat iY,const ALfloat iZ);
	void SetSourcePosition(int iSourceId, const ALfloat iX,const ALfloat iY,const ALfloat iZ);
	
private:
	bool Init();
	bool InitEAX();
	bool InitListener();

	

	bool CheckErrors(const std::string& iSource) const;

	int GetFreeBuffer()const;
	int GetFreeSource()const;

	void LoadOgg(const std::string& iFileName, unsigned int iBufferId);
	void LoadWav(const std::string& iFileName, unsigned int iBufferId);
	//----------------- MEMBER FIELDS ---------------------------
	ALCdevice* mSoundDevice;
	ALCcontext* mSoundContext;

	static const int MAX_AUDIO_BUFFERS = 10;
	static const int MAX_AUDIO_SOURCES = 10;
	static const ALfloat DEFAULT_LISTENER_POS[3];
	static const ALfloat DEFAULT_LISTENER_VEL[3];
	static const ALfloat DEFAULT_LISTENER_ORIENTATION[6];// = {0.0f, 0.0f,0.0f};

	unsigned int mAudioBuffers[ MAX_AUDIO_BUFFERS ];
	std::bitset<MAX_AUDIO_BUFFERS> mUsedBuffers;

	unsigned int mAudioSources[ MAX_AUDIO_SOURCES ];
	std::bitset<MAX_AUDIO_BUFFERS> mUsedSources;

	typedef std::unordered_map<std::string, int> BufferNameMap;
	BufferNameMap mBufferNames;

	//------ EAX extensions --------------
	ALboolean mActiveEAX;
	ALboolean mActiveEAX_AC3;

	LPEAXAC3FNTABLE mEaxFunctionTable;
//	EAXSet mEaxSet;
};

}

