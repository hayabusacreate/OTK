#include "Renderer.h"
#include "DxLib.h"

#define PI    3.1415926535897932384626433832795f

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw(const char* failname, float x, float y)//画像描画(左上始点)
{
	//画像の読み込み
	int GHandle = LoadGraph(failname);

	// 読みこんだグラフィックを画面に描画
	DrawGraph(x, y, GHandle, TRUE);

	// 読み込んだ画像のグラフィックハンドルを削除
	DeleteGraph(GHandle);
}

void Renderer::Draw(const char * failname, float x, float y, float xx, float yy)//画像描画(画像のサイズ変更)
{
	//画像の読み込み
	int GHandle = LoadGraph(failname);

	// 読みこんだグラフィックを画面に描画
	DrawExtendGraph(x, y, xx, yy, GHandle, TRUE);

	// 読み込んだ画像のグラフィックハンドルを削除
	DeleteGraph(GHandle);
}

//flag trueなら反転 falseならそのまま
void Renderer::Rotate(const char * failname, float x, float y, double angle, int flag)//画像回転
{
	//画像の読み込み
	int GHandle = LoadGraph(failname);
	double ang = PI / 180 * angle;
	// 読みこんだグラフィックを回転描画
	DrawRotaGraph(x, y, 1.0f, ang, GHandle, TRUE, flag);

	// 読み込んだ画像のグラフィックハンドルを削除
	DeleteGraph(GHandle);
}

void Renderer::Rotate(const char * failname, float x, float y, float cx, float cy, float angle, int flag)
{
	//画像の読み込み
	int GHandle = LoadGraph(failname);
	double ang = PI / 180 * angle;
	// 読みこんだグラフィックを回転描画
	DrawRotaGraph2(x, y, cx, cy, 1.0f, ang, GHandle, TRUE, flag);

	// 読み込んだ画像のグラフィックハンドルを削除
	DeleteGraph(GHandle);
}
