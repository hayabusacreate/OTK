#include "Enemy.h"
#include "Player.h"

//コンストラクタ
//位置:マップ
Enemy::Enemy(Vector2 pos, Map map)
	:SetFastPosition(pos.x * 64, pos.y * 64), _scale(Vector2(60, 60))
{
	this->_map = map;
	Player player(Vector2(11, 10), _map);
}

//デストラクタ
Enemy::~Enemy()
{
	DeleteGraph(img);
}

//初期化
void Enemy::Initialize()
{
	_position = SetFastPosition;
	MoveSpeed = 2.0f;
	radian = 0;
	anime[6] = { 0 };
	ImgIndex = 0;
	count = 0;
	img = LoadDivGraph("puddle.png", 6, 6, 1, 32, 32, anime);
	MoveCount = 0;
	Score = 0;
	IsActive = true;
	isHitPlayer = false;
}

//移動
void Enemy::Move(Vector2 PlayerPos, Vector2 PlayerSca, bool IsAction)
{
	if (!IsActive) return;
	if (IsAction) return;
	//移動量の初期化
	Vector2 velocity;
	velocity = Vector2(0, 0);

	//プレイヤーと自分の当たり判定
	auto dx = abs((PlayerPos.x + PlayerSca.x * 0.5f) - (_position.x + _scale.x * 0.5f));
	auto dy = abs((PlayerPos.y + PlayerSca.y * 0.5f) - (_position.y + _scale.y * 0.5f));

	//索敵範囲(*2)に当たっているか?
	if (dx < (PlayerSca.x + _scale.x * 2) && dy < (PlayerSca.y + _scale.y * 2))
	{
		//移動カウント更新
		MoveCount = 1;
	}
	else
	{
		//当たっていなければ戻す
		MoveCount = 0;
	}

	//当たっていたらプレイヤーの座標に移動
	if (MoveCount == 1)
	{
		radian = atan2(PlayerPos.y - _position.y, PlayerPos.x - _position.x);
		velocity.x += MoveSpeed * cos(radian);
		velocity.y += MoveSpeed * sin(radian);
	}

	//移動
	CheckMapMove(_position, velocity, _scale);
}

//プレイヤーに当たった時の処理
void Enemy::HitPlayer(Vector2 PlayerPos, Vector2 PlayerScale, bool IsAction)
{
	//敵との当たり判定
	auto dx = abs((PlayerPos.x + PlayerScale.x / 2.f) - (_position.x + _scale.x / 2));
	auto dy = abs((PlayerPos.y + PlayerScale.y / 2.f) - (_position.y + _scale.y / 2));

	if (dx < (PlayerScale.x + _scale.x) / 2 && dy < (PlayerScale.y + _scale.y) / 2)
	{
		//プレイヤーがアクション状態の
		if (IsAction)
		{
			//自分が生きていたら死亡
			if (IsActive == true)
			{
				//音楽、ゲージプラス、フラグを折る
				PlaySoundFile("", DX_PLAYTYPE_BACK);
				Score = 30;
				IsActive = false;
			}
			else
			{
				//死んでいる敵に当たってもスコアは増えない
				Score = 0;
			}
		}
		else
		{
			//アクション状態でないプレイヤーに当たったら
			if (IsActive == true)
			{
				//プレイヤーを殺すフラグを立てる
				isHitPlayer = true;
			}
		}
	}
}

//描画
void Enemy::Draw()
{
	if (!IsActive) return;
	//敵の画像描画
		//表示する画像の番号を変更
	ImgIndex = count % 36;
	ImgIndex /= 6;//中に6が入るように設定する

	//アニメーション描画
	DrawGraph(_position.x - _scale.x * 0.5f, _position.y - _scale.y * 0.5f, anime[ImgIndex], true);
	//カウントを増やす
	++count;

	//敵の索敵範囲仮で表示
	DrawBox((int)(_position.x - _scale.x * 2.0f), (int)(_position.y - _scale.y * 2.0f),
		(int)(_position.x + _scale.x * 2.0f) + 1, (int)(_position.y + _scale.y * 2.0f) + 1,
		GetColor(255, 0, 0), FALSE);

	//プレイヤーが索敵範囲内にいたら色を変える
	if (MoveCount == 1)
	{
		DrawBox((int)(_position.x - _scale.x * 2.0f), (int)(_position.y - _scale.y * 2.0f),
			(int)(_position.x + _scale.x * 2.0f) + 1, (int)(_position.y + _scale.y * 2.0f) + 1,
			GetColor(0, 255, 0), FALSE);
	}
}

//マップとの当たり判定
int Enemy::CheckMapMove(Vector2 pos, Vector2 velocity, Vector2 scale)
{
	float Dummy = 0.0f;
	Vector2 hsize;

	// キャラクタの左上、右上、左下、右下部分に当たり判定のある
	// マップに衝突しているか調べ、衝突していたら補正する
	// 半分のサイズを算出
	hsize = _scale * 0.5f;

	// 左下がブロックの上に当たったら落下を止める
	_map.MapHitCheck(_position.x - hsize.x, _position.y + hsize.y, &Dummy, &velocity.y);

	// 右下がブロックの上当たっていたら落下を止める
	_map.MapHitCheck(_position.x + hsize.x, _position.y + hsize.y, &Dummy, &velocity.y);

	// 左上がブロックの下に当たっていたら落下させる
	_map.MapHitCheck(_position.x - hsize.x, _position.y - hsize.y, &Dummy, &velocity.y);

	// 右下がブロックの下に当たっていたら落下させる
	_map.MapHitCheck(_position.x + hsize.x, _position.y - hsize.y, &Dummy, &velocity.y);

	// 上下移動成分を加算
	_position.y += velocity.y;

	{
		// 左下のチェック
		_map.MapHitCheck(_position.x - hsize.x, _position.y + hsize.y, &velocity.x, &Dummy);

		// 右下のチェック
		_map.MapHitCheck(_position.x + hsize.x, _position.y + hsize.y, &velocity.x, &Dummy);

		// 左上のチェック
		_map.MapHitCheck(_position.x - hsize.x, _position.y - hsize.y, &velocity.x, &Dummy);

		// 右上のチェック
		_map.MapHitCheck(_position.x + hsize.x, _position.y - hsize.y, &velocity.x, &Dummy);

	}
	// 左右移動成分を加算
	_position.x += velocity.x;

	return 0;
}

//位置取得
Vector2 Enemy::GetPosition()
{
	return Vector2(_position.x, _position.y);
}

//大きさ取得
Vector2 Enemy::GetScale()
{
	return Vector2(_scale.x, _scale.y);
}

//ゲージに追加するポイントを取得
int Enemy::GetScore()
{
	return Score;
}

//プレイヤーを殺すフラグを取得
bool Enemy::GetHitPlayer()
{
	return isHitPlayer;
}
