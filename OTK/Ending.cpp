#include "Ending.h"
#include <DxLib.h>

Ending::Ending(ISceneChanger* changer) : BaseScene(changer)
{
}

void Ending::Initialize()
{
	//mImageHandle = LoadGraph("clear.png");
	//SoundHandle = LoadSoundMem("GameClear.mp3");
	//PlaySoundMem(SoundHandle, DX_PLAYTYPE_LOOP);
	sound.PlayBGM("GameClear.mp3");
	InputMonitor = 0;
}

void Ending::Finalize()
{
	BaseScene::Finalize();
	//StopSoundMem(SoundHandle);
	sound.StopBGM("GameClear.mp3");
}

void Ending::Update()
{
	pad = GetJoypadInputState(DX_INPUT_PAD1);

	if ((pad & PAD_INPUT_B) || (CheckHitKey(KEY_INPUT_W) == 1))
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

void Ending::Draw()
{
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(0, 0, "エンディング画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Bボタンを押すとタイトルに進みます。", GetColor(255, 255, 255));
	/*DrawGraph(0, 0, mImageHandle, TRUE);*/
}
