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

void Effect::BloodSplash(Vector2 position, float t)//ŒŒ‚µ‚Ô‚«//maru.png
{

}

void Effect::Afterimage(Vector2 position, float t)//c‘œ
{
}

void Effect::Trajectory(Vector2 position, float t)//‹OÕ//bou.png
{
}

void Effect::Slashing(Vector2 position, float t)//aŒ‚
{
}

void Effect::Trigger(Vector2 position, float t)//ŠÔ’â~”­“®//giza.png
{
	
}

void Effect::End(Vector2 position, float t)//ŠÔ’â~I—¹//hosi.png
{
}

void Effect::Test(const char * filename, Vector2 position, float t)
{
	if (!flag)
	{
		flag = true;
		timer.SetTime(t);
	}
	timer.Update();
	//int GrHandle = LoadGraph(filename);
	//‹P“x‚Ìİ’è’l‚ğÔ‚É•ÏX

	SetDrawBright(255, 0, 0);
	//DrawRotaGraph(position.x, position.y, 1.0, t, GraphicHandle, TRUE);
	//renderer.Rotate(filename, position, -timer.Now() * 200, TRUE);
	//renderer.Rotate(filename, position, -timer.Now() * 100, TRUE);
	int GHandle = LoadGraph(filename);
	DrawRotaGraph3(position.x, position.y, 50, 50, 5.0f, 5.0f, -timer.Now() * 2, GHandle, TRUE);
	//Œ³‚É–ß‚·
	SetDrawBright(255, 255, 255);
	if (timer.IsTime())
	{
		flag = false;
	}
}
