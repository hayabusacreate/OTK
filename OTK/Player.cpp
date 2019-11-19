#include "Player.h"
#include "Input.h"

Input input;

//コンストラクタ
Player::Player(Vector2 pos, Map map)
	:_position(pos.x * 32, pos.y * 32), _scale(Vector2(30, 30))
{
	this->_map = map;
}

//デストラクタ
Player::~Player()
{
	DeleteGraph(img);
}

void Player::Initialize()
{
	Gravity = 0.3f;
	JumpForce = 9.0f;
	MoveSpeed = 5.0f;
	PlayerDownSpeed = 0.0f;
	IsJumpFlag = false;

	anime[6] = { 0 };
	ImgIndex = 0;
	count = 0;
	//画像の読み込み
	img = LoadDivGraph("puddle.png", 6, 6, 1, 32, 32, anime);


	ActionFlag = false;
	ActionCount = 0;
	radian = 0;

	key[256];
	pad = 0;

	InputX = 0;
	InputY = 0;

	InputFlag = 0;
}

void Player::Update()
{
	if (ActionCount == 0)
	{
		Move();
	}

	pad = GetJoypadInputState(DX_INPUT_PAD1);

	InputKey_PAD();
}

//プレイヤーInputクラス(できればライブラリ化？したかった)
void Player::InputKey_PAD()
{
	static char pushkey[256];
	GetHitKeyStateAll(pushkey);
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

	for (int i = 0; i < 28; i++)
	{
		if (pad & (1 << i))//ボタンiの入力フラグが立っていたら
		{
			DrawFormatString(0, i * 15, GetColor(255, 255, 255), "%dのキーが押されています", i);
		}
	}
}

void Player::Move()
{
	//移動量の生成
	Vector2 velocity;

	velocity = Vector2(0, 0);

	//左移動
	if (/*key[KEY_INPUT_LEFT] == 2 ||*/
		(pad & PAD_INPUT_LEFT))
	{
		velocity.x -= MoveSpeed;
	}

	//右移動
	if (/*key[KEY_INPUT_RIGHT] == 2 ||*/
		(pad & PAD_INPUT_RIGHT))
	{
		velocity.x += MoveSpeed;
	}


	// 着地しているかつスペースが押されたとき
	if (IsJumpFlag == false)
	{
		if (/*(key[KEY_INPUT_SPACE] == 1) || */(pad & PAD_INPUT_B))
		{
			//前フレームで押していなければ
			if (InputFlag == 0)
			{
				PlayerDownSpeed -= JumpForce;
				IsJumpFlag = true;
			}
			//前フレームでボタンが押されたかをtrueにする
			InputFlag = 1;
		}
		else
		{
			//ボタンが押されていない場合は、falseにする
			InputFlag = 0;
		}
	}

	// 落下処理;
	PlayerDownSpeed += Gravity;

	// 落下速度を移動量に加える
	velocity.y = PlayerDownSpeed;

	//移動
	CheckMapMove(_position, &PlayerDownSpeed, velocity, _scale, &IsJumpFlag);
}


//アクション実行(PlayerActionTimeのアクションフラグ:敵の位置:敵の大きさ)
void Player::Action(bool IsActionFlag)
{
	//移動量の初期化
	Vector2 velocity;
	velocity = Vector2(0, 0);

	//0の時はアクションしていない
	if (ActionCount == 0) ActionFlag = false;
	//アクションしている
	else ActionFlag = true;

	//ゲージが0より大きいとき
	if (IsActionFlag == true)
	{
		//通常状態
		if (ActionCount == 0)
		{
			//&zキーが押されたら
			if (/*key[KEY_INPUT_Z] == 1 || */(pad & PAD_INPUT_A))
			{
				//前フレームで押していなければ
				if (InputFlag == 0)
				{
					ActionCount = 1;
				}
				//前フレームでボタンが押されたかをtrueにする
				InputFlag = 1;
			}
			else
			{
				//ボタンが押されていない場合は、falseにする
				InputFlag = 0;
			}
		}
		//方向入力状態
		else if (ActionCount == 1)
		{
			//ジョイパッドのスティック入力取得
			GetJoypadAnalogInput(&InputX, &InputY, DX_INPUT_PAD1);

			radian = atan2((float)InputY - _position.y, (float)InputX - _position.x);

			if (/*key[KEY_INPUT_Z] == 1 || */pad & PAD_INPUT_A)
			{
				//前フレームで押していなければ
				if (InputFlag == 0)
				{
					ActionCount = 0;
				}
				//前フレームでボタンが押されたかをtrueにする
				InputFlag = 1;
			}
			else if (/*key[KEY_INPUT_SPACE] == 1 || */pad & PAD_INPUT_B)
			{
				//前フレームで押していなければ
				if (InputFlag == 0)
				{
					ActionCount = 2;
				}
				//前フレームでボタンが押されたかをtrueにする
				InputFlag = 1;
			}
			else
			{
				//ボタンが押されていない場合は、falseにする
				InputFlag = 0;
			}
		}
		//移動
		else if (ActionCount == 2)
		{
			velocity.x += MoveSpeed * cos(radian);
			velocity.y += MoveSpeed * sin(radian);

			StartJoypadVibration(DX_INPUT_PAD1, 500,1);
		}

		//移動
		CheckMapMove(_position, &PlayerDownSpeed, velocity, _scale, &IsJumpFlag);
	}
	//ゲージが0より小さいなら、アクション出来なくする
	else
	{
		ActionCount = 0;
	}
}


void Player::Draw()
{
	//アクションモードが1の時
	if (ActionCount == 1)
	{
		//敵の索敵範囲仮で表示
		DrawBox((int)(_position.x - _scale.x * 2.0f), (int)(_position.y - _scale.y * 2.0f),
			(int)(_position.x + _scale.x * 2.0f) + 1, (int)(_position.y + _scale.y * 2.0f) + 1,
			GetColor(0, 255, 0), FALSE);
	}
	else
	{
		//敵の索敵範囲仮で表示
		DrawBox((int)(_position.x - _scale.x * 2.0f), (int)(_position.y - _scale.y * 2.0f),
			(int)(_position.x + _scale.x * 2.0f) + 1, (int)(_position.y + _scale.y * 2.0f) + 1,
			GetColor(255, 255, 0), FALSE);
	}
	//表示する画像の番号を変更
	ImgIndex = count % 36;
	ImgIndex /= 6;//中に6が入るように設定する

	//アニメーション描画
	DrawGraph(_position.x - _scale.x * 0.5f, _position.y - _scale.y * 0.5f, anime[ImgIndex], true);
	//カウントを増やす
	++count;

}

int Player::CheckMapMove(Vector2 pos, float * PDownS, Vector2 velocity, Vector2 scale, bool * JumpFlag)
{
	float Dummy = 0.0f;
	Vector2 hsize;

	// キャラクタの左上、右上、左下、右下部分に当たり判定のある
	// マップに衝突しているか調べ、衝突していたら補正する
	// 半分のサイズを算出
	hsize = _scale * 0.5f;
	// 左下がブロックの上に当たったら落下を止める
	if (_map.MapHitCheck(_position.x - hsize.x, _position.y + hsize.y, &Dummy, &velocity.y) == 3)
	{
		*PDownS = 0.0f;
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

	// 右下がブロックの上当たっていたら落下を止める
	if (_map.MapHitCheck(_position.x + hsize.x, _position.y + hsize.y, &Dummy, &velocity.y) == 3)
	{
		*PDownS = 0.0f;
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

	// 左上がブロックの下に当たっていたら落下させる
	if (_map.MapHitCheck(_position.x - hsize.x, _position.y - hsize.y, &Dummy, &velocity.y) == 4)
	{
		*PDownS = 1.0f;
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

	// 右下がブロックの下に当たっていたら落下させる
	if (_map.MapHitCheck(_position.x + hsize.x, _position.y - hsize.y, &Dummy, &velocity.y) == 4)
	{
		*PDownS = 1.0f;
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

	// 上下移動成分を加算
	_position.y += velocity.y;

	// 左下のチェック
	if (_map.MapHitCheck(_position.x - hsize.x, _position.y + hsize.y, &velocity.x, &Dummy) == 2)
	{
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

	// 右下のチェック
	if (_map.MapHitCheck(_position.x + hsize.x, _position.y + hsize.y, &velocity.x, &Dummy) == 1)
	{
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

	// 左上のチェック
	if (_map.MapHitCheck(_position.x - hsize.x, _position.y - hsize.y, &velocity.x, &Dummy) == 2)
	{
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

	// 右上のチェック
	if (_map.MapHitCheck(_position.x + hsize.x, _position.y - hsize.y, &velocity.x, &Dummy) == 1)
	{
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

#pragma region ターゲットがいるとき
	//// 左下のチェック
	//if (_map.MapHitCheck(_position.x - hsize.x, _position.y + hsize.y, &velocity.x, &Dummy) == 2)
	//{
	//	if (ActionCount == 3)
	//	{
	//		ActionCount = 1;
	//	}
	//}

	//// 右下のチェック
	//if (_map.MapHitCheck(_position.x + hsize.x, _position.y + hsize.y, &velocity.x, &Dummy) == 1)
	//{
	//	if (ActionCount == 3)
	//	{
	//		ActionCount = 1;
	//	}
	//}

	//// 左上のチェック
	//if (_map.MapHitCheck(_position.x - hsize.x, _position.y - hsize.y, &velocity.x, &Dummy) == 2)
	//{
	//	if (ActionCount == 3)
	//	{
	//		ActionCount = 1;
	//	}
	//}

	//// 右上のチェック
	//if (_map.MapHitCheck(_position.x + hsize.x, _position.y - hsize.y, &velocity.x, &Dummy) == 1)
	//{
	//	if (ActionCount == 3)
	//	{
	//		ActionCount = 1;
	//	}
	//}
#pragma endregion

	// 左右移動成分を加算
	_position.x += velocity.x;

	// キャラクタの左下と右下の1ピクセル下にブロックがあるか?
	if (_map.GetMapChip(_position.x - hsize.x, _position.y + hsize.y + 1.0f) == 0 &&
		_map.GetMapChip(_position.x + hsize.x, _position.y + hsize.y + 1.0f) == 0)
	{
		//無かったらジャンプ中にする
		*JumpFlag = true;
	}
	else
	{
		// あったらfalse
		*JumpFlag = false;
	}

	return 0;
}

//プレイヤーの位置取得
Vector2 Player::GetPosition()
{
	return Vector2(_position.x, _position.y);
}

Vector2 Player::GetScale()
{
	return Vector2(_scale.x, _scale.y);
}

bool Player::GetActionFlag()
{
	return ActionFlag;
}


