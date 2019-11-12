#include "DxLib.h"
#include "GamePlay.h"

#define SCREEN_WIDTH     (640)                          // 画面横幅
#define SCREEN_HEIGHT    (480)                          // 画面縦幅
#define CHIP_SIZE        (32)                           // 一つのチップのサイズ
#define MAP_WIDTH        (SCREEN_WIDTH / CHIP_SIZE)     // マップの横幅
#define MAP_HEIGHT       (SCREEN_HEIGHT / CHIP_SIZE)    // マップの縦幅




// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	// ＤＸライブラリの初期化
	if (DxLib_Init() == -1) return -1;

	// 描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// 垂直同期信号を待たない
	SetWaitVSyncFlag(FALSE);

	// ６０ＦＰＳ固定用、時間保存用変数を現在のカウント値にセット
	int FrameStartTime = GetNowCount();

	GamePlay game;
	game.Init();

	// メインループ開始、ＥＳＣキーで外に出る
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面のクリア
		ClearDrawScreen();

		// １/６０秒立つまで待つ
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}

		// 現在のカウント値を保存
		FrameStartTime = GetNowCount();

		game.Update();
		game.Draw();
		
		ScreenFlip();
	}

	// ＤＸライブラリの後始末
	DxLib_End();

	// 終了
	return 0;
}



