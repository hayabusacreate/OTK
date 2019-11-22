#include "Player.h"

//コンストラクタ
Player::Player(Vector2 pos, Map map)
	:SetFastPosition(pos.x * 60, pos.y * 60), _scale(Vector2(60, 60))
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
	//指定位置の初期化
	_position = SetFastPosition;
	Gravity = 0.3f;
	JumpForce = 9.0f;
	MoveSpeed = 3.0f;
	AttackSpeed = 30;
	PlayerDownSpeed = 0.0f;
	IsJumpFlag = false;

	img = LoadDivGraph("saiba-rennbann2.png", 88, 11, 8, 64, 64, anime);
	anime[88];
	ImgIndex = 0;
	count = 0;
	AnimNum = 0;

	ActionFlag = false;
	ActionCount = 0;
	radian = 0;
	pad = 0;
	InputX = 0;
	InputY = 0;
	InputFlag = 0;

	IsActive = true;
}

void Player::Update()
{
	if (!IsActive) return;
	if (ActionCount == 0)
	{
		Move();
	}

	//パッド入力の更新
	pad = GetJoypadInputState(DX_INPUT_PAD1);
}

void Player::Move()
{
	//移動量の生成
	Vector2 velocity;

	velocity = Vector2(0, 0);

	//左移動
	if ((pad & PAD_INPUT_LEFT))
	{
		velocity.x -= MoveSpeed;
		AnimNum = 3;
	}
	//右移動
	else if ((pad & PAD_INPUT_RIGHT))
	{
		velocity.x += MoveSpeed;
		AnimNum = 2;
	}
	else if (IsJumpFlag == false)
	{
		if (AnimNum == 3 || AnimNum == 5 || AnimNum == 7)
			AnimNum = 1;
		if (AnimNum == 2 || AnimNum == 4 || AnimNum == 6)
			AnimNum = 0;
	}


	// 着地しているかつスペースが押されたとき
	if (IsJumpFlag == false)
	{
		if ((pad & PAD_INPUT_B))
		{
			PlaySoundFile("", DX_PLAYTYPE_BACK);

			PlayerDownSpeed -= JumpForce;
			IsJumpFlag = true;
			if (AnimNum == 0 || AnimNum == 2 || AnimNum == 6)
				AnimNum = 4;
			count = 0;

			if (AnimNum == 1 || AnimNum == 3 || AnimNum == 7)
				AnimNum = 5;
		}
	}

	// 落下処理;
	PlayerDownSpeed += Gravity;

	// 落下速度を移動量に加える
	velocity.y = PlayerDownSpeed;

	//移動
	CheckMapMove(_position, &PlayerDownSpeed, velocity, _scale, &IsJumpFlag);
}


//アクション実行(PlayerActionTimeのアクションフラグ)
void Player::Action(bool IsActionFlag)
{
	if (!IsActive) return;
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
			if ((pad & PAD_INPUT_A))
			{
				//前フレームで押していなければ
				if (InputFlag == 0)
				{
					PlaySoundFile("", DX_PLAYTYPE_BACK);
					ActionCount = 1;
					radian = 0;
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

			radian = atan2((float)InputY /*- _position.y*/, (float)InputX /*- _position.x*/);

			if (pad & PAD_INPUT_A)
			{
				//前フレームで押していなければ
				if (InputFlag == 0)
				{
					PlaySoundFile("", DX_PLAYTYPE_BACK);
					ActionCount = 0;
				}
				//前フレームでボタンが押されたかをtrueにする
				InputFlag = 1;
			}
			else if (pad & PAD_INPUT_B)
			{
				//前フレームで押していなければ
				if (InputFlag == 0)
				{
					PlaySoundFile("", DX_PLAYTYPE_BACK);
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
			velocity.x += AttackSpeed * cos(radian);
			velocity.y += AttackSpeed * sin(radian);

			StartJoypadVibration(DX_INPUT_PAD1, 500, 1);
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
	if (!IsActive) return;

	//表示する画像の番号を変更
	ImgIndex = count % 121;
	ImgIndex /= 11;//中に6が入るように設定する
    //アニメーション描画
	DrawGraph(_position.x - _scale.x * 0.5f, _position.y - _scale.y * 0.5f, anime[ImgIndex + (11 * AnimNum)], true);

	if (ActionCount != 1)
	{
		//カウントを増やす
		++count;
		++count;
	}
	if (ActionCount == 2)
	{
		//カウントを増やす
		++count;
		++count;
		++count;
		++count;
		++count;
		++count;
		++count;
		++count;
		++count;
		++count;
		++count;
		++count;
		if (AnimNum != 6)
		{
			count = 0;
		}
		else if (count >= 11)
		{
			count == 12;
		}
		if (AnimNum == 0 || AnimNum == 2 || AnimNum == 4)
			AnimNum = 6;
		if (AnimNum == 1 || AnimNum == 3 || AnimNum == 5)
			AnimNum = 7;
	}
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
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
		*PDownS = 0.0f;
	}

	// 右下がブロックの上当たっていたら落下を止める
	if (_map.MapHitCheck(_position.x + hsize.x, _position.y + hsize.y, &Dummy, &velocity.y) == 3)
	{
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
		*PDownS = 0.0f;
	}

	// 左上がブロックの下に当たっていたら落下させる
	if (_map.MapHitCheck(_position.x - hsize.x, _position.y - hsize.y, &Dummy, &velocity.y) == 4)
	{
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
		*PDownS = 1.0f;
	}

	// 右下がブロックの下に当たっていたら落下させる
	if (_map.MapHitCheck(_position.x + hsize.x, _position.y - hsize.y, &Dummy, &velocity.y) == 4)
	{
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
		*PDownS = 1.0f;
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

void Player::SetActive(bool value)
{
	IsActive = value;
}


