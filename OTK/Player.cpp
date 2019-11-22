#include "Player.h"

//�R���X�g���N�^
Player::Player(Vector2 pos, Map map)
	:SetFastPosition(pos.x * 60, pos.y * 60), _scale(Vector2(60, 60))
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
	//�w��ʒu�̏�����
	_position = SetFastPosition;
	Gravity = 0.3f;
	JumpForce = 9.0f;
	MoveSpeed = 3.0f;
	AttackSpeed = 30;
	PlayerDownSpeed = 0.0f;
	IsJumpFlag = false;

	img = LoadDivGraph("saiba-rennbann2.png", 88, 11, 8, 64, 64, anime);
	anime[88];
	ImgIndex = 0;
	count = 0;
	AnimNum = 0;

	ActionFlag = false;
	ActionCount = 0;
	radian = 0;
	pad = 0;
	InputX = 0;
	InputY = 0;
	InputFlag = 0;

	IsActive = true;
}

void Player::Update()
{
	if (!IsActive) return;
	if (ActionCount == 0)
	{
		Move();
	}

	//�p�b�h���͂̍X�V
	pad = GetJoypadInputState(DX_INPUT_PAD1);
}

void Player::Move()
{
	//�ړ��ʂ̐���
	Vector2 velocity;

	velocity = Vector2(0, 0);

	//���ړ�
	if ((pad & PAD_INPUT_LEFT))
	{
		velocity.x -= MoveSpeed;
		AnimNum = 3;
	}
	//�E�ړ�
	else if ((pad & PAD_INPUT_RIGHT))
	{
		velocity.x += MoveSpeed;
		AnimNum = 2;
	}
	else if (IsJumpFlag == false)
	{
		if (AnimNum == 3 || AnimNum == 5 || AnimNum == 7)
			AnimNum = 1;
		if (AnimNum == 2 || AnimNum == 4 || AnimNum == 6)
			AnimNum = 0;
	}


	// ���n���Ă��邩�X�y�[�X�������ꂽ�Ƃ�
	if (IsJumpFlag == false)
	{
		if ((pad & PAD_INPUT_B))
		{
			PlaySoundFile("", DX_PLAYTYPE_BACK);

			PlayerDownSpeed -= JumpForce;
			IsJumpFlag = true;
			if (AnimNum == 0 || AnimNum == 2 || AnimNum == 6)
				AnimNum = 4;
			count = 0;

			if (AnimNum == 1 || AnimNum == 3 || AnimNum == 7)
				AnimNum = 5;
		}
	}

	// ��������;
	PlayerDownSpeed += Gravity;

	// �������x���ړ��ʂɉ�����
	velocity.y = PlayerDownSpeed;

	//�ړ�
	CheckMapMove(_position, &PlayerDownSpeed, velocity, _scale, &IsJumpFlag);
}


//�A�N�V�������s(PlayerActionTime�̃A�N�V�����t���O)
void Player::Action(bool IsActionFlag)
{
	if (!IsActive) return;
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
			if ((pad & PAD_INPUT_A))
			{
				//�O�t���[���ŉ����Ă��Ȃ����
				if (InputFlag == 0)
				{
					PlaySoundFile("", DX_PLAYTYPE_BACK);
					ActionCount = 1;
					radian = 0;
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

			radian = atan2((float)InputY /*- _position.y*/, (float)InputX /*- _position.x*/);

			if (pad & PAD_INPUT_A)
			{
				//�O�t���[���ŉ����Ă��Ȃ����
				if (InputFlag == 0)
				{
					PlaySoundFile("", DX_PLAYTYPE_BACK);
					ActionCount = 0;
				}
				//�O�t���[���Ń{�^���������ꂽ����true�ɂ���
				InputFlag = 1;
			}
			else if (pad & PAD_INPUT_B)
			{
				//�O�t���[���ŉ����Ă��Ȃ����
				if (InputFlag == 0)
				{
					PlaySoundFile("", DX_PLAYTYPE_BACK);
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
			velocity.x += AttackSpeed * cos(radian);
			velocity.y += AttackSpeed * sin(radian);

			StartJoypadVibration(DX_INPUT_PAD1, 500, 1);
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
	if (!IsActive) return;

	//�\������摜�̔ԍ���ύX
	ImgIndex = count % 121;
	ImgIndex /= 11;//����6������悤�ɐݒ肷��
    //�A�j���[�V�����`��
	DrawGraph(_position.x - _scale.x * 0.5f, _position.y - _scale.y * 0.5f, anime[ImgIndex + (11 * AnimNum)], true);

	if (ActionCount != 1)
	{
		//�J�E���g�𑝂₷
		++count;
		++count;
	}
	if (ActionCount == 2)
	{
		//�J�E���g�𑝂₷
		++count;
		++count;
		++count;
		++count;
		++count;
		++count;
		++count;
		++count;
		++count;
		++count;
		++count;
		++count;
		if (AnimNum != 6)
		{
			count = 0;
		}
		else if (count >= 11)
		{
			count == 12;
		}
		if (AnimNum == 0 || AnimNum == 2 || AnimNum == 4)
			AnimNum = 6;
		if (AnimNum == 1 || AnimNum == 3 || AnimNum == 5)
			AnimNum = 7;
	}
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
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
		*PDownS = 0.0f;
	}

	// �E�����u���b�N�̏㓖�����Ă����痎�����~�߂�
	if (_map.MapHitCheck(_position.x + hsize.x, _position.y + hsize.y, &Dummy, &velocity.y) == 3)
	{
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
		*PDownS = 0.0f;
	}

	// ���オ�u���b�N�̉��ɓ������Ă����痎��������
	if (_map.MapHitCheck(_position.x - hsize.x, _position.y - hsize.y, &Dummy, &velocity.y) == 4)
	{
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
		*PDownS = 1.0f;
	}

	// �E�����u���b�N�̉��ɓ������Ă����痎��������
	if (_map.MapHitCheck(_position.x + hsize.x, _position.y - hsize.y, &Dummy, &velocity.y) == 4)
	{
		if (ActionCount == 2)
		{
			ActionCount = 1;
		}
		*PDownS = 1.0f;
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

void Player::SetActive(bool value)
{
	IsActive = value;
}


