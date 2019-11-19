#include "Title.h"
#include "DxLib.h"

Title::Title(ISceneChanger* changer) : BaseScene(changer)
{

}

//初期化
void Title::Initialize()
{
	mImageHandle = LoadGraph("images/Scene_Config.png");    //画像のロード
}

//更新
void Title::Update()
{
	if (CheckHitKey(KEY_INPUT_W) != 0)
	{ //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_GamePlay);//シーンをメニューに変更
	}
}

//描画
void Title::Draw()
{
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(0, 0, "設定画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
}