#pragma once
#include "DxLib.h"
#include "Vector2.h"

class TimeStop
{
public:
	TimeStop();
	//������
	void Initialize();
	//�g��
	void Expansion();
	//�k��
	void Shrink();

	void Draw(Vector2 pos);

private:
	float expansion;
	float Maxexpansion;
	float Minexpansion;
	int ImageHandle;
	Vector2 size;
};
