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

Effect::Effect()
{
	flag = false;
	renderer.LoadTexture("ring.png");
	renderer.LoadTexture("explosion.jpg");
}

Effect::~Effect()
{
}

void Effect::BloodSplash(Vector2& position, float t)//�����Ԃ�//maru.png
{

}

void Effect::Afterimage(Vector2& position, float t)//�c��
{
}

void Effect::Explosion(Vector2  position, float t)//����ring.png
{
	/*if (!flag)
	{
		timer.SetTime(10);
		flag = true;
	}
	timer.Update();
	SetDrawBright(timer.Now() / 10 * 255, 0, 0);
	renderer.Draw("ring.png", position);
	renderer.Draw("ring.png", position.x, position.y + timer.Now() * 20);
	SetDrawBright(255, 255, 255);
	renderer.Draw("ring.png", timer.Rate() * 100 + position.x, position.y);*/


	//explosion.jpg
	
	if (!flag)
	{
		for (int i = 0; i < 12; i++)
		{
			motion.Add(i,&Rectangles(120 * (i % 3), 120 * (i % 3), 120, 120));
		}
		motion.Init(Range(0, 12), CountDownTimer(t));
		flag = true;
	}
	motion.Update();
	//DrawRectGraph(position.x, position.y, 0, 0, 1, 1;
	renderer.MotionDraw("explosion.jpg", position, motion.DrawwingRange());
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
