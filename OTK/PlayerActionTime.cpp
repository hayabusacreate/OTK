#include "PlayerActionTime.h"

PlayerActionTime::PlayerActionTime()
{

}

PlayerActionTime::~PlayerActionTime()
{
	DeleteGraph(img);
}

void PlayerActionTime::Initialize()
{
	img = LoadGraph("ActionGage.png");
	sizex = 1;
	sizey = 32;
	expansionX = 100.0f;
	MaxexpansionX = 100.f;
	IsActionFlag = false;

	key[256];
	pad = 0;
	InputFlag = 0;
}

void PlayerActionTime::Update(bool ActionFlag, int EnemyDeadScore)
{
	//�L�[���͍X�V
	InputKey();

	//�ő�l�ɓ��B������ő�l������
	if (expansionX >= MaxexpansionX)
	{
		expansionX = MaxexpansionX;
	}

	//�ŏ��l�ɓ��B������ŏ��l������
	if (expansionX <= MinexpansionX)
	{
		expansionX = MinexpansionX;
		//�A�N�V�����t���O�𖳂���
		IsActionFlag = false;
	}
	if (expansionX >= MaxexpansionX * 0.5f)
	{
		//0�ɂȂ��Ă���Ăюg���ɂ�50�K�v
		IsActionFlag = true;
	}

	//�A�N�V�������s�m�F
	if (ActionFlag == false)//���ĂȂ�
	{
		//��ɃQ�[�W�͑�����
		expansionX += 1.f / 10.f;
	}
	else                   //���Ă�
	{
		//�X�y�[�X�������ꂽ��i�A�N�V�������v���C���[�Ŏ��s���ꂽ��j
		if (/*key[KEY_INPUT_SPACE] == 1 || */pad & PAD_INPUT_B)
		{
			//�O�t���[���ŉ����Ă��Ȃ����
			if (InputFlag == 0)
			{
				expansionX -= 10;
			}
			//�O�t���[���Ń{�^���������ꂽ����true�ɂ���
			InputFlag = 1;
		}
		else
		{
			//�{�^����������Ă��Ȃ��ꍇ�́Afalse�ɂ���
			InputFlag = 0;
		}

		expansionX += EnemyDeadScore;


		//1�b�Ԃ�(1/15)*60�̒l��100�Ŋ������l�ŃQ�[�W��0�ɂȂ�
		//25�b�ŃQ�[�W��0�ɂȂ�܂�
		expansionX -= 1.f / 15.f;
	}
}

void PlayerActionTime::InputKey()
{
	static char pushkey[256];
	GetHitKeyStateAll(pushkey);
	pad = GetJoypadInputState(DX_INPUT_PAD1);
	for (int i = 0; i < 256; i++)
	{
		//�L�[��null�o�Ȃ���?
		if (pushkey[i])
		{
			//1�t���O�Ƀ{�^����������Ă��Ȃ�������
			if (key[i] == 0)
			{
				key[i] = 1;
			}
			//1�t���O�Ƀ{�^����������Ă�����
			else if (key[i] == 1)
			{
				key[i] = 2;
			}
		}
		//�����Ȃ�������
		else key[i] = 0;
	}
}

void PlayerActionTime::Draw(float x, float y)
{
	//����̍��W�F�E���̍��W(���݂̈ʒu+�摜�̑傫��*�g�嗦)
	DrawExtendGraph(x, y, x + sizex * expansionX, y + sizey, img, FALSE);
}

bool PlayerActionTime::GetActionFlag()
{
	return IsActionFlag;
}

int PlayerActionTime::GetExpansionX()
{
	return expansionX;
}
