#include "DxLib.h"
#include "SceneManager.h"
#include "Effect.h"
#include "Screen.h"

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//	Windowモードの設定
	ChangeWindowMode(TRUE);
	//Windowタイトルを設定する
	SetMainWindowText("タイトル");
	//画面サイズ決定
	SetGraphMode(Screen::WindowWidth, Screen::WindowHeight, 16);

	// ＤＸライブラリの初期化
	if (DxLib_Init() == -1) return -1;

	// 描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// 垂直同期信号を待たない
	SetWaitVSyncFlag(FALSE);

	// ６０ＦＰＳ固定用、時間保存用変数を現在のカウント値にセット
	int FrameStartTime = GetNowCount();

	SceneManager scenemanager;
	scenemanager.Initialize();

	

	// メインループ開始、ＥＳＣキーで外に出る
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面のクリア
		ClearDrawScreen();

		// １/６０秒立つまで待つ
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}

		// 現在のカウント値を保存
		FrameStartTime = GetNowCount();

		scenemanager.Update();
		scenemanager.Draw();
		
		//反転
		ScreenFlip();
	}

	// ＤＸライブラリの後始末
	DxLib_End();

	// 終了
	return 0;
}



