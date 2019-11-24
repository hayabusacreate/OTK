#include "GamePlay.h"
#include "Player.h"
#include "Map.h"
#include "Vector2.h"
#include "Enemy.h"
#include "PlayerActionTime.h"
#include "GoalBlock.h"

#include "DxLib.h"

Map map;
Player player(Vector2(17, 4), map);
Enemy enemy(Vector2(12, 3), map);
Enemy enemy2(Vector2(3, 7), map);
Enemy enemy3(Vector2(7, 11), map);
Enemy enemy4(Vector2(12, 14), map);
Enemy enemy5(Vector2(11, 11), map);
Enemy enemy6(Vector2(14, 8), map);
Enemy enemy7(Vector2(17, 6), map);
Enemy enemy8(Vector2(18, 14), map);
Enemy enemy9(Vector2(21, 12), map);
Enemy enemy10(Vector2(24, 6), map);
PlayerActionTime pActiont;
GoalBlock goalblock(Vector2(3, 16));
GoalBlock goalblock2(Vector2(28, 4));
GoalBlock goalblock3(Vector2(28, 13));


GamePlay::GamePlay(ISceneChanger * changer)
	:BaseScene(changer)
{

}

void GamePlay::Initialize()
{
	PlaySoundFile("", DX_PLAYTYPE_LOOP);

	count = 0;

	player.Initialize();
	enemy.Initialize();
	enemy2.Initialize();
	enemy3.Initialize();
	enemy4.Initialize();
	enemy5.Initialize();
	enemy6.Initialize();
	enemy7.Initialize();
	enemy8.Initialize();
	enemy9.Initialize();
	enemy10.Initialize();
	pActiont.Initialize();
	goalblock.Initialize();
	goalblock2.Initialize();
	goalblock3.Initialize();
	map.Initialize();
}


void GamePlay::Update()
{
	player.Update();
	player.Action(pActiont.GetActionFlag());
	pActiont.Update(player.GetActionFlag(), enemy.GetScore());
	pActiont.Update(player.GetActionFlag(), enemy2.GetScore());
	pActiont.Update(player.GetActionFlag(), enemy3.GetScore());
	pActiont.Update(player.GetActionFlag(), enemy4.GetScore());
	pActiont.Update(player.GetActionFlag(), enemy5.GetScore());
	pActiont.Update(player.GetActionFlag(), enemy6.GetScore());
	pActiont.Update(player.GetActionFlag(), enemy7.GetScore());
	pActiont.Update(player.GetActionFlag(), enemy8.GetScore());
	pActiont.Update(player.GetActionFlag(), enemy9.GetScore());
	pActiont.Update(player.GetActionFlag(), enemy10.GetScore());
	enemy.Move(player.GetPosition(), player.GetScale(),player.GetActionFlag());
	enemy2.Move(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy3.Move(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy4.Move(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy5.Move(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy6.Move(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy7.Move(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy8.Move(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy9.Move(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy10.Move(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy2.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy3.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy4.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy5.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy6.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy7.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy8.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy9.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	enemy10.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	goalblock.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	goalblock2.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());
	goalblock3.HitPlayer(player.GetPosition(), player.GetScale(), player.GetActionFlag());

	count = goalblock.GetBreakCount() + goalblock2.GetBreakCount() + goalblock3.GetBreakCount();
	if (count == 3)
	{
		mSceneChanger->ChangeScene(eScene_Ending);
	}

	if (enemy.GetHitPlayer()||
		enemy2.GetHitPlayer() || 
		enemy3.GetHitPlayer() || 
		enemy4.GetHitPlayer() || 
		enemy5.GetHitPlayer() || 
		enemy6.GetHitPlayer() || 
		enemy7.GetHitPlayer() ||
		enemy8.GetHitPlayer() ||
		enemy9.GetHitPlayer() ||
		enemy10.GetHitPlayer())
	{
		PlaySoundFile("", DX_PLAYTYPE_BACK);
		player.SetActive(false);
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
	enemy2.Draw();
	enemy3.Draw();
	enemy4.Draw();
	enemy5.Draw();
	enemy6.Draw();
	enemy7.Draw();
	enemy8.Draw();
	enemy9.Draw();
	enemy10.Draw();
	goalblock.Draw();
	goalblock2.Draw();
	goalblock3.Draw();
}
