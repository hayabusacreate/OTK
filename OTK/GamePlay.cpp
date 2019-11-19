#include "GamePlay.h"
#include "Player.h"
#include "Map.h"
#include "Vector2.h"
#include "Enemy.h"
#include "PlayerActionTime.h"
#include "GoalBlock.h"

#include "DxLib.h"

Map map;
Player player(Vector2(10, 10), map);
Enemy enemy(Vector2(12, 10), map);
PlayerActionTime pActiont;
GoalBlock goalblock(Vector2(14, 8));
GoalBlock goalblock2(Vector2(8, 2));


GamePlay::GamePlay(ISceneChanger * changer)
	:BaseScene(changer)
{

}

void GamePlay::Initialize()
{
	count = 0;

	player.Initialize();
	enemy.Initialize();
	pActiont.Initialize();
	goalblock.Initialize();
	goalblock2.Initialize();
	map.Initialize();
}


void GamePlay::Update()
{
	player.Update();
	player.Action(pActiont.GetActionFlag());
	pActiont.Update(player.GetActionFlag(), enemy.GetScore());
	//enemy.Move(player.GetPosition(), player.GetScale());
	enemy.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	goalblock.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	goalblock2.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());

	//if (CheckHitKey(KEY_INPUT_W) != 0)//W
	//{
	//	mSceneChanger->ChangeScene(eScene_Ending);
	//}

	count = goalblock.GetBreakCount() + goalblock2.GetBreakCount();

	if (count == 2)
	{
		mSceneChanger->ChangeScene(eScene_Ending);
	}

}

void GamePlay::Draw()
{
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	map.Draw();
	pActiont.Draw(0, 0);
	player.Draw();
	enemy.Draw();
	goalblock.Draw();
	goalblock2.Draw();
}
