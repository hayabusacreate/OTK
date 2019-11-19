#include "Rectangles.h"

Rectangles::Rectangles(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Rectangles::~Rectangles()
{
}

inline int Rectangles::Rx()
{
	return x;
}

inline int Rectangles::Ry()
{
	return y;
}

inline int Rectangles::Rwidth()
{
	return width;
}

inline int Rectangles::Rheight()
{
	return height;
}
