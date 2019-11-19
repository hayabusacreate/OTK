#pragma once

class Range
{
public:
	Range(int first, int end);
	~Range();
	int First();
	int End();
	bool IsWithin(int num);
	bool IsOutOfRange();
	bool IsOutOfRange(int num);
private:
	int first;
	int end;
};
