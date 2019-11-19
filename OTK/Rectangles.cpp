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

int Rectangles::Rx()
{
	return x;
}

int Rectangles::Ry()
{
	return y;
}

int Rectangles::Rwidth()
{
	return width;
}

int Rectangles::Rheight()
{
	return height;
}
