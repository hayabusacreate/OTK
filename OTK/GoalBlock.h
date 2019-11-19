#pragma once

#include <DxLib.h>
#include "Vector2.h"

class GoalBlock
{
public:
	GoalBlock(Vector2 InitPos);

	~GoalBlock();

	void Initialize();

	void HitPlayer(Vector2 PlayerPos, Vector2 PlayerScale, bool IsAction);

	void Draw();

	int GetBreakCount();


private:
	Vector2 _position;
	Vector2 _scale;
	int img;
	int BreakCount;

	bool IsBreak;
};
