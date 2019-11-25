#include "Vector2.h"
#include <DxLib.h>
#include "Map.h"
#include "Renderer.h"
#include "Effect.h"
#include "CountDownTimer.h"
#include "Sound.h"

//�G�l�~�[�N���X
class Enemy
{
public:
	//�R���X�g���N�^(�����ʒu�F�}�b�v)
	Enemy(Vector2 pos, Map map);

	//�f�X�g���N�^
	~Enemy();

	//������
	void Initialize();

	//�ړ�(�v���C���[�̈ʒu�F�v���C���[�̃T�C�Y)
	void Move(Vector2 PlayerPos, Vector2 PlayerScale,bool IsAction);

	//�v���C���[�ƓG�̓����蔻��(�v���C���[�̈ʒu�F�v���C���[�̃T�C�Y:�A�N�V����)
	void HitPlayer(Vector2 PlayerPos, Vector2 PlayerScale, bool IsAction);

	//�`��
	void Draw();

	//�����蔻��
	int CheckMapMove(Vector2 pos, Vector2 velocity, Vector2 scale);

	//�ʒu���擾
	Vector2 GetPosition();

	//�傫�����擾
	Vector2 GetScale();

	//�G��|�����Ƃ��ɃQ�[�W�𑝂₷�Ƃ��Ɏg�������
	int GetScore();

	//��A�N�V�����̃v���C���[�ɂԂ��������H
	bool GetHitPlayer();

private:
	Vector2 _position;    //�G�l�~�[�̍��W
	Vector2 _scale;       // �G�l�~�[�̃T�C�Y
	float MoveSpeed;      // �L�����̈ړ��X�s�[�h
	float radian;         //�G�̈ړ���������
	int anime[12];         //�G�l�~�[�̉摜�����z��
	int ImgIndex;         //�`�悷��摜�̔ԍ�
	int count;            //�J�E���g
	int img;              //�摜��
	int MoveCount;        //�ړ��p�̃J�E���g
	int Score;            //�|���ꂽ�Ƃ��̃J�E���g
	bool IsActive;        //ture:�����Ă��� false:����ł���
	bool isHitPlayer;     //true:�v���C���[�ɓ������� false:�v���C���[�ɓ������Ă��Ȃ�
	Map _map;             //�}�b�v���������Ă���
	
	Vector2 SetFastPosition;//�v���C���[�̏����ʒu�i�[�p
	Effect effect;
	CountDownTimer timer;
	bool t;//�^�C�}�[�̃Z�b�g����x�����ʂ�
	bool counts;

	int SoundHandle;
	Sound sound;
};