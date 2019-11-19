#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "DxLib.h"
#include "Vector2.h"
#include "Rectangles.h"
#include <string>

#include <iostream>
#include <map>

class Renderer
{
public://‚¨‚¢‚©‚¯•`‰æ(name,position,)
	Renderer();
	~Renderer();
	void LoadTexture(const char* failname);
	void Draw(const char* failname, float x, float y);
	void Draw(const char* failname, float x, float y, float xx, float yy);
	void Draw(const char* failname, Vector2 position);
	void Draw(const char* failname, Vector2 position, Vector2 scale);
	void Rotate(const char* failname, float x, float y, double angle, int flag);
	void Rotate(const char* failname, float x, float y, float cx, float cy, float angle, int flag);
	void Rotate(const char* failname, Vector2 position, double angle, int flag);
	void Rotate(const char* failname, Vector2 position, Vector2 scale, float angle, int flag);
	void MotionDraw(const char* failname, Vector2 position, Rectangles* rect);
private:
	std::map<std::string, int> texture;
};


#endif // !_RENDERER_H_
