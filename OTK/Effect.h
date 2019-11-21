#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Vector2.h"
#include "DxLib.h"

class  Effect
{
public:
	 Effect();
	 ~Effect();
	 void BloodSplash(Vector2& position,float t);//血しぶき
	 void Afterimage(Vector2& position,float t);//残像
	 void Explosion(Vector2 position, float t);//爆発
	 void Trajectory(Vector2& position,float t);//軌跡
	 void Slashing(Vector2& position, float t);//斬撃
	 void Trigger(Vector2& position, float t);//時間停止発動
	 void End(Vector2& position, float t);//時間停止終了
	 //void Explosion();//爆発
	 void Test(const char* filename, Vector2 position, float t);//テスト用
private:
	bool flag;//タイマーセット用
	int i;
	int GHandle[];
};

#endif // !_EFFECT_H_