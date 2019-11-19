#pragma once
#include <iostream>
#include <map>
#include "Range.h"
#include "CountDownTimer.h"
#include "Rectangles.h"


class Motion
{
public:
	Motion();
	Motion(Range range, CountDownTimer timer);
	~Motion();
	void Init(Range range, CountDownTimer timer);
	void Add(int index, Rectangles* rect);
	void Update();
	Rectangles* DrawwingRange();
private:
	void MotionUpdate();
	Range* range;
	CountDownTimer timer;
	int motionNumber;
	std::map<int, Rectangles*> rectangles;
};

