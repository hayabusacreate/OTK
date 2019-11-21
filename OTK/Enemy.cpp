#include "Enemy.h"
#include "Player.h"

//�R���X�g���N�^
//�ʒu:�}�b�v
Enemy::Enemy(Vector2 pos, Map map)
	:_position(pos.x * 64, pos.y * 64), _scale(Vector2(60, 60))
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
	MoveSpeed = 2.0f;
	anime[6] = { 0 };
	ImgIndex = 0;
	count = 0;
	img = LoadGraph("puddle.png");
	MoveCount = 0;
	radian = 0;
	IsDeadFlag = false;

	Score = 0;
	isHitPlayer = false;
}

//�X�V
void Enemy::Update()
{

}

//�ړ�
//
void Enemy::Move(Vector2 PlayerPos, Vector2 PlayerSca)
{
	if (!IsDeadFlag)
	{
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
}

void Enemy::HitPlayer(Vector2 PlayerPos, Vector2 PlayerScale, bool IsAction)
{
	//�G�Ƃ̓����蔻��
	auto dx = abs((PlayerPos.x + PlayerScale.x / 2.f) - (_position.x + _scale.x / 2));
	auto dy = abs((PlayerPos.y + PlayerScale.y / 2.f) - (_position.y + _scale.y / 2));

	if (dx < (PlayerScale.x + _scale.x) / 2 && dy < (PlayerScale.y + _scale.y) / 2)
	{ 
		//�v���C���[���A�N�V������Ԃ̎��������S����
		if (IsAction)
		{
			if (IsDeadFlag == false)
			{
				Score = 30;
				IsDeadFlag = true;
			}
			else
			{
				Score = 0;
			}
		}
		else
		{
			if (IsDeadFlag == false)
			{
				isHitPlayer = true;
			}
		}
	}
}

//�`��
void Enemy::Draw()
{
	if (!IsDeadFlag)
	{
		DrawGraph(_position.x - _scale.x * 0.5f, _position.y - _scale.y * 0.5f, img, FALSE);

		//�G�̍��G�͈͉��ŕ\��
		DrawBox((int)(_position.x - _scale.x * 2.0f), (int)(_position.y - _scale.y * 2.0f),
			(int)(_position.x + _scale.x * 2.0f) + 1, (int)(_position.y + _scale.y * 2.0f) + 1,
			GetColor(255, 0, 0), FALSE);

		if (MoveCount == 1)
		{
			DrawBox((int)(_position.x - _scale.x * 2.0f), (int)(_position.y - _scale.y * 2.0f),
				(int)(_position.x + _scale.x * 2.0f) + 1, (int)(_position.y + _scale.y * 2.0f) + 1,
				GetColor(0, 255, 0), FALSE);
		}
	}
}

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

Vector2 Enemy::GetScale()
{
	return Vector2(_scale.x, _scale.y);
}

int Enemy::GetScore()
{
	return Score;
}

bool Enemy::GetHitPlayer()
{
	return isHitPlayer;
}
