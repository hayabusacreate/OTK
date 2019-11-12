#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Vector2.h"
#include "DxLib.h"

class  Effect
{
public:
	 Effect();
	 ~Effect();
	 void BloodSplash(const char* filename,Vector2 position,float t);//血しぶき
	 void Afterimage(const char* filename,Vector2 position,float t);//残像
	 void Trajectory(const char* filename,Vector2 position,float t);//軌跡
	 void Slashing(const char* filename, Vector2 position, float t);//斬撃
	 void Trigger(const char* filename, Vector2 position, float t);//時間停止発動
	 void End(const char* filename, Vector2 position, float t);//時間停止終了
	 //void Explosion();//爆発
private:
	bool flag;//タイマーセット用
};

#endif // !_EFFECT_H_