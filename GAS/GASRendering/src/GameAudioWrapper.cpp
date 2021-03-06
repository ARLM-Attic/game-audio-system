#include "GameAudioWrapper.h"
#include <iostream>
#include <ogg\ogg.h>

#include <vorbis\vorbisfile.h>
#include <vector>
#include <AL\alut.h>

using namespace GAS;
template<> GameAudioWrapper* Ogre::Singleton<GameAudioWrapper>::msSingleton = 0;

const ALfloat GameAudioWrapper::DEFAULT_LISTENER_POS[3] = {0.0f,0.0f,0.0f};
const ALfloat GameAudioWrapper::DEFAULT_LISTENER_VEL[3] = {0.0f,0.0f,0.0f};
const ALfloat GameAudioWrapper::DEFAULT_LISTENER_ORIENTATION[6] = {0.0f,0.0f,-1.0f, 0.0f, 1.0f, 0.0f};


GameAudioWrapper::GameAudioWrapper(void)
{
	Init();
//	InitEAX();
	InitListener();
}


GameAudioWrapper::~GameAudioWrapper(void)
{
	// Delete the sources and buffers
	alDeleteSources( MAX_AUDIO_SOURCES, mAudioSources );
	alDeleteBuffers( MAX_AUDIO_BUFFERS, mAudioBuffers );
 
    // Destroy the sound context and device
    mSoundContext = alcGetCurrentContext();
    mSoundDevice = alcGetContextsDevice( mSoundContext );
    alcMakeContextCurrent( NULL );
    alcDestroyContext( mSoundContext );
    if ( mSoundDevice)
        alcCloseDevice( mSoundDevice );
 
}

bool GameAudioWrapper::Init()
{
	
	
	mSoundDevice = alcOpenDevice( NULL );
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

//	alutInit(NULL,NULL);
	// Create the Audio Buffers
	alGenBuffers( MAX_AUDIO_BUFFERS, mAudioBuffers );
	//alGenBuffers( 1, mAudioBuffers );
   if (CheckErrors("algenbuffers"))
        return false;

   // generate sources
   alGenSources( MAX_AUDIO_SOURCES, mAudioSources );
   //alGenSources( 1, mAudioSources );
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
bool GameAudioWrapper::InitListener()
{

	alListenerfv( AL_POSITION, DEFAULT_LISTENER_POS );
	alListenerfv( AL_VELOCITY, DEFAULT_LISTENER_VEL );
	
	alListenerfv( AL_ORIENTATION, DEFAULT_LISTENER_ORIENTATION );
	alDopplerFactor( 1.0 ); // 1.2 = exaggerate the pitch shift by 20%
	alDopplerVelocity( 343.0f ); // m/s this may need to be scaled at some point
 
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
bool GameAudioWrapper::IsLoadedSound(const std::string& iSoundName)const
{
	BufferNameMap::const_iterator it = mBufferNames.find(iSoundName);
	if (it != mBufferNames.end())
		return true;
	return false;
}
int GameAudioWrapper::CreateSource(const std::string& iFileName, const std::string& iFormat,const SoundSourceDescriptor& iDesc)
{
	
	
	std::string name = iFileName + "." + iFormat;
	if (!IsLoadedSound(name))
	{
		LoadSound(iFileName,iFormat);
	}

	alGetError();
	int bufferId = mBufferNames[name];
	int sourceId = GetFreeSource();

	if (sourceId == -1)
		throw;

	alSourcei( mAudioSources[sourceId], AL_BUFFER, mAudioBuffers[bufferId] );
	alSourcef( mAudioSources[sourceId], AL_GAIN, iDesc.gain );
	alSourcef( mAudioSources[sourceId], AL_PITCH, iDesc.pitch );
	alSourcef( mAudioSources[sourceId], AL_REFERENCE_DISTANCE, iDesc.reference_distance );
	alSourcef( mAudioSources[sourceId], AL_ROLLOFF_FACTOR, iDesc.rolloff );
	mUsedSources.set(sourceId);

	if (CheckErrors("GameAudioWrapper::CreateSource"))
		throw;
	return  sourceId;
}
void GameAudioWrapper::LoadSound(const std::string& iFileName, const std::string& iFormat)
{
	if (!IsFormatSupported(iFormat))
	{
		std::cout << "GameAudioWrapper: ERROR Audio Format Not Supported " << iFormat << std::endl;
		throw;
	}

	int bufferIndex = GetFreeBuffer();
	if (bufferIndex == -1)
	{
	    std::cout << "GameAudioWrapper: ERROR NO FREE BUFFER " <<std::endl;
		throw;
	}

	if (iFormat == "ogg")
		LoadOgg(iFileName + "." + iFormat, mAudioBuffers[bufferIndex]);
	if ((iFormat == "wav"))
		LoadWav(iFileName + "." + iFormat, mAudioBuffers[bufferIndex]);
	mUsedBuffers.set(bufferIndex);
 
	mBufferNames[iFileName + "." + iFormat] = bufferIndex;
}

bool GameAudioWrapper::IsFormatSupported(const std::string& iFormat)const
{
	if (iFormat == "ogg" || iFormat == "wav")
		return true;
	return false;
}
void GameAudioWrapper::LoadWav(const std::string& iFileName, unsigned int iBufferId)
{
	ALuint buffer, source;
	buffer = alutCreateBufferFromFile(iFileName.c_str());
	alGenSources (1, &source);
	alSourcei (source, AL_BUFFER, buffer);
	alSourcei(source, AL_LOOPING, AL_TRUE);
	alSourcePlay (source);
	alutSleep (30);
	alutSleep (30);

}

void GameAudioWrapper::LoadOgg(const std::string& iFileName, unsigned int iBufferId)
{
 
#define BUFFER_SIZE 4096
	int endian = 0;                         // 0 for Little-Endian, 1 for Big-Endian
    int bitStream;
    char array[BUFFER_SIZE];                // Local fixed size array
    FILE *f;

    // Open for binary reading
	f = fopen(iFileName.c_str(), "rb");

    if (f == NULL)
		throw;
    
    OggVorbis_File oggFile;

    // Try opening the given file
    if (ov_open(f, &oggFile, NULL, 0) != 0)
		throw;

	vorbis_info* info = ov_info(&oggFile, -1);;
    ALenum format;
    switch(info->channels)
    {
        case 1:
            format = AL_FORMAT_MONO16;
			break;
        case 2:
            format = AL_FORMAT_STEREO16;
			break;
        case 4:
            format = alGetEnumValue("AL_FORMAT_QUAD16"); 
			break;
        case 6:
            format = alGetEnumValue("AL_FORMAT_51CHN16"); 
			break;
        case 7:
            format = alGetEnumValue("AL_FORMAT_61CHN16"); 
			break;
        case 8:
            format = alGetEnumValue("AL_FORMAT_71CHN16"); 
			break;
        default:
            format = 0; 
			break;
    }
	std::vector<char> samples;
	long bytes;
	// Keep reading until all is read
    do
    {
		// Read up to a buffer's worth of decoded sound data
		bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);

		if (bytes < 0)
			{
			ov_clear(&oggFile);
		//     cerr << "Error decoding " << fileName << "..." << endl;
			exit(-1);
			}
		// end if

		// Append to end of buffer
		samples.insert(samples.end(), array, array + bytes);
	}while (bytes > 0);

 	alBufferData(iBufferId, format, &samples[0], static_cast<ALsizei>(samples.size()), info->rate);

 	ov_clear(&oggFile);
	if ( CheckErrors( "LoadOgg") )
		throw;
}

int GameAudioWrapper::GetFreeBuffer()const
{
	int size = mUsedBuffers.size();
	for (int index = 0 ; index < size ; ++index)
	{
		if (!mUsedBuffers.test(index))
			return index;
	}
	return -1;
}

int GameAudioWrapper::GetFreeSource()const
{
	int size = mUsedSources.size();

	for (int index = 0 ; index < size ; ++index)
	{
		if (!mUsedSources.test(index))
			return index;
	}
	return -1;
}

bool GameAudioWrapper::Play(int iSoundId,bool iLoop, bool iForceRestart )const
{
	int sourceAudioState = 0;
 
	alGetError();
 
 
	ALint state ;
	alGetSourcei(mAudioSources[iSoundId], AL_SOURCE_STATE, &state);

	if ( state == AL_PLAYING )
	{
		if ( iForceRestart )
		{
			bool ret = Stop( iSoundId);
			if (!ret)
			return false;
		}
		else
			return false; 
	}
	
	alSourcei( mAudioSources[iSoundId], AL_LOOPING, iLoop );
	
	alSourcePlay(mAudioSources[iSoundId]);
	////// This is a busy wait loop but should be good enough for example purpose
	//do {
	//	// Query the state of the souce
	//	alGetSourcei(mAudioSources[iSoundId], AL_SOURCE_STATE, &state);
	//} while (state != AL_STOPPED);
	////
	if ( CheckErrors( "GameAudioWrapper::Play ") )
		return false;
 
	return true;
}

bool GameAudioWrapper::Stop(int iSoundId)const
{
	alGetError();
	ALint state;
	alGetSourcei(mAudioSources[iSoundId], AL_SOURCE_STATE, &state);

	if (state == AL_PLAYING || state == AL_PAUSED){
		alSourceStop( mAudioSources[iSoundId] );

		if (!CheckErrors("GameAudioWrapper::Stop"))
			return true;
	}
	return false;
}
bool GameAudioWrapper::Pause(int iSoundId)const
{
	alGetError();
	ALint state;
	alGetSourcei(mAudioSources[iSoundId], AL_SOURCE_STATE, &state);

	if (state == AL_PLAYING){
		alSourcePause( mAudioSources[iSoundId] );

		if (!CheckErrors("GameAudioWrapper::Pause"))
			return true;
	}
	return false;
}
bool GameAudioWrapper::PauseAll()const
{
	alGetError();
 
	alSourcePausev(  MAX_AUDIO_SOURCES, mAudioSources );
 
	if ( CheckErrors( "GameAudioWrapper::PauseAll") )
		return false;
 
	return true;
}
bool GameAudioWrapper::StopAll()const
{
	alGetError();
 
	alSourceStopv(  MAX_AUDIO_SOURCES, mAudioSources );
 
	if ( CheckErrors( "GameAudioWrapper::StopAll") )
		return false;
 
	return true;
}

bool GameAudioWrapper::Resume(int iSoundId)const
{
	alGetError();

	ALint state;
	alGetSourcei(mAudioSources[iSoundId], AL_SOURCE_STATE, &state);

	if (state == AL_PAUSED)
	{
		return Play(iSoundId,false);
	}
	return false;
}

bool GameAudioWrapper::ResumeAll()const
{
	ALint state;
	bool ret = true;
	for (int i = 0 ; i < MAX_AUDIO_SOURCES;++i)
	{
		alGetSourcei(mAudioSources[i], AL_SOURCE_STATE, &state);
		if (state == AL_PAUSED)
		{
			ret = ret &&  Resume(mAudioSources[i]);
		}
	}
	return ret;
}
void GameAudioWrapper::SetLoop(int iSourceId,ALboolean iLoop)
{
	alSourcei(mAudioSources[iSourceId], AL_LOOPING, iLoop);
}
void GameAudioWrapper::SetPitch(int iSourceId, ALfloat iVal)
{
	alSourcef( mAudioSources[iSourceId], AL_PITCH, iVal );
	
}
void GameAudioWrapper::SetGain(int iSourceId, ALfloat iVal)
{
	alSourcef( mAudioSources[iSourceId], AL_GAIN, iVal );
	
}
ALfloat GameAudioWrapper::GetPitch(int iSourceId)const
{
	ALfloat pitch = 0.0f;
	alGetSourcef(mAudioSources[iSourceId], AL_PITCH, &pitch);

	return pitch;
}
ALfloat GameAudioWrapper::GetGain(int iSourceId)const
{
	ALfloat gain = 0.0f;
	alGetSourcef(mAudioSources[iSourceId], AL_GAIN, &gain);

	return gain;
}
void  GameAudioWrapper::SetFloatProperty(int iSourceId, ALenum iProp, ALfloat iVal)
{
	alSourcef( mAudioSources[iSourceId], iProp, iVal );
}
ALfloat GameAudioWrapper::GetFloatProperty(int iSourceId, ALenum iProp)const
{
	ALfloat prop = 0.0f;
	alGetSourcef(mAudioSources[iSourceId], iProp, &prop);

	return prop;
}
void GameAudioWrapper::SetSourcePosition(int iSourceId, const ALfloat iX,const ALfloat iY,const ALfloat iZ)
{
	alSource3f(mAudioSources[iSourceId], AL_POSITION, iX,iY,iZ);
}

void GameAudioWrapper::SetListenerPosition(const ALfloat iX,const ALfloat iY,const ALfloat iZ)
{
	alListener3f( AL_POSITION,  iX,iY,iZ );
}
