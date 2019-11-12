#include "Player.h"
#include "Vector2.h"
#include "Input.h"
#include "DxLib.h"

Input input;
Vector2 position;

Player::Player() :
	Gravity(0.3f),
	JumpForce(9.0f),
	Speed(5.0f),
	scale(30),
	//position(320.0f, 240.0f),
	PlayerDownSpeed(0.0f),
	IsJumpFlag(false),
	ImgIndex(0),
	count(0)
{
	position = Vector2(320.0f, 240.0f);
}

Player::~Player()
{
}

void Player::Move()
{
	input.Update();

	// �ړ��ʂ̏�����
	MoveX = 0.0f;
	MoveY = 0.0f;

	//���ړ�
	if ((input.GetKey() & PAD_INPUT_LEFT) != 0)
	{
		MoveX -= Speed;
	}

	//�E�ړ�
	if ((input.GetKey() & PAD_INPUT_RIGHT) != 0)
	{
		MoveX += Speed;
	}

	// ���n���Ă��邩�X�y�[�X�������ꂽ�Ƃ�
	if (IsJumpFlag == false && (input.GetKey() & PAD_INPUT_10) != 0)
	{
		PlayerDownSpeed -= JumpForce;
		IsJumpFlag = true;
	}

	// ��������;
	PlayerDownSpeed += Gravity;

	// �������x���ړ��ʂɉ�����
	MoveY = PlayerDownSpeed;

	// �ړ��ʂɊ�Â��ăL�����N�^�̍��W���ړ�
	//CheckMapMove(&position.x, &position.y, &PlayerDownSpeed, MoveX, MoveY, scale, &IsJumpFlag);
	position.x = position.x + (MoveX);
}

void Player::Draw()
{
	// �L�����N�^�̕`��
	//DrawBox((int)(player.position.x - player.scale * 0.5F), (int)(player.position.y - player.scale * 0.5F),
	//	(int)(player.position.x + player.scale * 0.5F) + 1, (int)(player.position.y + player.scale * 0.5F) + 1,
	//	GetColor(255, 0, 0), TRUE);


	Vector2 RectPos(position.x - scale * 0.5f, position.y - scale * 0.5f);
	//renderer.Draw("player.png", RectPos);//�ʏ�`��

	//�摜�̓ǂݍ���
	LoadDivGraph("puddle.png", 6, 6, 1, 32, 32, anime);

	//�\������摜�̔ԍ���ύX
	ImgIndex = count % 36;
	ImgIndex /= 6;//����6������悤�ɐݒ肷��

	//�A�j���[�V�����`��
	DrawGraph(position.x - scale * 0.5f, position.y - scale * 0.5f, anime[ImgIndex], true);
	//�J�E���g�𑝂₷
	++count;

	//�A�N�V�����t���O��true�̎�
	/*if (IsActionFlag)
	{
		DrawBox((int)(player.position.x - player.scale * 2.0f), (int)(player.position.y - player.scale * 2.0f),
			(int)(player.position.x + player.scale * 2.0f) + 1, (int)(player.position.y + player.scale * 2.0f) + 1,
			GetColor(255, 0, 0), FALSE);

		//��`�̓����蔻��
		auto dx = abs((player.position.x + player.scale / 2.f) - (enemy.position.x + enemy.scale / 2));
		auto dy = abs((player.position.y + player.scale / 2.f) - (enemy.position.y + enemy.scale / 2));

		//�����蔻��͘g�̑傫���̓�{�ŏ���
		if (dx < (player.scale * 4 + enemy.scale) / 2 && dy < (player.scale * 4 + enemy.scale) / 2)
		{
			DrawString(0, 0, "�g�̒��ɓG������!", GetColor(255, 0, 0));
			enemy.IsHitPlayer = true;
		}
    }*/
}

void Player::Hit(int hit)
{
	
	float Dummy = 0.0f;
	float hsize;
	// �L�����N�^�̍���A�E��A�����A�E�������ɓ����蔻��̂���
	// �}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă�����␳����
	// �����̃T�C�Y���Z�o
	//hsize = Size * 0.5f;
	//�����蔻��̏���
	Move();
}

float Player::ReturnPosX()
{
	return position.x;
}

float Player::ReturnPosY()
{
	return position.y;
}

float Player::ReturnGra()
{
	return MoveY;
}
