#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "DxLib.h"
#include <string>

class Renderer
{
public://‚¨‚¢‚©‚¯•`‰æ(name,position,)
	Renderer();
	~Renderer();
    void Draw(const char* failname, float x, float y);
	void Draw(const char* failname, float x, float y, float xx, float yy);
	void Rotate(const char* failname, float x, float y, double angle, int flag);
	void Rotate(const char* failname, float x, float y, float cx, float cy, float angle, int flag);
private:

};


#endif // !_RENDERER_H_
