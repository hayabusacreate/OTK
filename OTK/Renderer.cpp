#include "Renderer.h"
#include "DxLib.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw(const char* failname, float x, float y)
{
	//画像の読み込み
	int GHandle = LoadGraph(failname);

	// 読みこんだグラフィックを画面に描画
	DrawGraph(x, y, GHandle, TRUE);

	// 読み込んだ画像のグラフィックハンドルを削除
	DeleteGraph(GHandle);
}
