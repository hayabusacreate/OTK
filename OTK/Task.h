#pragma once

//タスククラス
class Task
{
public:
	//デス
	virtual ~Task()
	{

	}
	//初期化
	virtual void Initialize()
	{

	}

	//終了処理
	virtual void Finalize()
	{

	}
	virtual void Update() = 0;   //更新
	virtual void Draw() = 0;   //描画
};
