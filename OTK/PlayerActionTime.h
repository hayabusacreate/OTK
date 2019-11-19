#include "Vector2.h"
#include "Renderer.h"
#include <DxLib.h>

//プレイヤーのストップゲージクラス
class PlayerActionTime
{
public:
	//コンストラクタ
	PlayerActionTime();

	//デストラクタ
	~PlayerActionTime();

	//初期化
	void Initialize();

	//更新(プレイヤーのアクションフラグ)
	void Update(bool ActionFlag, int EnemyDeadScore);

	//入力
	void InputKey();

	//描画(表示位置(左上))
	void Draw(float x, float y);

	//アクション状態を取得
	bool GetActionFlag();

	//現在のゲージを取得
	int GetExpansionX();

private:
	int img;         //画像名
	int sizex, sizey;//画像サイズ
	float expansionX;  //拡大率
	float MaxexpansionX;//最大拡大率
	float MinexpansionX;//最小拡大率
	bool IsActionFlag;//アクションができる状態か？

	int key[256];
	int pad;
};
