#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"
#include "Effect.h"
#include "Sound.h"

//ゲーム画面クラス
class GamePlay
	: public BaseScene
{

public:
	GamePlay(ISceneChanger * changer);
	void Initialize() override;    //初期化処理をオーバーライド。
	void Finalize() override;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。

private:
	int count;
	int SoundHandle;
	Sound sound;
};
