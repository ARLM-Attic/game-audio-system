#pragma once


#include <eaxac3.h>
#include <eax.h>
#include <al.h>
#include <alc.h>
#include <ogg\ogg.h>

#include <string>
#include <bitset>


namespace GAS
{

class GameAudioWrapper
{
public:
	GameAudioWrapper(void);
	~GameAudioWrapper(void);

	void LoadSound(std::string& iFileName, std::string& iFormat);
	bool IsFormatSupported(std::string& iFormat) const;
private:
	bool Init();
	bool InitEAX();
	bool InitListener();

	bool CheckErrors(const std::string& iSource) const;


	void LoadOgg(const std::string& iFileName);
	//----------------- MEMBER FIELDS ---------------------------
	ALCdevice* mSoundDevice;
	ALCcontext* mSoundContext;

	static const int MAX_AUDIO_BUFFERS = 10;
	static const int MAX_AUDIO_SOURCES = 10;

	unsigned int mAudioBuffers[ MAX_AUDIO_BUFFERS ];
	std::bitset<MAX_AUDIO_BUFFERS> mUsedBuffers;

	unsigned int mAudioSources[ MAX_AUDIO_SOURCES ];
	std::bitset<MAX_AUDIO_BUFFERS> mUsedSources;


	//------ EAX extensions --------------
	bool mActiveEAX;
	bool mActiveEAX_AC3;

	LPEAXAC3FNTABLE mEaxFunctionTable;
//	EAXSet mEaxSet;
};

}

