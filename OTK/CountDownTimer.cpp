#include "Timer.h"
#include "CountDownTimer.h"
#include "DxLib.h"
#include <cmath>

CountDownTimer::CountDownTimer()
{
	Init();
}

CountDownTimer::~CountDownTimer()
{
}

void CountDownTimer::Init()
{
	currentTime = limitTime;
}

void CountDownTimer::Update()
{
	//int i = GetNowCount();
	currentTime = std::fmaxf(currentTime - 1.0f, 0.0f);
	//currentTime++;
}

bool CountDownTimer::IsTime()
{
	return currentTime <= 0.0f;
}

void CountDownTimer::SetTime(const float second)
{
	limitTime = 60.0f * second;
	Init();
}


float CountDownTimer::Rate()
{
	return 1.0f - currentTime / limitTime;
}

float CountDownTimer::Now()
{
	return currentTime / 60.0f;
}
