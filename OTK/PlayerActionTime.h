#include "Vector2.h"
#include "Renderer.h"
#include <DxLib.h>

//�v���C���[�̃X�g�b�v�Q�[�W�N���X
class PlayerActionTime
{
public:
	//�R���X�g���N�^
	PlayerActionTime();

	//�f�X�g���N�^
	~PlayerActionTime();

	//������
	void Initialize();

	//�X�V(�v���C���[�̃A�N�V�����t���O)
	void Update(bool ActionFlag, int EnemyDeadScore);

	//����
	void InputKey();

	//�`��(�\���ʒu(����))
	void Draw(float x, float y);

	//�A�N�V������Ԃ��擾
	bool GetActionFlag();

	//���݂̃Q�[�W���擾
	int GetExpansionX();

private:
	int img;         //�摜��
	int sizex, sizey;//�摜�T�C�Y
	float expansionX;  //�g�嗦
	float MaxexpansionX;//�ő�g�嗦
	float MinexpansionX;//�ŏ��g�嗦
	bool IsActionFlag;//�A�N�V�������ł����Ԃ��H

	int key[256];
	int pad;
};
