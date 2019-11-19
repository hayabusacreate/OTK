#include "Ending.h"
#include <DxLib.h>

Ending::Ending(ISceneChanger* changer) : BaseScene(changer) {
}

void Ending::Initialize()
{
}

void Ending::Update()
{
	if (CheckHitKey(KEY_INPUT_W) != 0)//W
	{
		mSceneChanger->ChangeScene(eScene_Title);
	}
	//if (CheckHitKey(KEY_INPUT_5))//S
	//{
	//	mSceneChanger->ChangeScene(eScene_GamePlay);
	//}
}

void Ending::Draw()
{
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(0, 0, "エンディング画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Wキーを押すとタイトルに進みます。", GetColor(255, 255, 255));
	DrawString(0, 40, "Sキーを押すとにゲーム画面に進みます。", GetColor(255, 255, 255));
}
