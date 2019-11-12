#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "DxLib.h"
#include "Vector2.h"
#include <string>

class Renderer
{
public://‚¨‚¢‚©‚¯•`‰æ(name,position,)
	Renderer();
	~Renderer();
	void Draw(const char* failname, Vector2 position);
	void Draw(const char* failname, Vector2 position, Vector2 scale);
	void Rotate(const char* failname, Vector2 position, double angle, int flag);
	void Rotate(const char* failname, Vector2 position, Vector2 scale, float angle, int flag);
private:

};


#endif // !_RENDERER_H_
