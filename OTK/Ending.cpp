#include "Ending.h"
#include <DxLib.h>

Ending::Ending(ISceneChanger* changer) : BaseScene(changer)
{
}

void Ending::Initialize()
{
	PlaySoundFile("", DX_PLAYTYPE_LOOP);
	InputMonitor = 0;
}

void Ending::Update()
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

void Ending::Draw()
{
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(0, 0, "エンディング画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Bボタンを押すとタイトルに進みます。", GetColor(255, 255, 255));
	//DrawString(0, 40, "Sキーを押すとにゲーム画面に進みます。", GetColor(255, 255, 255));
}
