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
	renderer.LoadTexture("ring.png");
	
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
	if (!flag)
	{
		timer.SetTime(10);
		flag = true;
	}
	timer.Update();
	SetDrawBright(timer.Now() / 10 * 255, 0, 0);
	renderer.Draw("ring.png", position);
	renderer.Draw("ring.png", position.x, position.y + timer.Now() * 20);
	SetDrawBright(255, 255, 255);
	renderer.Draw("ring.png", timer.Rate() * 100 + position.x, position.y);
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
	if (!flag)
	{
		flag = true;
		timer.SetTime(t);
	}
	timer.Update();
	//int GrHandle = LoadGraph(filename);
	//�P�x�̐ݒ�l��ԂɕύX

	SetDrawBright(255, 0, 0);
	//DrawRotaGraph(position.x, position.y, 1.0, t, GraphicHandle, TRUE);
	//renderer.Rotate(filename, position, -timer.Now() * 200, TRUE);
	//renderer.Rotate(filename, position, -timer.Now() * 100, TRUE);
	int GHandle = LoadGraph(filename);
	DrawRotaGraph3(position.x, position.y, 50, 50, 5.0f, 5.0f, -timer.Now() * 2, GHandle, TRUE);
	//���ɖ߂�
	SetDrawBright(255, 255, 255);
	if (timer.IsTime())
	{
		flag = false;
	}
}
