#ifndef _TIMER_H_
#define _TIMER_H_


class Timer
{
public:
	Timer(float second);
	virtual ~Timer();
	virtual void Init();
	virtual void Update();
	virtual bool IsTime();
	virtual void SetTime(const float second);
	virtual float Now();
	virtual float Rate();
protected:
	float limitTime;
	float currentTime;
};


#endif // !TIMER_H_
