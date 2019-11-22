#include "Title.h"
#include "DxLib.h"

Title::Title(ISceneChanger* changer) : BaseScene(changer)
{

}

//初期化
void Title::Initialize()
{
	mImageHandle = LoadGraph("images/Scene_Config.png");    //画像のロード
	InputMonitor = 0;
	PlaySoundFile("pianoTitle.mp3", DX_PLAYTYPE_LOOP);
}

//更新
void Title::Update()
{
	pad = GetJoypadInputState(DX_INPUT_PAD1);

	if (pad & PAD_INPUT_B)
	{
		if (InputMonitor == 0)
		{
			PlaySoundFile("", DX_PLAYTYPE_BACK);
			mSceneChanger->ChangeScene(eScene_GamePlay);//シーンをメニューに変更
		}
		InputMonitor = 1;
	}
	else
	{
		InputMonitor = 0;
	}
}

//描画
void Title::Draw()
{
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(0, 0, "タイトル画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Bボタンを押すとゲーム画面に戻ります。", GetColor(255, 255, 255));
}