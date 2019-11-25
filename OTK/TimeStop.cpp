#include "TimeStop.h"

TimeStop::TimeStop()
{
}

void TimeStop::Initialize()
{
	ImageHandle = LoadGraph("block.png");
	expansion = 0;
	Maxexpansion = 1000;
	Minexpansion = 0;
	size = Vector2(32, 32);
}

void TimeStop::Expansion()
{
	expansion += 10;
	//‰æ‘œ‚ðŠg‘å

	if (expansion >= Maxexpansion)
	{
		expansion = Maxexpansion;
	}
}

void TimeStop::Shrink()
{
	expansion -= 50;

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
