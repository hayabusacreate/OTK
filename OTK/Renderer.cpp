#include "Renderer.h"
#include "DxLib.h"

#define PI    3.1415926535897932384626433832795f

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw(const char* failname, Vector2 position)//画像描画(左上始点)
{
	//画像の読み込み
	int GHandle = LoadGraph(failname);

	// 読みこんだグラフィックを画面に描画
	DrawGraph(position.x, position.y, GHandle, TRUE);

	// 読み込んだ画像のグラフィックハンドルを削除
	DeleteGraph(GHandle);
}

void Renderer::Draw(const char * failname, Vector2 position, Vector2 scale)//画像描画(画像のサイズ変更)
{
	//画像の読み込み
	int GHandle = LoadGraph(failname);

	// 読みこんだグラフィックを画面に描画
	DrawExtendGraph(position.x, position.y, scale.x, scale.y, GHandle, TRUE);

	// 読み込んだ画像のグラフィックハンドルを削除
	DeleteGraph(GHandle);
}

//flag trueなら反転 falseならそのまま
void Renderer::Rotate(const char * failname, Vector2 position, double angle, int flag)//画像回転
{
	//画像の読み込み
	int GHandle = LoadGraph(failname);
	double ang = PI / 180 * angle;
	// 読みこんだグラフィックを回転描画
	DrawRotaGraph(position.x, position.y, 1.0f, ang, GHandle, TRUE, flag);

	// 読み込んだ画像のグラフィックハンドルを削除
	DeleteGraph(GHandle);
}

void Renderer::Rotate(const char * failname, Vector2 position, Vector2 scale, float angle, int flag)
{
	//画像の読み込み
	int GHandle = LoadGraph(failname);
	double ang = PI / 180 * angle;
	// 読みこんだグラフィックを回転描画
	DrawRotaGraph2(position.x, position.y, scale.x, scale.y, 1.0f, ang, GHandle, TRUE, flag);

	// 読み込んだ画像のグラフィックハンドルを削除
	DeleteGraph(GHandle);
}
