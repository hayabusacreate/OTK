#include "GameOver.h"
#include <DxLib.h>

GameOver::GameOver(ISceneChanger* changer) : BaseScene(changer)
{
}

void GameOver::Initialize()
{
	mImageHandle = LoadGraph("over.png");
	//SoundHandle = LoadSoundMem("GameOver.mp3");
	//PlaySoundMem(SoundHandle, DX_PLAYTYPE_LOOP);
	sound.PlayBGM("GameOver.mp3");
	InputMonitor = 0;
}

void GameOver::Finalize()
{
	BaseScene::Finalize();
	//StopSoundMem(SoundHandle);
	sound.StopBGM("GameOver.mp3");
}

void GameOver::Update()
{
	pad = GetJoypadInputState(DX_INPUT_PAD1);

	if (pad & PAD_INPUT_B)
	{
		if (InputMonitor == 0)
		{
			mSceneChanger->ChangeScene(eScene_Title);//シーンをメニューに変更
		}
		InputMonitor = 1;
	}
	else
	{
		InputMonitor = 0;
	}
}

void GameOver::Draw()
{
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(0, 0, "ゲームオーバー画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Bボタンを押すとタイトルに進みます。", GetColor(255, 255, 255));
}

