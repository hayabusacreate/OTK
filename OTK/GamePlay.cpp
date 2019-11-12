#include "GamePlay.h"
#include "Timer.h"
#include "Player.h"
#include "Map.h"
#include "Renderer.h"

#include "DxLib.h"

Player player;
Map map;

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
	
}

void GamePlay::Update()
{
	//player.Move();
	player.Hit(
		map.MapHitCheck(player.ReturnPosX(),
			player.ReturnPosY(),
			0,
			player.ReturnGra()));
}

void GamePlay::Draw()
{
	map.Draw();
	player.Draw();

}
