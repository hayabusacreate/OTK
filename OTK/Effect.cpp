#include "Effect.h"
#include "Timer.h"
#include "CountDownTimer.h"
#include "Vector2.h"
#include "Renderer.h"

#include "DxLib.h"

Renderer renderer;
CountDownTimer timer;


Effect::Effect()
{
	flag = false;
}

Effect::~Effect()
{
}

void Effect::BloodSplash(const char * filename, Vector2 position, float t)//ŒŒ‚µ‚Ô‚«//maru.png
{

}

void Effect::Afterimage(const char * filename, Vector2 position, float t)//c‘œ
{
}

void Effect::Trajectory(const char * filename, Vector2 position, float t)//‹OÕ//bou.png
{
}

void Effect::Slashing(const char * filename, Vector2 position, float t)//aŒ‚
{
}

void Effect::Trigger(const char * filename, Vector2 position, float t)//ŠÔ’â~”­“®
{//giza.png
	if (!flag)
	{
		flag = true;
		timer.SetTime(t);
	}
	timer.Update();
	//int GrHandle = LoadGraph(filename);
	//‹P“x‚Ìİ’è’l‚ğÔ‚É•ÏX

	SetDrawBright(255, 255, 0);
	//DrawRotaGraph(position.x, position.y, 1.0, t, GraphicHandle, TRUE);
	renderer.Rotate(filename, position, -timer.Now()*200, TRUE);
	//Œ³‚É–ß‚·
	SetDrawBright(255, 255, 255);	if (timer.IsTime())
	{
		flag = false;
	}
}

void Effect::End(const char * filename, Vector2 position, float t)//ŠÔ’â~I—¹//hosi.png
{
}
