#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player
{
public:
	Player();
	~Player();
	void Move();
	void Draw();
	void Hit(int hit);
	float ReturnPosX();
	float ReturnPosY();
	float ReturnGra();
	//CheckMapMove(&position.x, &position.y, &PlayerDownSpeed, MoveX, MoveY, scale, &IsJumpFlag);
private:
	float Gravity;// キャラに掛かる重力加速度
	float JumpForce;// キャラのジャンプ力
	float Speed; // キャラの移動スピード
	float scale;// プレイヤーのサイズ
	//Vector2 position; //プレイヤーの座標
	float PlayerDownSpeed;//プレイヤーの落下速度
	bool IsJumpFlag;//ジャンプしたかどうか?

	int anime[6];//プレイヤーの画像枚数配列
	int ImgIndex;//描画する画像の番号
	int count;//カウント
	float MoveX;
	float MoveY;
};


#endif // !_PLAYER_H_
