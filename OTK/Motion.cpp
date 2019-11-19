#include <iostream>
#include <map>
#include "Motion.h"
#include "Range.h"
#include "CountDownTimer.h"
#include "Rectangles.h"



Motion::Motion()
{
	Init(Range(0, 0),CountDownTimer());
}

Motion::Motion(Range range, CountDownTimer timer)
{
	Init(range, timer);
}

Motion::~Motion()
{
}

void Motion::Init(Range range, CountDownTimer timer)
{
	this->range = &range;
	this->timer = timer;
	motionNumber = range.First();
}

void Motion::Add(int index, Rectangles* rect)
{
	/*if (rectangles.ContainsKey(index))
	{
		return;
	}*/
	if (rectangles.count(index))
	{
		return;
	}
	//rectangles.Add(index, rect);
	rectangles[index] = rect;
}

void Motion::Update()
{
	if (range->IsOutOfRange())
	{
		return;
	}
	timer.Update();
	if (timer.IsTime())
	{
		timer.Init();
		MotionUpdate();
	}
}

Rectangles* Motion::DrawwingRange()
{
	return rectangles[motionNumber];
}

void Motion::MotionUpdate()
{
	motionNumber += 1;
	if (range->IsOutOfRange(motionNumber))
	{
		motionNumber = range->First();
	}
}
