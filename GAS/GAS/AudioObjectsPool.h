#pragma once

#include <vector>

#include "AudioObject.h"

namespace GAS
{

class AudioObjectsPool
{
public:
	AudioObjectsPool(void);
	~AudioObjectsPool(void);

	bool HasFreeSpace();

private:

	std::vector<AudioObject> mAudioObjPool;
};

}
