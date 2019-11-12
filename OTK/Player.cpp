#include "Player.h"
#include "Vector2.h"
#include "Input.h"
#include "DxLib.h"

Input input;
Vector2 position;

Player::Player() :
	Gravity(0.3f),
	JumpForce(9.0f),
	Speed(5.0f),
	scale(30),
	//position(320.0f, 240.0f),
	PlayerDownSpeed(0.0f),
	IsJumpFlag(false),
	ImgIndex(0),
	count(0)
{
	position = Vector2(320.0f, 240.0f);
}

Player::~Player()
{
}

void Player::Move()
{
	input.Update();

	// 移動量の初期化
	MoveX = 0.0f;
	MoveY = 0.0f;

	//左移動
	if ((input.GetKey() & PAD_INPUT_LEFT) != 0)
	{
		MoveX -= Speed;
	}

	//右移動
	if ((input.GetKey() & PAD_INPUT_RIGHT) != 0)
	{
		MoveX += Speed;
	}

	// 着地しているかつスペースが押されたとき
	if (IsJumpFlag == false && (input.GetKey() & PAD_INPUT_10) != 0)
	{
		PlayerDownSpeed -= JumpForce;
		IsJumpFlag = true;
	}

	// 落下処理;
	PlayerDownSpeed += Gravity;

	// 落下速度を移動量に加える
	MoveY = PlayerDownSpeed;

	// 移動量に基づいてキャラクタの座標を移動
	//CheckMapMove(&position.x, &position.y, &PlayerDownSpeed, MoveX, MoveY, scale, &IsJumpFlag);
	position.x = position.x + (MoveX);
}

void Player::Draw()
{
	// キャラクタの描画
	//DrawBox((int)(player.position.x - player.scale * 0.5F), (int)(player.position.y - player.scale * 0.5F),
	//	(int)(player.position.x + player.scale * 0.5F) + 1, (int)(player.position.y + player.scale * 0.5F) + 1,
	//	GetColor(255, 0, 0), TRUE);


	Vector2 RectPos(position.x - scale * 0.5f, position.y - scale * 0.5f);
	//renderer.Draw("player.png", RectPos);//通常描画

	//画像の読み込み
	LoadDivGraph("puddle.png", 6, 6, 1, 32, 32, anime);

	//表示する画像の番号を変更
	ImgIndex = count % 36;
	ImgIndex /= 6;//中に6が入るように設定する

	//アニメーション描画
	DrawGraph(position.x - scale * 0.5f, position.y - scale * 0.5f, anime[ImgIndex], true);
	//カウントを増やす
	++count;

	//アクションフラグがtrueの時
	/*if (IsActionFlag)
	{
		DrawBox((int)(player.position.x - player.scale * 2.0f), (int)(player.position.y - player.scale * 2.0f),
			(int)(player.position.x + player.scale * 2.0f) + 1, (int)(player.position.y + player.scale * 2.0f) + 1,
			GetColor(255, 0, 0), FALSE);

		//矩形の当たり判定
		auto dx = abs((player.position.x + player.scale / 2.f) - (enemy.position.x + enemy.scale / 2));
		auto dy = abs((player.position.y + player.scale / 2.f) - (enemy.position.y + enemy.scale / 2));

		//当たり判定は枠の大きさの弐倍で書く
		if (dx < (player.scale * 4 + enemy.scale) / 2 && dy < (player.scale * 4 + enemy.scale) / 2)
		{
			DrawString(0, 0, "枠の中に敵がいる!", GetColor(255, 0, 0));
			enemy.IsHitPlayer = true;
		}
    }*/
}

void Player::Hit(int hit)
{
	
	float Dummy = 0.0f;
	float hsize;
	// キャラクタの左上、右上、左下、右下部分に当たり判定のある
	// マップに衝突しているか調べ、衝突していたら補正する
	// 半分のサイズを算出
	//hsize = Size * 0.5f;
	//当たり判定の処理
	Move();
}

float Player::ReturnPosX()
{
	return position.x;
}

float Player::ReturnPosY()
{
	return position.y;
}

float Player::ReturnGra()
{
	return MoveY;
}
