#include "TimeStop.h"

TimeStop::TimeStop()
{
}

void TimeStop::Initialize()
{
	ImageHandle = LoadGraph("ActionGage.png");
	expansion = 0;
	Maxexpansion = 2500;
	Minexpansion = 0;
	size = Vector2(1, 32);
}

void TimeStop::Expansion()
{
	expansion += 200;
	//‰æ‘œ‚ðŠg‘å

	if (expansion >= Maxexpansion)
	{
		expansion = Maxexpansion;
	}
}

void TimeStop::Shrink()
{
	expansion -= 250;

	if (expansion <= Minexpansion)
	{
		expansion = Minexpansion;
	}
}

void TimeStop::Draw(Vector2 pos)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
	DrawRotaGraph(pos.x, pos.y, expansion, 0, ImageHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
