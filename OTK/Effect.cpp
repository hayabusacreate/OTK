#include "Effect.h"
#include "Timer.h"
#include "CountDownTimer.h"
#include "Vector2.h"
#include "Renderer.h"
#include "Motion.h"
#include "Rectangles.h"

#include "DxLib.h"

Renderer renderer;
CountDownTimer timer;
Motion motion;

Effect::Effect():i(0),GHandle()
{
	flag = false;
	renderer.LoadTexture("ring.png");
	renderer.LoadTexture("explosion.jpg");
}

Effect::~Effect()
{
	for (i = 0; i < 12; i++)
	{
		DeleteGraph(GHandle[i]);
	}
}

void Effect::BloodSplash(Vector2& position, float t)//�����Ԃ�//maru.png
{

}

void Effect::Afterimage(Vector2& position, float t)//�c��
{
}

void Effect::Explosion(Vector2  position, float t)//����ring.png
{
	
	//explosion.jpg
	
	/*if (!flag)
	{
		for (int i = 0; i < 12; i++)
		{
			motion.Add(i,&Rectangles(120 * (i % 3), 120 * (i % 3), 120, 120));
		}
		motion.Init(Range(0, 12), CountDownTimer(t));
		flag = true;
	}
	motion.Update();
	renderer.MotionDraw("explosion.jpg", position, motion.DrawwingRange());*/
	if (!flag)
	{
		i = 0;
		GHandle[13];
		LoadDivGraph("explosion.png", 13, 3, 5, 120, 120, GHandle);
		flag = true;
	}
	int a = i / (t * 60);
	if (a < 13)
	{
		SetDrawBright(114, 178, 227);
		DrawGraph(position.x, position.y, GHandle[a], FALSE);
		SetDrawBright(255, 255, 255);
		
	}
	++i;
	if (a >= 20 )i = 0;
}

void Effect::Trajectory(Vector2& position, float t)//�O��//bou.png
{
}

void Effect::Slashing(Vector2& position, float t)//�a��
{
}

void Effect::Trigger(Vector2& position, float t)//���Ԓ�~����//giza.png
{
	
}

void Effect::End(Vector2& position, float t)//���Ԓ�~�I��//hosi.png
{
}

void Effect::Test(const char * filename, Vector2 position, float t)
{
	
}
