#include "GameOver.h"
#include <DxLib.h>

GameOver::GameOver(ISceneChanger* changer) : BaseScene(changer)
{
}

void GameOver::Initialize()
{
	mImageHandle = LoadGraph("over.png");
	sound.PlayBGM("GameOver.mp3");
	InputMonitor = 0;
}

void GameOver::Finalize()
{
	BaseScene::Finalize();
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
}

