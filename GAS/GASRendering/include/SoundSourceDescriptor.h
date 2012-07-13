#pragma once

#include <al.h>
namespace GAS
{

struct SoundSourceDescriptor
{
	
	ALfloat position[3];
	ALfloat velocity[3];
	ALfloat orientation[6];

	float pitch;
	float gain;
	bool loop;
	float reference_distance;

};

struct DefualtSoundSourceDescriptor : public SoundSourceDescriptor
{
	DefualtSoundSourceDescriptor()
	{
		position[0] = position[1] = position[2]= 0.0f;
		velocity[0] = velocity[1] = velocity[2]= 0.0f;
		orientation[0] = 0.0f;
		orientation[1] = 0.0f;
		orientation[2] = -1.0f;
		orientation[3] = 0.0f;
		orientation[4] = 1.0f;
		orientation[5] = 0.0f;

		pitch = 1.0f;
		gain = 0.8f;
		loop = false;
		reference_distance = 200;
	}
};
}