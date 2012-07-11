#include "GameAudioWrapper.h"
#include <iostream>

using namespace GAS;

GameAudioWrapper::GameAudioWrapper(void)
{
	Init();
//	InitEAX();
}


GameAudioWrapper::~GameAudioWrapper(void)
{
}

bool GameAudioWrapper::Init()
{
	mSoundDevice = alcOpenDevice( nullptr );
	if ( !mSoundDevice )
	{
		std::cout << "GameAudioWrapper: Sound Device creation FAILED" <<std::endl;
		return false;
	}

	mSoundContext = alcCreateContext( mSoundDevice, NULL );
	if ( !mSoundContext )
	{
		std::cout << "GameAudioWrapper: Sound Context creation FAILED" <<std::endl;
		return false;
	}

	alcMakeContextCurrent( mSoundContext );
	if ( CheckErrors( "Initizialization" ) )
	{
		std::cout << "GameAudioWrapper: Sound Context Setup FAILED" <<std::endl;
		return false;
	}


	// Create the Audio Buffers
   alGenBuffers( MAX_AUDIO_BUFFERS, mAudioBuffers );
   if (CheckErrors("alGenBuffers"))
        return false;

   // Generate Sources
   alGenSources( MAX_AUDIO_SOURCES, mAudioSources );
   if (CheckErrors( "alGenSources"))
        return false;


	return true;

	
}
bool GameAudioWrapper::InitEAX()
{
	mActiveEAX = alIsExtensionPresent( "EAX2.0" );

	mEaxFunctionTable = new EAXAC3FNTABLE;

	if (!mEaxFunctionTable)
	{
		std::cout << "GameAudioWrapper: ERROR EAX Out of memory" <<std::endl;
		return false;
	}
	ALchar szAC3[] = "EAX-AC3";
	mActiveEAX_AC3 = alIsExtensionPresent(szAC3);

	return true;
}
bool GameAudioWrapper::CheckErrors(const std::string& iSource) const
{
	ALenum error = 0;
 
    if ( (error = alGetError()) == AL_NO_ERROR )
		return false;
 
   switch ( error )
   {
        case AL_INVALID_NAME:
			std::cout << "GameAudioWrapper: ERROR INVALID_NAME " << iSource << std::endl;
            break;
        case AL_INVALID_ENUM:
            std::cout << "GameAudioWrapper: ERROR INVALID_ENUM " << iSource << std::endl;
            break;
        case AL_INVALID_VALUE:
            std::cout << "GameAudioWrapper: ERROR INVALID_VALUE " << iSource << std::endl;
            break;
        case AL_INVALID_OPERATION:
            std::cout << "GameAudioWrapper: ERROR INVALID_OPERATION " << iSource << std::endl;
            break;
        case AL_OUT_OF_MEMORY:
            std::cout << "GameAudioWrapper: ERROR OUT_OF_MEMORY " << iSource << std::endl;
            break;
        default:
            std::cout << "GameAudioWrapper: ERROR UNKNOWN ERROR CODE " << error << " " << iSource << std::endl;
            break;
   };
 
 
   return true;
 }

void GameAudioWrapper::LoadSound(std::string& iFileName, std::string& iFormat)
{
	if (!IsFormatSupported(iFormat))
	{
		std::cout << "GameAudioWrapper: ERROR Audio Format Not Supported " << iFormat << std::endl;
		return;
	}


}

bool GameAudioWrapper::IsFormatSupported(std::string& iFormat)const
{
	if (iFormat == "ogg")
		return true;
	return false;
}

void GameAudioWrapper::LoadOgg(const std::string& iFileName)
{
  
    OggVorbis_File oggfile;
 
    if(ov_fopen(const_cast<char*>(filename.c_str()), &oggfile))
    {
        printf("SoundManager::loadOGG() : ov_fopen failed.\n");
        return false;
    }
 
    vorbis_info* info = ov_info(&oggfile, -1);
 
    ALenum format;
    switch(info->channels)
    {
        case 1:
            format = AL_FORMAT_MONO16; break;
        case 2:
            format = AL_FORMAT_STEREO16; break;
        case 4:
            format = alGetEnumValue("AL_FORMAT_QUAD16"); break;
        case 6:
            format = alGetEnumValue("AL_FORMAT_51CHN16"); break;
        case 7:
            format = alGetEnumValue("AL_FORMAT_61CHN16"); break;
        case 8:
            format = alGetEnumValue("AL_FORMAT_71CHN16"); break;
        default:
            format = 0; break;
    }
 
    std::vector<int16> samples;
    char tmpbuf[4096];
    int section = 0;
    bool firstrun = true;
    while(1)
    {
        int result = ov_read(&oggfile, tmpbuf, 4096, 0, 2, 1, &section);
        if(result > 0)
        {
            firstrun = false;
            samples.insert(samples.end(), tmpbuf, tmpbuf + (result));
        }
        else
        {
            if(result < 0)
            {
                printf("SoundManager::loadOGG() : Loading ogg sound data failed!");
                ov_clear(&oggfile);
                return false;
            }
            else
            {
                if(firstrun)
                    return false;
                break;
            }
        }
    }
 
    alBufferData(pDestAudioBuffer, format, &samples[0], ov_pcm_total(&oggfile, -1), info->rate);
 
    return true;
 }
}