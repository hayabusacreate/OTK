#include "DxLib.h"
#include "Vector2.h"
#include "Renderer.h"

#define SCREEN_WIDTH     (640)                          // 画面横幅
#define SCREEN_HEIGHT    (480)                          // 画面縦幅
#define CHIP_SIZE        (32)                           // 一つのチップのサイズ
#define MAP_WIDTH        (SCREEN_WIDTH / CHIP_SIZE)     // マップの横幅
#define MAP_HEIGHT       (SCREEN_HEIGHT / CHIP_SIZE)    // マップの縦幅

//プレイヤークラス?
typedef struct  Player
{
	float Gravity;         // キャラに掛かる重力加速度
	float JumpForce;	   // キャラのジャンプ力
	float Speed;		   // キャラの移動スピード
	float scale;	        // プレイヤーのサイズ
	Vector2 position;       //プレイヤーの座標
	float PlayerDownSpeed; //プレイヤーの落下速度
	bool IsJumpFlag;       //ジャンプしたかどうか?


	int anime[6] = { 0 };    //プレイヤーの画像枚数配列
	int ImgIndex;          //描画する画像の番号
	int count;             //カウント

	//初期化
	Player()
		:Gravity(0.3f),
		JumpForce(9.0f),
		Speed(5.0f),
		scale(30),
		position(320.0f, 240.0f),
		PlayerDownSpeed(0.0f),
		IsJumpFlag(false),
		ImgIndex(0),
		count(0)
	{

	}

	//プレイヤーの移動
	void PlayerMove();
	//プレイヤーの描画
	void PlayerRenderer();
};

//敵生成テスト
typedef struct Enemy
{
	float Gravity;
	float JumpForce;
	float Speed;
	float scale;
	Vector2 position;
	float EnemyDownSpeed;
	bool IsJumpFlag;

	bool IsHitPlayer;

	//初期化
	Enemy()
		:Gravity(0.3f),
		JumpForce(9.0f),
		Speed(5.0f),
		scale(30),
		position(320.0f, 240.0f),
		EnemyDownSpeed(0.0f),
		IsJumpFlag(false),


		IsHitPlayer(false)
	{

	}

	//プレイヤーの移動
	void EnemyMove();
	//プレイヤーの描画
	void EnemyRenderer();
};

//Inputクラス?
typedef struct  InputState
{
	int input, key;      // 入力状態

	// 入力状態の初期化
	InputState()
		:input(0), key(0)
	{

	}

	void InputUpdate();
};

//マップクラス？
typedef struct  Map
{
	int chip[3];

	// マップデータ
	char MapData[15][22] =
	{
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,1,
		1,0,0,2,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,1,
		1,0,0,2,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0,0,1,
		1,0,0,2,2, 2,2,0,0,0, 0,0,0,0,0, 0,0,2,0,0,0,1,

		1,0,0,0,0, 0,0,0,2,2, 0,0,0,0,0, 0,0,2,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,2,2,0, 0,0,2,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,1,
		1,0,0,0,0, 0,0,2,2,0, 0,0,0,0,0, 2,0,0,0,0,0,1,

		1,0,0,0,0, 2,2,2,2,2, 0,0,0,0,2, 2,0,0,0,0,0,1,
		1,0,0,0,0, 2,2,2,2,2, 0,0,0,2,2, 2,0,0,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,2,2, 2,0,0,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,1,
		1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,1,1,
	};

	// マップチップの値を取得する関数
	int GetMapChip(float X, float Y);

	//マップの描画
	void MapRenderer();

	// マップとの当たり判定( 戻り値 0:当たらなかった  1:左辺に当たった  2:右辺に当たった
	//                                                3:上辺に当たった  4:下辺に当たった
	// 注意：MoveX と MoveY 、どっちか片方が０じゃないとまともに動作しません(爆)
	int MapHitCheck(float X, float Y, float *MoveX, float *MoveY);
};


//プレイヤー生成
Player player;
//エネミー生成
Enemy enemy;
//Input生成
InputState Input;
//マップ生成
Map map;
//Renderer生成
Renderer renderer;

bool IsActionFlag = false;

int FrameStartTime;        // ６０ＦＰＳ固定用、時間保存用変数

	// キャラクタをマップとの当たり判定を考慮しながら移動する関数
int CheckMapMove(float *X, float *Y, float *DownSP,
	float MoveX, float MoveY, float Size, bool *JumpFlag);

// アクションサンプルプログラムメイン関数
int ActionMain(void);


// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	// ＤＸライブラリの初期化
	if (DxLib_Init() == -1) return -1;

	// アクションゲームのメイン関数を呼ぶ
	ActionMain();

	// ＤＸライブラリの後始末
	DxLib_End();

	// 終了
	return 0;
}

// アクションサンプルプログラムメイン
int ActionMain(void)
{
	// 描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// 垂直同期信号を待たない
	SetWaitVSyncFlag(FALSE);

	// ６０ＦＰＳ固定用、時間保存用変数を現在のカウント値にセット
	FrameStartTime = GetNowCount();

	// メインループ開始、ＥＳＣキーで外に出る
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面のクリア
		ClearDrawScreen();

		// １/６０秒立つまで待つ
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}

		// 現在のカウント値を保存
		FrameStartTime = GetNowCount();


		Input.InputUpdate();
		map.MapRenderer();

		enemy.EnemyMove();
		enemy.EnemyRenderer();
		player.PlayerMove();
		player.PlayerRenderer();


		//Zキーが押されたら当たり判定を表示
		if ((Input.input & PAD_INPUT_1) != 0)
		{
			IsActionFlag = true;
		}
		else
		{
			IsActionFlag = false;
		}


		//矩形の当たり判定
		auto dx = abs((player.position.x + player.scale / 2.f) - (enemy.position.x + enemy.scale / 2));
		auto dy = abs((player.position.y + player.scale / 2.f) - (enemy.position.y + enemy.scale / 2));

		if (dx < (player.scale + enemy.scale) / 2 && dy < (player.scale + enemy.scale) / 2)
		{
			DrawString(0, 0, "当たった!", GetColor(255, 0, 0));
		}

		//枠内に敵がいたとき
		if (enemy.IsHitPlayer)
		{
			//敵の位置を取得
			//            b
			Vector2 epos(enemy.position.x, enemy.position.y);
			//            a
			Vector2 ppos(player.position.x, player.position.y);

			//お互いの中心を求める
			auto x = abs((ppos.x + player.scale / 2.f) - (epos.x + enemy.scale / 2));
			auto y = abs((ppos.y + player.scale / 2.f) - (epos.y + enemy.scale / 2));

			float test(sqrt(x * x + y * y));

			ppos = epos;
		}


		// 画面の更新
		ScreenFlip();
	}

	// 終了
	return 0;
}

// プレイヤーの移動処理
void Player::PlayerMove()
{
	float MoveX, MoveY;

	// 移動量の初期化
	MoveX = 0.0f;
	MoveY = 0.0f;

	//左移動
	if ((Input.input & PAD_INPUT_LEFT) != 0)
	{
		MoveX -= player.Speed;
	}

	//右移動
	if ((Input.input & PAD_INPUT_RIGHT) != 0)
	{
		MoveX += player.Speed;
	}

	// 着地しているかつスペースが押されたとき
	if (player.IsJumpFlag == false && (Input.key & PAD_INPUT_10) != 0)
	{
		player.PlayerDownSpeed -= player.JumpForce;
		player.IsJumpFlag = true;
	}

	// 落下処理;
	player.PlayerDownSpeed += player.Gravity;

	// 落下速度を移動量に加える
	MoveY = player.PlayerDownSpeed;

	// 移動量に基づいてキャラクタの座標を移動
	CheckMapMove(&player.position.x, &player.position.y, &player.PlayerDownSpeed, MoveX, MoveY, player.scale, &player.IsJumpFlag);
}

//プレイヤーの描画
void Player::PlayerRenderer()
{
	// キャラクタの描画
	//DrawBox((int)(player.position.x - player.scale * 0.5F), (int)(player.position.y - player.scale * 0.5F),
	//	(int)(player.position.x + player.scale * 0.5F) + 1, (int)(player.position.y + player.scale * 0.5F) + 1,
	//	GetColor(255, 0, 0), TRUE);


	Vector2 RectPos(player.position.x - player.scale * 0.5f, player.position.y - player.scale * 0.5f);
	//renderer.Draw("player.png", RectPos);//通常描画

	//画像の読み込み
	LoadDivGraph("puddle.png", 6, 6, 1, 32, 32, player.anime);

	//表示する画像の番号を変更
	player.ImgIndex = player.count % 36;
	player.ImgIndex /= 6;//中に6が入るように設定する

	//アニメーション描画
	DrawGraph(player.position.x - player.scale * 0.5f, player.position.y - player.scale * 0.5f, player.anime[player.ImgIndex], true);
	//カウントを増やす
	++player.count;

	//アクションフラグがtrueの時
	if (IsActionFlag)
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
	}
}

// 入力状態を更新
void InputState::InputUpdate()
{
	int i;

	// パッド１とキーボードから入力を得る
	i = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// エッジを取った入力をセット
	Input.key = i & Input.input;

	// 入力状態の保存
	Input.input = i;
}

// マップチップの値を取得する関数
int Map::GetMapChip(float X, float Y)
{
	int x, y;

	// 整数値へ変換
	x = (int)X / CHIP_SIZE;
	y = (int)Y / CHIP_SIZE;

	// 指定の座標に該当するマップの情報を返す
	return map.MapData[y][x];
}

// マップの描画
void Map::MapRenderer()
{
	LoadDivGraph("testblock.png", 3, 3, 1, 32, 32, map.chip);

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 22; x++)
		{
			DrawGraph(x * 32, y * 32, map.chip[MapData[y][x]], FALSE);
		}
	}

	//for (int i = 0; i < MAP_HEIGHT; i++)
	//{
	//	for (int j = 0; j < MAP_WIDTH; j++)
	//	{
	//		// １は当たり判定チップを表しているので１のところだけ描画
	//		if (map.MapData[i][j] == 1)
	//		{
	//			DrawBox(j * CHIP_SIZE, i * CHIP_SIZE,
	//				j * CHIP_SIZE + CHIP_SIZE, i * CHIP_SIZE + CHIP_SIZE,
	//				GetColor(255, 255, 255), TRUE);
	//		}
	//	}
	//}
}

// キャラクタをマップとの当たり判定を考慮しながら移動する
int CheckMapMove(float * X, float * Y, float * DownSP, float MoveX, float MoveY, float Size, bool * JumpFlag)
{
	float Dummy = 0.0f;
	float hsize;

	// キャラクタの左上、右上、左下、右下部分に当たり判定のある
	// マップに衝突しているか調べ、衝突していたら補正する
	// 半分のサイズを算出
	hsize = Size * 0.5f;

	// 先ず上下移動成分だけでチェック
	{
		// 左下のチェック、もしブロックの上辺に着いていたら落下を止める
		if (map.MapHitCheck(*X - hsize, *Y + hsize, &Dummy, &MoveY) == 3)
		{
			*DownSP = 0.0F;
		}

		// 右下のチェック、もしブロックの上辺に着いていたら落下を止める
		if (map.MapHitCheck(*X + hsize, *Y + hsize, &Dummy, &MoveY) == 3)
		{
			*DownSP = 0.0F;
		}

		// 左上のチェック、もしブロックの下辺に当たっていたら落下させる
		if (map.MapHitCheck(*X - hsize, *Y - hsize, &Dummy, &MoveY) == 4)
		{
			*DownSP *= -1.0F;
		}

		// 右上のチェック、もしブロックの下辺に当たっていたら落下させる
		if (map.MapHitCheck(*X + hsize, *Y - hsize, &Dummy, &MoveY) == 4)
		{
			*DownSP *= -1.0F;
		}

		// 上下移動成分を加算
		*Y += MoveY;
	}

	// 後に左右移動成分だけでチェック
	{
		// 左下のチェック
		map.MapHitCheck(*X - hsize, *Y + hsize, &MoveX, &Dummy);

		// 右下のチェック
		map.MapHitCheck(*X + hsize, *Y + hsize, &MoveX, &Dummy);

		// 左上のチェック
		map.MapHitCheck(*X - hsize, *Y - hsize, &MoveX, &Dummy);

		// 右上のチェック
		map.MapHitCheck(*X + hsize, *Y - hsize, &MoveX, &Dummy);

		// 左右移動成分を加算
		*X += MoveX;
	}

	// 接地判定
	{
		// キャラクタの左下と右下の1ピクセル下にブロックがあるか?
		if (map.GetMapChip(*X - hsize, *Y + hsize + 1.0f) == 0 &&
			map.GetMapChip(*X + hsize, *Y + hsize + 1.0f) == 0)
		{
			//無かったらジャンプ中にする
			*JumpFlag = true;
		}
		else
		{
			// あったらfalse
			*JumpFlag = false;
		}
	}

	// 終了
	return 0;
}

// マップとの当たり判定( 戻り値 0:当たらなかった  1:左辺に当たった  2:右辺に当たった
//                                                3:上辺に当たった  4:下辺に当たった
int Map::MapHitCheck(float X, float Y, float * MoveX, float * MoveY)
{
	float afX, afY;

	// 移動量を足す
	afX = X + *MoveX;
	afY = Y + *MoveY;

	//ブロックにぶつかっていたら
	if (map.GetMapChip(afX, afY) == 1 ||
		map.GetMapChip(afX, afY) == 2)
	{
		float blx, bty, brx, bby;

		//ぶつかった時の座標を代入
		blx = (float)((int)afX / CHIP_SIZE) * CHIP_SIZE;        // 左辺の X 座標
		brx = (float)((int)afX / CHIP_SIZE + 1) * CHIP_SIZE;    // 右辺の X 座標

		bty = (float)((int)afY / CHIP_SIZE) * CHIP_SIZE;        // 上辺の Y 座標
		bby = (float)((int)afY / CHIP_SIZE + 1) * CHIP_SIZE;    // 下辺の Y 座標

		// 左辺に当たっていた場合
		if (*MoveX > 0.0f)
		{
			// 移動量を補正する
			*MoveX = blx - X - 1.0f;

			// 左辺に当たったと返す
			return 1;
		}

		// 右辺に当たっていた場合
		if (*MoveX < 0.0f)
		{
			// 移動量を補正する
			*MoveX = brx - X + 1.0f;

			// 右辺に当たったと返す
			return 2;
		}

		// 上辺に当たっていた場合
		if (*MoveY > 0.0f)
		{
			// 移動量を補正する
			*MoveY = bty - Y - 1.0f;

			// 上辺に当たったと返す
			return 3;
		}

		// 下辺に当たっていた場合
		if (*MoveY < 0.0f)
		{
			// 移動量を補正する
			*MoveY = bby - Y + 1.0f;

			// 下辺に当たったと返す
			return 4;
		}

		//例外設定
		return 4;
	}

	// どこにも当たらなかったと返す
	return 0;
}

void Enemy::EnemyMove()
{
	float MoveX, MoveY;

	// 移動量の初期化
	MoveX = 0.0f;
	MoveY = 0.0f;

	// 落下処理;
	enemy.EnemyDownSpeed += enemy.Gravity;

	// 落下速度を移動量に加える
	MoveY = enemy.EnemyDownSpeed;

	// 移動量に基づいてキャラクタの座標を移動
	CheckMapMove(&enemy.position.x, &enemy.position.y, &enemy.EnemyDownSpeed, MoveX, MoveY, enemy.scale, &enemy.IsJumpFlag);
}

void Enemy::EnemyRenderer()
{
	//int red;
	//if (enemy.IsHitPlayer)
	//{
	//	red = 255;
	//}
	//else
	//{
	//	red = 0;
	//}

	//// キャラクタの描画
	//DrawBox((int)(enemy.position.x - enemy.scale * 0.5F), (int)(enemy.position.y - enemy.scale * 0.5F),
	//	(int)(enemy.position.x + enemy.scale * 0.5F) + 1, (int)(enemy.position.y + enemy.scale * 0.5F) + 1,
	//	GetColor(red, 0, 255), TRUE);

	Vector2 RectPos(enemy.position.x - enemy.scale * 0.5f, enemy.position.y - enemy.scale * 0.5f);
	renderer.Draw("block.png", RectPos);
}
