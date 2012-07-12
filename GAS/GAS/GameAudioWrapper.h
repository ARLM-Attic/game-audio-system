#pragma once


#include <eaxac3.h>
#include <eax.h>
#include <al.h>
#include <alc.h>

#include <string>
#include <bitset>
#include <unordered_map>

#include "AudioObjectsPool.h"

namespace GAS
{

class GameAudioWrapper
{
public:
	GameAudioWrapper(void);
	~GameAudioWrapper(void);

	void LoadSound(std::string& iFileName, std::string& iFormat);
	unsigned int CreateSource(std::string& iFileName, std::string& iFormat);
	bool IsFormatSupported(std::string& iFormat) const;
	bool IsLoadedSound(std::string& iSoundName)const;
	bool Play(unsigned int iSoundId)const;
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

	typedef std::unordered_map<std::string, unsigned int> BufferNameMap;
	BufferNameMap mBufferNames;

	//------ EAX extensions --------------
	bool mActiveEAX;
	bool mActiveEAX_AC3;

	LPEAXAC3FNTABLE mEaxFunctionTable;
//	EAXSet mEaxSet;
};

}
