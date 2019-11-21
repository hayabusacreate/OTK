#define _PLAYER_H_
#include "Vector2.h"
#include <DxLib.h>
#include "Map.h"

//プレイヤークラス
class Player
{
public:
	//コンストラクタ(初期位置：マップ)
	Player(Vector2 pos, Map map);

	//デストラクタ
	~Player();

	//初期化
	void Initialize();

	//更新
	void Update();

	//入力
	void InputKey_PAD();

	//移動
	void Move();

	//アクション実行(PlayerActionTimeのアクションフラグ:敵の位置:敵の大きさ)
	void Action(bool ActionFlag);


	//描画
	void Draw();

	//当たり判定(位置：落下速度：移動量：サイズ：ジャンプフラグ)
	int CheckMapMove(Vector2 pos, float * PDownS, Vector2 velocity, Vector2 scale, bool *JumpFlag);

	//位置を取得
	Vector2 GetPosition();

	//大きさを取得
	Vector2 GetScale();

	//アクションフラグ取得
	bool GetActionFlag();

	void SetActive(bool value);

private:
	Vector2 _position;    //プレイヤーの座標
	Vector2 _scale;       // プレイヤーのサイズ
	float Gravity;        // キャラに掛かる重力加速度
	float JumpForce;      // キャラのジャンプ力
	float MoveSpeed;      // キャラの移動スピード
	float AttackSpeed;
	float PlayerDownSpeed;//プレイヤーの落下速度
	bool IsJumpFlag;      //ジャンプしたかどうか?
	int img;


	int anime[88];         //プレイヤーの画像枚数配列
	int ImgIndex;         //描画する画像の番号
	int AnimNum;          //アニメーション番号
	int count;            //カウント
	Map _map;             //マップ情報


	bool ActionFlag;      //アクション実行
	int ActionCount;      //0:通常状態,1:索敵状態,2:角度指定&発射待機状態,3:移動状態
	float radian;         //距離計算

	int key[256];         // 0:入力されていない 1:入力された瞬間 2:入力されている
	int pad;          // 0:入力されていない 1:入力された瞬間 2:入力されている

	int InputX, InputY;

	int InputFlag; //１フレ前にボタンがおされたら

	bool IsActive;//true:死んだ false:生きている
};
