#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Vector2.h"
#include "DxLib.h"

class  Effect
{
public:
	 Effect();
	 ~Effect();
	 void BloodSplash(const char* filename,Vector2 position,float t);//�����Ԃ�
	 void Afterimage(const char* filename,Vector2 position,float t);//�c��
	 void Trajectory(const char* filename,Vector2 position,float t);//�O��
	 void Slashing(const char* filename, Vector2 position, float t);//�a��
	 void Trigger(const char* filename, Vector2 position, float t);//���Ԓ�~����
	 void End(const char* filename, Vector2 position, float t);//���Ԓ�~�I��
	 //void Explosion();//����
private:
	bool flag;//�^�C�}�[�Z�b�g�p
};

#endif // !_EFFECT_H_