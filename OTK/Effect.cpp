#include "Effect.h"
#include "Timer.h"
#include "CountDownTimer.h"
#include "Vector2.h"
#include "Renderer.h"
#include "Motion.h"
#include "Rectangles.h"

#include "DxLib.h"

Renderer renderer;

Effect::Effect()
{
	flag = false;
	renderer.LoadTexture("ring.png");
	renderer.LoadTexture("explosion.jpg");
}

Effect::~Effect()
{
}

void Effect::Init()
{
	flag = false;
	count = 0;
	img[9999];
}

void Effect::BloodSplash(Vector2& position, float t)//ååÇµÇ‘Ç´//maru.png
{

}

void Effect::Afterimage(Vector2& position, float t)//écëú
{
}

void Effect::Explosion(Vector2  position, float t)//îöî≠ring.png
{
	if (!flag)
	{
		count = 0;
		flag = true;
		img[13];
		
		LoadDivGraph("explosion.jpg", 13, 3, 5, 120, 120, img);
	}
	
	count++;
	int a = count/ (t * 60) ;
	if (a < 14)DrawGraph(position.x - 60, position.y - 60, img[a], FALSE);
	if (a >= 13)count = 10000;
}

void Effect::Trajectory(Vector2& position, float t)//ãOê’//bou.png
{
}

void Effect::Slashing(Vector2& position, float t)//éaåÇ
{
}

void Effect::Trigger(Vector2& position, float t)//éûä‘í‚é~î≠ìÆ//giza.png
{
	
}

void Effect::End(Vector2& position, float t)//éûä‘í‚é~èIóπ//hosi.png
{
}

void Effect::Test(const char * filename, Vector2 position, float t)
{
	
}
