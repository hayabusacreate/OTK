#include "DxLib.h"
#include "Renderer.h"
#include<string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int CmdShow)
{
	//Windowモードで起動する
	ChangeWindowMode(true);

	//画面サイズを320×320に設定
	SetGraphMode(1920, 1080, 16);

	if (DxLib_Init() == -1) return -1;

	//描画先を指定
	SetDrawScreen(DX_SCREEN_BACK);

	//画面背景の色を設定する
	SetBackgroundColor(255, 255, 255);

	//初期化
	Renderer renderer;
	
	int i = 0;
	int x = 0;
	//ここまで

	//更新
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//画面をクリア
		ClearDrawScreen();
		//これより下↓

		//これより↑
		//バックバッファの内容を画面に表示
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}