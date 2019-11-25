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
	renderer.LoadTexture("explosion2.png");
	renderer.LoadTexture("zangeki.png");
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

void Effect::BloodSplash(Vector2& position, float t)//ติซ//maru.png
{

}

void Effect::Afterimage(Vector2& position, float t)//c
{
}

void Effect::Explosion(Vector2  position, float t)//ญring.png
{
	if (!flag)
	{
		count = 0;
		flag = true;
		img[13];
		
		LoadDivGraph("explosion2.png", 13, 3, 5, 120, 120, img);
	}
	
	count++;
	int a = count/ (t * 60) ;
	if (a < 14) 
	{
		SetDrawBright(134, 245, 253);
		DrawGraph(position.x - 60, position.y - 60, img[a], TRUE);
		SetDrawBright(255, 255, 255);
	}
	if (a >= 13)count = 10000;
}

void Effect::Trajectory(Vector2& position, float t)//Oี//bou.png
{
	//renderer.Draw("zangeki.png", position.x, position.y);
	DrawGraph(position.x-128, position.y-128, LoadGraph("zangeki.png"), TRUE);
}

void Effect::Slashing(Vector2& position, float t)//a
{

}

void Effect::Trigger(Vector2& position, float t)//ิโ~ญฎ//giza.png
{
	
}

void Effect::End(Vector2& position, float t)//ิโ~Iน//hosi.png
{
}

void Effect::Test(const char * filename, Vector2 position, float t)
{
	
}
