#include "Vector2.h"
#include <DxLib.h>
#include "Map.h"
#include "Renderer.h"
#include "Effect.h"
#include "CountDownTimer.h"
#include "Sound.h"

//エネミークラス
class Enemy
{
public:
	//コンストラクタ(初期位置：マップ)
	Enemy(Vector2 pos, Map map);

	//デストラクタ
	~Enemy();

	//初期化
	void Initialize();

	//移動(プレイヤーの位置：プレイヤーのサイズ)
	void Move(Vector2 PlayerPos, Vector2 PlayerScale,bool IsAction);

	//プレイヤーと敵の当たり判定(プレイヤーの位置：プレイヤーのサイズ:アクション)
	void HitPlayer(Vector2 PlayerPos, Vector2 PlayerScale, bool IsAction);

	//描画
	void Draw();

	//当たり判定
	int CheckMapMove(Vector2 pos, Vector2 velocity, Vector2 scale);

	//位置を取得
	Vector2 GetPosition();

	//大きさを取得
	Vector2 GetScale();

	//敵を倒したときにゲージを増やすときに使ったやつ
	int GetScore();

	//非アクションのプレイヤーにぶつかったか？
	bool GetHitPlayer();

private:
	Vector2 _position;    //エネミーの座標
	Vector2 _scale;       // エネミーのサイズ
	float MoveSpeed;      // キャラの移動スピード
	float radian;         //敵の移動方向を代入
	int anime[12];         //エネミーの画像枚数配列
	int ImgIndex;         //描画する画像の番号
	int count;            //カウント
	int img;              //画像名
	int MoveCount;        //移動用のカウント
	int Score;            //倒されたときのカウント
	bool IsActive;        //ture:生きている false:死んでいる
	bool isHitPlayer;     //true:プレイヤーに当たった false:プレイヤーに当たっていない
	Map _map;             //マップ情報を持っておく
	
	Vector2 SetFastPosition;//プレイヤーの初期位置格納用
	Effect effect;
	CountDownTimer timer;
	bool t;//タイマーのセットを一度だけ通す
	bool counts;

	int SoundHandle;
	Sound sound;
};