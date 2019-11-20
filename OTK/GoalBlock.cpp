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
	//ÉvÉåÉCÉÑÅ[Ç∆ÇÃìñÇΩÇËîªíË
	auto dx = abs((PlayerPos.x + PlayerScale.x * 0.5f) - (_position.x + _scale.x * 0.5f));
	auto dy = abs((PlayerPos.y + PlayerScale.y * 0.5f) - (_position.y + _scale.y * 0.5f));

	//ìñÇΩÇ¡ÇƒÇ¢ÇÈÇ©
	if (dx < (PlayerScale.x + _scale.x) / 2 && dy < (PlayerScale.y + _scale.y * 2))
	{
		if (ActionFlag)
		{
			if (IsBreak == false)
			{
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
	if (!IsBreak)
	{
		DrawGraph(_position.x - _scale.x , _position.y - _scale.y, img, TRUE);
		//DrawBox((int)(_position.x - _scale.x * 0.5F), (int)(_position.y - _scale.y * 0.5F),
		//	(int)(_position.x + _scale.x * 0.5F) + 1, (int)(_position.y + _scale.y * 0.5F) + 1,
		//	GetColor(255, 255, 255), TRUE);
	}
}

int GoalBlock::GetBreakCount()
{
	return BreakCount;
}
