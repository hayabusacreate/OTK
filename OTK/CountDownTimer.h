#ifndef _COUNTDOWN_TIMER_H_
#define _COUNTDOWN_TIMER_H_

#include "Timer.h"

class CountDownTimer:public Timer
{
public:
	CountDownTimer();
	CountDownTimer(float t);
	~CountDownTimer();
	void Init();
	void Update();
	bool IsTime();
	void SetTime(const float second);
	float Rate();
	float Now();
};


#endif // !_COUNTDOWN_TIMER_H_
