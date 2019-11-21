#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Vector2.h"
#include "DxLib.h"

class  Effect
{
public:
	 Effect();
	 ~Effect();
	 void BloodSplash(Vector2& position,float t);//�����Ԃ�
	 void Afterimage(Vector2& position,float t);//�c��
	 void Explosion(Vector2 position, float t);//����
	 void Trajectory(Vector2& position,float t);//�O��
	 void Slashing(Vector2& position, float t);//�a��
	 void Trigger(Vector2& position, float t);//���Ԓ�~����
	 void End(Vector2& position, float t);//���Ԓ�~�I��
	 //void Explosion();//����
	 void Test(const char* filename, Vector2 position, float t);//�e�X�g�p
private:
	bool flag;//�^�C�}�[�Z�b�g�p
	int i;
	int GHandle[];
};

#endif // !_EFFECT_H_