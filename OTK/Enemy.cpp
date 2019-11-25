#include "Enemy.h"
#include "Player.h"

//�R���X�g���N�^
//�ʒu:�}�b�v
Enemy::Enemy(Vector2 pos, Map map)
	:SetFastPosition(pos.x * 64, pos.y * 64), _scale(Vector2(60, 60))
{
	this->_map = map;
	Player player(Vector2(11, 10), _map);
}

//�f�X�g���N�^
Enemy::~Enemy()
{
	DeleteGraph(img);
}

//������
void Enemy::Initialize()
{
	_position = SetFastPosition;
	MoveSpeed = 2.0f;
	radian = 0;
	anime[12] = { 0 };
	ImgIndex = 0;
	count = 0;
	img = LoadDivGraph("doro-nn.png", 12, 11, 1, 64, 64, anime);
	MoveCount = 0;
	Score = 0;
	IsActive = true;
	isHitPlayer = false;
	timer.SetTime(0);
	t = false;
	counts = false;
	effect.Init();

	//SoundHandle = LoadSoundMem("Destroy.mp3");
}

//�ړ�
void Enemy::Move(Vector2 PlayerPos, Vector2 PlayerSca, bool IsAction)
{
	if (IsAction)return;
	if (counts)return;
	/*if (!IsActive && !t)
	{
		timer.SetTime(1.5f);
		t = true;
	}
	if (t)timer.Update();
	if (t&&timer.IsTime())counts = true;*/
	if (!IsActive)counts = true;
	if (!IsActive) return;
	if (IsAction) return;

	//�ړ��ʂ̏�����
	Vector2 velocity;
	velocity = Vector2(0, 0);

	//�v���C���[�Ǝ����̓����蔻��
	auto dx = abs((PlayerPos.x + PlayerSca.x * 0.5f) - (_position.x + _scale.x * 0.5f));
	auto dy = abs((PlayerPos.y + PlayerSca.y * 0.5f) - (_position.y + _scale.y * 0.5f));

	//���G�͈�(*2)�ɓ������Ă��邩?
	if (dx < (PlayerSca.x + _scale.x * 2) && dy < (PlayerSca.y + _scale.y * 2))
	{
		//�ړ��J�E���g�X�V
		MoveCount = 1;
	}
	else
	{
		//�������Ă��Ȃ���Ζ߂�
		MoveCount = 0;
	}

	//�������Ă�����v���C���[�̍��W�Ɉړ�
	if (MoveCount == 1)
	{
		radian = atan2(PlayerPos.y - _position.y, PlayerPos.x - _position.x);
		velocity.x += MoveSpeed * cos(radian);
		velocity.y += MoveSpeed * sin(radian);
	}

	//�ړ�
	CheckMapMove(_position, velocity, _scale);
}

//�v���C���[�ɓ����������̏���
void Enemy::HitPlayer(Vector2 PlayerPos, Vector2 PlayerScale, bool IsAction)
{

	//�G�Ƃ̓����蔻��
	auto dx = abs((PlayerPos.x + PlayerScale.x / 2.f) - (_position.x + _scale.x / 2));
	auto dy = abs((PlayerPos.y + PlayerScale.y / 2.f) - (_position.y + _scale.y / 2));

	if (dx < (PlayerScale.x + _scale.x) / 2 && dy < (PlayerScale.y + _scale.y) / 2)
	{
		//�v���C���[���A�N�V������Ԃ�
		if (IsAction)
		{
			//�����������Ă����玀�S
			if (IsActive == true)
			{
				//���y�A�Q�[�W�v���X�A�t���O��܂�
				//PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
				sound.PlaySE("Destroy.mp3");
				Score = 30;
				IsActive = false;
			}
			else
			{
				//����ł���G�ɓ������Ă��X�R�A�͑����Ȃ�
				Score = 0;
			}
		}
		else
		{
			//�A�N�V������ԂłȂ��v���C���[�ɓ���������
			if (IsActive == true)
			{
				//�v���C���[���E���t���O�𗧂Ă�
				isHitPlayer = true;
			}
		}
	}
}

//�`��
void Enemy::Draw(bool IsAction)
{
	if (counts) { effect.Explosion(_position, 0.1f); return; }

	//�G�̉摜�`��
	//�\������摜�̔ԍ���ύX
	if (!IsAction)
	{
		ImgIndex = count % 121;
		ImgIndex /= 11;
		count += 2;
	}

	//�A�j���[�V�����`��
	DrawGraph(_position.x - _scale.x * 0.5f, _position.y - _scale.y * 0.5f, anime[ImgIndex], true);
	//�J�E���g�𑝂₷
	if (!IsActive&& IsAction)effect.Trajectory(_position, 0);
	//if (t)effect.Explosion(_position, 0.1f);
}

//�}�b�v�Ƃ̓����蔻��
int Enemy::CheckMapMove(Vector2 pos, Vector2 velocity, Vector2 scale)
{
	float Dummy = 0.0f;
	Vector2 hsize;

	// �L�����N�^�̍���A�E��A�����A�E�������ɓ����蔻��̂���
	// �}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă�����␳����
	// �����̃T�C�Y���Z�o
	hsize = _scale * 0.5f;

	// �������u���b�N�̏�ɓ��������痎�����~�߂�
	_map.MapHitCheck(_position.x - hsize.x, _position.y + hsize.y, &Dummy, &velocity.y);

	// �E�����u���b�N�̏㓖�����Ă����痎�����~�߂�
	_map.MapHitCheck(_position.x + hsize.x, _position.y + hsize.y, &Dummy, &velocity.y);

	// ���オ�u���b�N�̉��ɓ������Ă����痎��������
	_map.MapHitCheck(_position.x - hsize.x, _position.y - hsize.y, &Dummy, &velocity.y);

	// �E�����u���b�N�̉��ɓ������Ă����痎��������
	_map.MapHitCheck(_position.x + hsize.x, _position.y - hsize.y, &Dummy, &velocity.y);

	// �㉺�ړ����������Z
	_position.y += velocity.y;

	{
		// �����̃`�F�b�N
		_map.MapHitCheck(_position.x - hsize.x, _position.y + hsize.y, &velocity.x, &Dummy);

		// �E���̃`�F�b�N
		_map.MapHitCheck(_position.x + hsize.x, _position.y + hsize.y, &velocity.x, &Dummy);

		// ����̃`�F�b�N
		_map.MapHitCheck(_position.x - hsize.x, _position.y - hsize.y, &velocity.x, &Dummy);

		// �E��̃`�F�b�N
		_map.MapHitCheck(_position.x + hsize.x, _position.y - hsize.y, &velocity.x, &Dummy);

	}
	// ���E�ړ����������Z
	_position.x += velocity.x;

	return 0;
}

//�ʒu�擾
Vector2 Enemy::GetPosition()
{
	return Vector2(_position.x, _position.y);
}

//�傫���擾
Vector2 Enemy::GetScale()
{
	return Vector2(_scale.x, _scale.y);
}

//�Q�[�W�ɒǉ�����|�C���g���擾
int Enemy::GetScore()
{
	return Score;
}

//�v���C���[���E���t���O���擾
bool Enemy::GetHitPlayer()
{
	return isHitPlayer;
}
