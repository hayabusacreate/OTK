#define _PLAYER_H_
#include "Vector2.h"
#include <DxLib.h>
#include "Map.h"

//�v���C���[�N���X
class Player
{
public:
	//�R���X�g���N�^(�����ʒu�F�}�b�v)
	Player(Vector2 pos, Map map);

	//�f�X�g���N�^
	~Player();

	//������
	void Initialize();

	//�X�V
	void Update();

	//����
	void InputKey_PAD();

	//�ړ�
	void Move();

	//�A�N�V�������s(PlayerActionTime�̃A�N�V�����t���O:�G�̈ʒu:�G�̑傫��)
	void Action(bool ActionFlag);


	//�`��
	void Draw();

	//�����蔻��(�ʒu�F�������x�F�ړ��ʁF�T�C�Y�F�W�����v�t���O)
	int CheckMapMove(Vector2 pos, float * PDownS, Vector2 velocity, Vector2 scale, bool *JumpFlag);

	//�ʒu���擾
	Vector2 GetPosition();

	//�傫�����擾
	Vector2 GetScale();

	//�A�N�V�����t���O�擾
	bool GetActionFlag();

	void SetActive(bool value);

private:
	Vector2 _position;    //�v���C���[�̍��W
	Vector2 _scale;       // �v���C���[�̃T�C�Y
	float Gravity;        // �L�����Ɋ|����d�͉����x
	float JumpForce;      // �L�����̃W�����v��
	float MoveSpeed;      // �L�����̈ړ��X�s�[�h
	float AttackSpeed;
	float PlayerDownSpeed;//�v���C���[�̗������x
	bool IsJumpFlag;      //�W�����v�������ǂ���?
	int img;


	int anime[88];         //�v���C���[�̉摜�����z��
	int ImgIndex;         //�`�悷��摜�̔ԍ�
	int AnimNum;          //�A�j���[�V�����ԍ�
	int count;            //�J�E���g
	Map _map;             //�}�b�v���


	bool ActionFlag;      //�A�N�V�������s
	int ActionCount;      //0:�ʏ���,1:���G���,2:�p�x�w��&���ˑҋ@���,3:�ړ����
	float radian;         //�����v�Z

	int key[256];         // 0:���͂���Ă��Ȃ� 1:���͂��ꂽ�u�� 2:���͂���Ă���
	int pad;          // 0:���͂���Ă��Ȃ� 1:���͂��ꂽ�u�� 2:���͂���Ă���

	int InputX, InputY;

	int InputFlag; //�P�t���O�Ƀ{�^���������ꂽ��

	bool IsActive;//true:���� false:�����Ă���
};
