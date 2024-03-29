#include "GoalBlock.h"

GoalBlock::GoalBlock(Vector2 InitPos)
	:_position(InitPos.x * 64, InitPos.y * 64), _scale(Vector2(64, 64))
{

}

GoalBlock::~GoalBlock()
{

}

void GoalBlock::Initialize()
{
	img = LoadGraph("GoalObj.png");
	IsBreak = false;
	BreakCount = 0;
}

void GoalBlock::HitPlayer(Vector2 PlayerPos, Vector2 PlayerScale, bool ActionFlag)
{
	//プレイヤーとの当たり判定
	auto dx = abs((PlayerPos.x + PlayerScale.x * 0.5f) - (_position.x + _scale.x * 0.5f));
	auto dy = abs((PlayerPos.y + PlayerScale.y * 0.5f) - (_position.y + _scale.y * 0.5f));

	//当たっているか
	if (dx < (PlayerScale.x + _scale.x) / 2 && dy < (PlayerScale.y + _scale.y * 2))
	{
		if (ActionFlag)
		{
			if (IsBreak == false)
			{
				PlaySoundFile("", DX_PLAYTYPE_BACK);
				BreakCount += 1;
				IsBreak = true;
			}
			else
			{
				IsBreak = true;
			}
		}
	}
}

void GoalBlock::Draw()
{
	if (IsBreak) return;

	DrawGraph(_position.x - _scale.x, _position.y - _scale.y, img, TRUE);
}

int GoalBlock::GetBreakCount()
{
	return BreakCount;
}
