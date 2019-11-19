#pragma once

class Rectangles
{
public:
	Rectangles(int x, int y, int width, int height);
	~Rectangles();
	int Rx();
	int Ry();
	int Rwidth();
	int Rheight();
private:
	int x;
	int y;
	int width;
	int height;
};
