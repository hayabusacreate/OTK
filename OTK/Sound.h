#pragma once

#include <map>
#include <unordered_map>
class Sound
{
public:
	Sound();
	~Sound();
	void Init(const char* filename);
	void PlayBGM(const char* filename);
	void PlaySE(const char* filename);
	void StopBGM(const char* filename);
	void End();

	//static std::map<const char*, int>soundfiles;
	static std::unordered_map<const char*, int>soundfile;
};

