#include "Sound.h"

#include "DxLib.h"

std::unordered_map<const char*, int>Sound::soundfile;

Sound::Sound()
{

}

Sound::~Sound()
{

}

void Sound::Init(const char * filename)
{
	 soundfile[filename] = LoadSoundMem(filename);
}

void Sound::PlayBGM(const char * filename)
{
	if (filename == "GamePlayBGM.mp3")
	{
		ChangeVolumeSoundMem(255 * 80 / 100, soundfile[filename]);
	}
	PlaySoundMem(soundfile[filename], DX_PLAYTYPE_LOOP);
}

void Sound::PlaySE(const char * filename)
{
	PlaySoundMem(soundfile[filename], DX_PLAYTYPE_BACK);
}

void Sound::StopBGM(const char * filename)
{
	StopSoundMem(soundfile[filename]);
}

void Sound::End()
{
	InitSoundMem();
}
