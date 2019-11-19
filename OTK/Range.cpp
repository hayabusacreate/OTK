#include "Range.h"

Range::Range(int first, int end)
{
	this->first = first;
	this->end = end;
}

Range::~Range()
{
}

int Range::First()
{
	return first;
}

int Range::End()
{
	return end;
}

bool Range::IsWithin(int num)
{
	if (num < first)
	{
		return false;
	}
	if (num > end)
	{
		return false;
	}
	return true;
}

bool Range::IsOutOfRange()
{
	return first >= end;
}

bool Range::IsOutOfRange(int num)
{
	return !IsWithin(num);
}
