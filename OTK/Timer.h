#ifndef _TIMER_H_
#define _TIMER_H_


class Timer
{
public:
	virtual ~Timer() {};
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual bool IsTime() = 0;
	virtual void SetTime(const float second) = 0;
	virtual float Now() = 0;
	virtual float Rate() = 0;
protected:
	float limitTime;
	float currentTime;
};


#endif // !TIMER_H_
