#include "PlayerActionTime.h"

PlayerActionTime::PlayerActionTime()
{

}

PlayerActionTime::~PlayerActionTime()
{
	DeleteGraph(img);
}

void PlayerActionTime::Initialize()
{
	img = LoadGraph("ActionGage.png");
	sizex = 1;
	sizey = 32;
	expansionX = 100.0f;
	MaxexpansionX = 100.f;
	IsActionFlag = false;

	key[256];
	pad = 0;
	InputFlag = 0;
}

void PlayerActionTime::Update(bool ActionFlag, int EnemyDeadScore)
{
	//キー入力更新
	InputKey();

	//最大値に到達したら最大値を入れる
	if (expansionX >= MaxexpansionX)
	{
		expansionX = MaxexpansionX;
	}

	//最小値に到達したら最小値を入れる
	if (expansionX <= MinexpansionX)
	{
		expansionX = MinexpansionX;
		//アクションフラグを無くす
		IsActionFlag = false;
	}
	if (expansionX >= MaxexpansionX * 0.5f)
	{
		//0になってから再び使うには50必要
		IsActionFlag = true;
	}

	//アクション実行確認
	if (ActionFlag == false)//してない
	{
		//常にゲージは増える
		expansionX += 1.f / 10.f;
	}
	else                   //してる
	{
		//スペースが押されたら（アクションがプレイヤーで実行されたら）
		if (/*key[KEY_INPUT_SPACE] == 1 || */pad & PAD_INPUT_B)
		{
			//前フレームで押していなければ
			if (InputFlag == 0)
			{
				expansionX -= 10;
			}
			//前フレームでボタンが押されたかをtrueにする
			InputFlag = 1;
		}
		else
		{
			//ボタンが押されていない場合は、falseにする
			InputFlag = 0;
		}

		expansionX += EnemyDeadScore;


		//1秒間に(1/15)*60の値を100で割った値でゲージが0になる
		//25秒でゲージが0になります
		expansionX -= 1.f / 15.f;
	}
}

void PlayerActionTime::InputKey()
{
	static char pushkey[256];
	GetHitKeyStateAll(pushkey);
	pad = GetJoypadInputState(DX_INPUT_PAD1);
	for (int i = 0; i < 256; i++)
	{
		//キーがnull出ないか?
		if (pushkey[i])
		{
			//1フレ前にボタンが押されていなかったら
			if (key[i] == 0)
			{
				key[i] = 1;
			}
			//1フレ前にボタンが押されていたら
			else if (key[i] == 1)
			{
				key[i] = 2;
			}
		}
		//何もなかったら
		else key[i] = 0;
	}
}

void PlayerActionTime::Draw(float x, float y)
{
	//左上の座標：右下の座標(現在の位置+画像の大きさ*拡大率)
	DrawExtendGraph(x, y, x + sizex * expansionX, y + sizey, img, FALSE);
}

bool PlayerActionTime::GetActionFlag()
{
	return IsActionFlag;
}

int PlayerActionTime::GetExpansionX()
{
	return expansionX;
}
