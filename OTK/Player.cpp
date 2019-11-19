#include "Player.h"
#include "Input.h"

Input input;

//�R���X�g���N�^
Player::Player(Vector2 pos, Map map)
	:_position(pos.x * 32, pos.y * 32), _scale(Vector2(30, 30))
{
	this->_map = map;
}

//�f�X�g���N�^
Player::~Player()
{
	DeleteGraph(img);
}

void Player::Initialize()
{
	Gravity = 0.3f;
	JumpForce = 9.0f;
	MoveSpeed = 5.0f;
	PlayerDownSpeed = 0.0f;
	IsJumpFlag = false;

	anime[6] = { 0 };
	ImgIndex = 0;
	count = 0;
	//�摜�̓ǂݍ���
	img = LoadDivGraph("puddle.png", 6, 6, 1, 32, 32, anime);


	ActionFlag = false;
	ActionCount = 0;
	radian = 0;

	key[256];
	pad = 0;

	InputX = 0;
	InputY = 0;

	InputFlag = 0;
}

void Player::Update()
{
	if (ActionCount == 0)
	{
		Move();
	}

	pad = GetJoypadInputState(DX_INPUT_PAD1);

	InputKey_PAD();
}

//�v���C���[Input�N���X(�ł���΃��C�u�������H����������)
void Player::InputKey_PAD()
{
	static char pushkey[256];
	GetHitKeyStateAll(pushkey);
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

	for (int i = 0; i < 28; i++)
	{
		if (pad & (1 << i))//�{�^��i�̓��̓t���O�������Ă�����
		{
			DrawFormatString(0, i * 15, GetColor(255, 255, 255), "%d�̃L�[��������Ă��܂�", i);
		}
	}
}

void Player::Move()
{
	//�ړ��ʂ̐���
	Vector2 velocity;

	velocity = Vector2(0, 0);

	//���ړ�
	if (/*key[KEY_INPUT_LEFT] == 2 ||*/
		(pad & PAD_INPUT_LEFT))
	{
		velocity.x -= MoveSpeed;
	}

	//�E�ړ�
	if (/*key[KEY_INPUT_RIGHT] == 2 ||*/
		(pad & PAD_INPUT_RIGHT))
	{
		velocity.x += MoveSpeed;
	}


	// ���n���Ă��邩�X�y�[�X�������ꂽ�Ƃ�
	if (IsJumpFlag == false)
	{
		if (/*(key[KEY_INPUT_SPACE] == 1) || */(pad & PAD_INPUT_B))
		{
			//�O�t���[���ŉ����Ă��Ȃ����
			if (InputFlag == 0)
			{
				PlayerDownSpeed -= JumpForce;
				IsJumpFlag = true;
			}
			//�O�t���[���Ń{�^���������ꂽ����true�ɂ���
			InputFlag = 1;
		}
		else
		{
			//�{�^����������Ă��Ȃ��ꍇ�́Afalse�ɂ���
			InputFlag = 0;
		}
	}

	// ��������;
	PlayerDownSpeed += Gravity;

	// �������x���ړ��ʂɉ�����
	velocity.y = PlayerDownSpeed;

	//�ړ�
	CheckMapMove(_position, &PlayerDownSpeed, velocity, _scale, &IsJumpFlag);
}


//�A�N�V�������s(PlayerActionTime�̃A�N�V�����t���O:�G�̈ʒu:�G�̑傫��)
void Player::Action(bool IsActionFlag)
{
	//�ړ��ʂ̏�����
	Vector2 velocity;
	velocity = Vector2(0, 0);

	//0�̎��̓A�N�V�������Ă��Ȃ�
	if (ActionCount == 0) ActionFlag = false;
	//�A�N�V�������Ă���
	else ActionFlag = true;

	//�Q�[�W��0���傫���Ƃ�
	if (IsActionFlag == true)
	{
		//�ʏ���
		if (ActionCount == 0)
		{
			//&z�L�[�������ꂽ��
			if (/*key[KEY_INPUT_Z] == 1 || */(pad & PAD_INPUT_A))
			{
				//�O�t���[���ŉ����Ă��Ȃ����
				if (InputFlag == 0)
				{
					ActionCount = 1;
				}
				//�O�t���[���Ń{�^���������ꂽ����true�ɂ���
				InputFlag = 1;
			}
			else
			{
				//�{�^����������Ă��Ȃ��ꍇ�́Afalse�ɂ���
				InputFlag = 0;
			}
		}
		//�������͏��
		else if (ActionCount == 1)
		{
			//�W���C�p�b�h�̃X�e�B�b�N���͎擾
			GetJoypadAnalogInput(&InputX, &InputY, DX_INPUT_PAD1);

			radian = atan2((float)InputY - _position.y, (float)InputX - _position.x);

			if (/*key[KEY_INPUT_Z] == 1 || */pad & PAD_INPUT_A)
			{
				//�O�t���[���ŉ����Ă��Ȃ����
				if (InputFlag == 0)
				{
					ActionCount = 0;
				}
				//�O�t���[���Ń{�^���������ꂽ����true�ɂ���
				InputFlag = 1;
			}
			else if (/*key[KEY_INPUT_SPACE] == 1 || */pad & PAD_INPUT_B)
			{
				//�O�t���[���ŉ����Ă��Ȃ����
				if (InputFlag == 0)
				{
					ActionCount = 2;
				}
				//�O�t���[���Ń{�^���������ꂽ����true�ɂ���
				InputFlag = 1;
			}
			else
			{
				//�{�^����������Ă��Ȃ��ꍇ�́Afalse�ɂ���
				InputFlag = 0;
			}
		}
		//�ړ�
		else if (ActionCount == 2)
		{
			velocity.x += MoveSpeed * cos(radian);
			velocity.y += MoveSpeed * sin(radian);

			StartJoypadVibration(DX_INPUT_PAD1, 500,1);
		}

		//�ړ�
		CheckMapMove(_position, &PlayerDownSpeed, velocity, _scale, &IsJumpFlag);
	}
	//�Q�[�W��0��菬�����Ȃ�A�A�N�V�����o���Ȃ�����
	else
	{
		ActionCount = 0;
	}
}


void Player::Draw()
{
	//�A�N�V�������[�h��1�̎�
	if (ActionCount == 1)
	{
		//�G�̍��G�͈͉��ŕ\��
		DrawBox((int)(_position.x - _scale.x * 2.0f), (int)(_position.y - _scale.y * 2.0f),
			(int)(_position.x + _scale.x * 2.0f) + 1, (int)(_position.y + _scale.y * 2.0f) + 1,
			GetColor(0, 255, 0), FALSE);
	}
	else
	{
		//�G�̍��G�͈͉��ŕ\��
		DrawBox((int)(_position.x - _scale.x * 2.0f), (int)(_position.y - _scale.y * 2.0f),
			(int)(_position.x + _scale.x * 2.0f) + 1, (int)(_position.y + _scale.y * 2.0f) + 1,
			GetColor(255, 255, 0), FALSE);
	}
	//�\������摜�̔ԍ���ύX
	ImgIndex = count % 36;
	ImgIndex /= 6;//����6������悤�ɐݒ肷��

	//�A�j���[�V�����`��
	DrawGraph(_position.x - _scale.x * 0.5f, _position.y - _scale.y * 0.5f, anime[ImgIndex], true);
	//�J�E���g�𑝂₷
	++count;

}

int Player::CheckMapMove(Vector2 pos, float * PDownS, Vector2 velocity, Vector2 scale, bool * JumpFlag)
{
	float Dummy = 0.0f;
	Vector2 hsize;

	// �L�����N�^�̍���A�E��A�����A�E�������ɓ����蔻��̂���
	// �}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă�����␳����
	// �����̃T�C�Y���Z�o
	hsize = _scale * 0.5f;
	// �������u���b�N�̏�ɓ��������痎�����~�߂�
	if (_map.MapHitCheck(_position.x - hsize.x, _position.y + hsize.y, &Dummy, &velocity.y) == 3)
	{
		*PDownS = 0.0f;
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

	// �E�����u���b�N�̏㓖�����Ă����痎�����~�߂�
	if (_map.MapHitCheck(_position.x + hsize.x, _position.y + hsize.y, &Dummy, &velocity.y) == 3)
	{
		*PDownS = 0.0f;
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

	// ���オ�u���b�N�̉��ɓ������Ă����痎��������
	if (_map.MapHitCheck(_position.x - hsize.x, _position.y - hsize.y, &Dummy, &velocity.y) == 4)
	{
		*PDownS = 1.0f;
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

	// �E�����u���b�N�̉��ɓ������Ă����痎��������
	if (_map.MapHitCheck(_position.x + hsize.x, _position.y - hsize.y, &Dummy, &velocity.y) == 4)
	{
		*PDownS = 1.0f;
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

	// �㉺�ړ����������Z
	_position.y += velocity.y;

	// �����̃`�F�b�N
	if (_map.MapHitCheck(_position.x - hsize.x, _position.y + hsize.y, &velocity.x, &Dummy) == 2)
	{
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

	// �E���̃`�F�b�N
	if (_map.MapHitCheck(_position.x + hsize.x, _position.y + hsize.y, &velocity.x, &Dummy) == 1)
	{
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

	// ����̃`�F�b�N
	if (_map.MapHitCheck(_position.x - hsize.x, _position.y - hsize.y, &velocity.x, &Dummy) == 2)
	{
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

	// �E��̃`�F�b�N
	if (_map.MapHitCheck(_position.x + hsize.x, _position.y - hsize.y, &velocity.x, &Dummy) == 1)
	{
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
	}

#pragma region �^�[�Q�b�g������Ƃ�
	//// �����̃`�F�b�N
	//if (_map.MapHitCheck(_position.x - hsize.x, _position.y + hsize.y, &velocity.x, &Dummy) == 2)
	//{
	//	if (ActionCount == 3)
	//	{
	//		ActionCount = 1;
	//	}
	//}

	//// �E���̃`�F�b�N
	//if (_map.MapHitCheck(_position.x + hsize.x, _position.y + hsize.y, &velocity.x, &Dummy) == 1)
	//{
	//	if (ActionCount == 3)
	//	{
	//		ActionCount = 1;
	//	}
	//}

	//// ����̃`�F�b�N
	//if (_map.MapHitCheck(_position.x - hsize.x, _position.y - hsize.y, &velocity.x, &Dummy) == 2)
	//{
	//	if (ActionCount == 3)
	//	{
	//		ActionCount = 1;
	//	}
	//}

	//// �E��̃`�F�b�N
	//if (_map.MapHitCheck(_position.x + hsize.x, _position.y - hsize.y, &velocity.x, &Dummy) == 1)
	//{
	//	if (ActionCount == 3)
	//	{
	//		ActionCount = 1;
	//	}
	//}
#pragma endregion

	// ���E�ړ����������Z
	_position.x += velocity.x;

	// �L�����N�^�̍����ƉE����1�s�N�Z�����Ƀu���b�N�����邩?
	if (_map.GetMapChip(_position.x - hsize.x, _position.y + hsize.y + 1.0f) == 0 &&
		_map.GetMapChip(_position.x + hsize.x, _position.y + hsize.y + 1.0f) == 0)
	{
		//����������W�����v���ɂ���
		*JumpFlag = true;
	}
	else
	{
		// ��������false
		*JumpFlag = false;
	}

	return 0;
}

//�v���C���[�̈ʒu�擾
Vector2 Player::GetPosition()
{
	return Vector2(_position.x, _position.y);
}

Vector2 Player::GetScale()
{
	return Vector2(_scale.x, _scale.y);
}

bool Player::GetActionFlag()
{
	return ActionFlag;
}


