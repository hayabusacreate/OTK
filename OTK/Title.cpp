#include "Title.h"
#include "DxLib.h"

Title::Title(ISceneChanger* changer) : BaseScene(changer)
{

}

//初期化
void Title::Initialize()
{
	mImageHandle = LoadGraph("title.png");    //画像のロード
	InputMonitor = 0;
	sound.PlayBGM("Title.mp3");

}

void Title::Finalize()
{
	BaseScene::Finalize();
	sound.StopBGM("Title.mp3");
}

//更新
void Title::Update()
{

	pad = GetJoypadInputState(DX_INPUT_PAD1);

	if ((pad & PAD_INPUT_B))
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
}