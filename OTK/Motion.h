#pragma once
#include <iostream>
#include <map>
#include "Range.h"
#include "CountDownTimer.h"
#include "Timer.h"
#include "Rectangles.h"


class Motion
{
public:
	Motion();
	Motion(Range range, Timer timer);
	~Motion();
	void Init(Range range, Timer timer);
	void Add(int index, Rectangles* rect);
	void Update();
	Rectangles* DrawwingRange();
private:
	void MotionUpdate();
	Range* range;
	Timer* timer;
	int motionNumber;
	std::map<int, Rectangles*> rectangles;
};

