#pragma once

typedef enum
{
	eScene_Title,    //タイトル
	eScene_GamePlay, //ゲームプレイ
	eScene_Ending,   //エンディング
	eScene_GameOver, //ゲームオーバー
	eScene_None      //なし
} eScene;


//シーンを変更するためのインターフェイスクラス
class ISceneChanger
{
public:
	virtual ~ISceneChanger() = 0;
	//指定シーンに変更する
	virtual void ChangeScene(eScene nextScene) = 0;
};
