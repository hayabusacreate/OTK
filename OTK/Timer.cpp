#include "Timer.h"

Timer::Timer(float second)
{
	limitTime = 60.0f*second;
}

Timer::~Timer()
{

}

void Timer::Init()
{

}

void Timer::Update(){}

bool Timer::IsTime()
{
	return currentTime <= 0.0f;
}


void Timer::SetTime(const float second)
{
	limitTime = 60.0f * second;
}

float Timer::Now()
{
	return currentTime / 60.0f;
}

float Timer::Rate()
{
	return 0.0f;
}
