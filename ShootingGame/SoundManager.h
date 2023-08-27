#pragma once
#include "SingletonBase.h"
#include <mmsystem.h>
#include <mciapi.h>

#pragma comment(lib, "Winmm.lib")
class SoundManager : public SingletonBase<SoundManager>
{
private:
	FMOD::System* pSystem;
	FMOD::Channel* pChannel[20];
	typedef map<string, FMOD::Sound*> mapSoundList;
	typedef map<string, FMOD::Sound*>::iterator mapSoundIter;

	mapSoundList _mSoundList;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	FMOD::Sound* addSoundFMOD(string key, const char* fileName);
	FMOD::Sound* addSoundFMOD(string key, const char* fileName, bool loop);
	FMOD::Sound* findSound(string key);
	void playSoundFMOD(string key, float volume);
	void stopSoundFMOD(string key);
	unsigned int getSoundLength(string key);
	unsigned int getCurrentPos(string key);
	bool isPlaying();
	void stopAllSoundFMOD();
	bool deleteAll();

	SoundManager() {};
	~SoundManager() {};
};

