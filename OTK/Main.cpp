#include "DxLib.h"
#include "Vector2.h"
#include "Renderer.h"

#define SCREEN_WIDTH     (640)                          // ��ʉ���
#define SCREEN_HEIGHT    (480)                          // ��ʏc��
#define CHIP_SIZE        (32)                           // ��̃`�b�v�̃T�C�Y
#define MAP_WIDTH        (SCREEN_WIDTH / CHIP_SIZE)     // �}�b�v�̉���
#define MAP_HEIGHT       (SCREEN_HEIGHT / CHIP_SIZE)    // �}�b�v�̏c��

//�v���C���[�N���X?
typedef struct  Player
{
	float Gravity;         // �L�����Ɋ|����d�͉����x
	float JumpForce;	   // �L�����̃W�����v��
	float Speed;		   // �L�����̈ړ��X�s�[�h
	float scale;	        // �v���C���[�̃T�C�Y
	Vector2 position;       //�v���C���[�̍��W
	float PlayerDownSpeed; //�v���C���[�̗������x
	bool IsJumpFlag;       //�W�����v�������ǂ���?


	int anime[6] = { 0 };    //�v���C���[�̉摜�����z��
	int ImgIndex;          //�`�悷��摜�̔ԍ�
	int count;             //�J�E���g

	//������
	Player()
		:Gravity(0.3f),
		JumpForce(9.0f),
		Speed(5.0f),
		scale(30),
		position(320.0f, 240.0f),
		PlayerDownSpeed(0.0f),
		IsJumpFlag(false),
		ImgIndex(0),
		count(0)
	{

	}

	//�v���C���[�̈ړ�
	void PlayerMove();
	//�v���C���[�̕`��
	void PlayerRenderer();
};

//�G�����e�X�g
typedef struct Enemy
{
	float Gravity;
	float JumpForce;
	float Speed;
	float scale;
	Vector2 position;
	float EnemyDownSpeed;
	bool IsJumpFlag;

	bool IsHitPlayer;

	//������
	Enemy()
		:Gravity(0.3f),
		JumpForce(9.0f),
		Speed(5.0f),
		scale(30),
		position(320.0f, 240.0f),
		EnemyDownSpeed(0.0f),
		IsJumpFlag(false),


		IsHitPlayer(false)
	{

	}

	//�v���C���[�̈ړ�
	void EnemyMove();
	//�v���C���[�̕`��
	void EnemyRenderer();
};

//Input�N���X?
typedef struct  InputState
{
	int input, key;      // ���͏��

	// ���͏�Ԃ̏�����
	InputState()
		:input(0), key(0)
	{

	}

	void InputUpdate();
};

//�}�b�v�N���X�H
typedef struct  Map
{
	int chip[3];

	// �}�b�v�f�[�^
	char MapData[15][22] =
	{
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,1,
		1,0,0,2,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,1,
		1,0,0,2,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0,0,1,
		1,0,0,2,2, 2,2,0,0,0, 0,0,0,0,0, 0,0,2,0,0,0,1,

		1,0,0,0,0, 0,0,0,2,2, 0,0,0,0,0, 0,0,2,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,2,2,0, 0,0,2,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,1,
		1,0,0,0,0, 0,0,2,2,0, 0,0,0,0,0, 2,0,0,0,0,0,1,

		1,0,0,0,0, 2,2,2,2,2, 0,0,0,0,2, 2,0,0,0,0,0,1,
		1,0,0,0,0, 2,2,2,2,2, 0,0,0,2,2, 2,0,0,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,2,2, 2,0,0,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,1,
		1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,1,1,
	};

	// �}�b�v�`�b�v�̒l���擾����֐�
	int GetMapChip(float X, float Y);

	//�}�b�v�̕`��
	void MapRenderer();

	// �}�b�v�Ƃ̓����蔻��( �߂�l 0:������Ȃ�����  1:���ӂɓ�������  2:�E�ӂɓ�������
	//                                                3:��ӂɓ�������  4:���ӂɓ�������
	// ���ӁFMoveX �� MoveY �A�ǂ������Е����O����Ȃ��Ƃ܂Ƃ��ɓ��삵�܂���(��)
	int MapHitCheck(float X, float Y, float *MoveX, float *MoveY);
};


//�v���C���[����
Player player;
//�G�l�~�[����
Enemy enemy;
//Input����
InputState Input;
//�}�b�v����
Map map;
//Renderer����
Renderer renderer;

bool IsActionFlag = false;

int FrameStartTime;        // �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ�

	// �L�����N�^���}�b�v�Ƃ̓����蔻����l�����Ȃ���ړ�����֐�
int CheckMapMove(float *X, float *Y, float *DownSP,
	float MoveX, float MoveY, float Size, bool *JumpFlag);

// �A�N�V�����T���v���v���O�������C���֐�
int ActionMain(void);


// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	// �c�w���C�u�����̏�����
	if (DxLib_Init() == -1) return -1;

	// �A�N�V�����Q�[���̃��C���֐����Ă�
	ActionMain();

	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �I��
	return 0;
}

// �A�N�V�����T���v���v���O�������C��
int ActionMain(void)
{
	// �`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// ���������M����҂��Ȃ�
	SetWaitVSyncFlag(FALSE);

	// �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ������݂̃J�E���g�l�ɃZ�b�g
	FrameStartTime = GetNowCount();

	// ���C�����[�v�J�n�A�d�r�b�L�[�ŊO�ɏo��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ̃N���A
		ClearDrawScreen();

		// �P/�U�O�b���܂ő҂�
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}

		// ���݂̃J�E���g�l��ۑ�
		FrameStartTime = GetNowCount();


		Input.InputUpdate();
		map.MapRenderer();

		enemy.EnemyMove();
		enemy.EnemyRenderer();
		player.PlayerMove();
		player.PlayerRenderer();


		//Z�L�[�������ꂽ�瓖���蔻���\��
		if ((Input.input & PAD_INPUT_1) != 0)
		{
			IsActionFlag = true;
		}
		else
		{
			IsActionFlag = false;
		}


		//��`�̓����蔻��
		auto dx = abs((player.position.x + player.scale / 2.f) - (enemy.position.x + enemy.scale / 2));
		auto dy = abs((player.position.y + player.scale / 2.f) - (enemy.position.y + enemy.scale / 2));

		if (dx < (player.scale + enemy.scale) / 2 && dy < (player.scale + enemy.scale) / 2)
		{
			DrawString(0, 0, "��������!", GetColor(255, 0, 0));
		}

		//�g���ɓG�������Ƃ�
		if (enemy.IsHitPlayer)
		{
			//�G�̈ʒu���擾
			//            b
			Vector2 epos(enemy.position.x, enemy.position.y);
			//            a
			Vector2 ppos(player.position.x, player.position.y);

			//���݂��̒��S�����߂�
			auto x = abs((ppos.x + player.scale / 2.f) - (epos.x + enemy.scale / 2));
			auto y = abs((ppos.y + player.scale / 2.f) - (epos.y + enemy.scale / 2));

			float test(sqrt(x * x + y * y));

			ppos = epos;
		}


		// ��ʂ̍X�V
		ScreenFlip();
	}

	// �I��
	return 0;
}

// �v���C���[�̈ړ�����
void Player::PlayerMove()
{
	float MoveX, MoveY;

	// �ړ��ʂ̏�����
	MoveX = 0.0f;
	MoveY = 0.0f;

	//���ړ�
	if ((Input.input & PAD_INPUT_LEFT) != 0)
	{
		MoveX -= player.Speed;
	}

	//�E�ړ�
	if ((Input.input & PAD_INPUT_RIGHT) != 0)
	{
		MoveX += player.Speed;
	}

	// ���n���Ă��邩�X�y�[�X�������ꂽ�Ƃ�
	if (player.IsJumpFlag == false && (Input.key & PAD_INPUT_10) != 0)
	{
		player.PlayerDownSpeed -= player.JumpForce;
		player.IsJumpFlag = true;
	}

	// ��������;
	player.PlayerDownSpeed += player.Gravity;

	// �������x���ړ��ʂɉ�����
	MoveY = player.PlayerDownSpeed;

	// �ړ��ʂɊ�Â��ăL�����N�^�̍��W���ړ�
	CheckMapMove(&player.position.x, &player.position.y, &player.PlayerDownSpeed, MoveX, MoveY, player.scale, &player.IsJumpFlag);
}

//�v���C���[�̕`��
void Player::PlayerRenderer()
{
	// �L�����N�^�̕`��
	//DrawBox((int)(player.position.x - player.scale * 0.5F), (int)(player.position.y - player.scale * 0.5F),
	//	(int)(player.position.x + player.scale * 0.5F) + 1, (int)(player.position.y + player.scale * 0.5F) + 1,
	//	GetColor(255, 0, 0), TRUE);


	Vector2 RectPos(player.position.x - player.scale * 0.5f, player.position.y - player.scale * 0.5f);
	//renderer.Draw("player.png", RectPos);//�ʏ�`��

	//�摜�̓ǂݍ���
	LoadDivGraph("puddle.png", 6, 6, 1, 32, 32, player.anime);

	//�\������摜�̔ԍ���ύX
	player.ImgIndex = player.count % 36;
	player.ImgIndex /= 6;//����6������悤�ɐݒ肷��

	//�A�j���[�V�����`��
	DrawGraph(player.position.x - player.scale * 0.5f, player.position.y - player.scale * 0.5f, player.anime[player.ImgIndex], true);
	//�J�E���g�𑝂₷
	++player.count;

	//�A�N�V�����t���O��true�̎�
	if (IsActionFlag)
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
	}
}

// ���͏�Ԃ��X�V
void InputState::InputUpdate()
{
	int i;

	// �p�b�h�P�ƃL�[�{�[�h������͂𓾂�
	i = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �G�b�W����������͂��Z�b�g
	Input.key = i & Input.input;

	// ���͏�Ԃ̕ۑ�
	Input.input = i;
}

// �}�b�v�`�b�v�̒l���擾����֐�
int Map::GetMapChip(float X, float Y)
{
	int x, y;

	// �����l�֕ϊ�
	x = (int)X / CHIP_SIZE;
	y = (int)Y / CHIP_SIZE;

	// �w��̍��W�ɊY������}�b�v�̏���Ԃ�
	return map.MapData[y][x];
}

// �}�b�v�̕`��
void Map::MapRenderer()
{
	LoadDivGraph("testblock.png", 3, 3, 1, 32, 32, map.chip);

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 22; x++)
		{
			DrawGraph(x * 32, y * 32, map.chip[MapData[y][x]], FALSE);
		}
	}

	//for (int i = 0; i < MAP_HEIGHT; i++)
	//{
	//	for (int j = 0; j < MAP_WIDTH; j++)
	//	{
	//		// �P�͓����蔻��`�b�v��\���Ă���̂łP�̂Ƃ��낾���`��
	//		if (map.MapData[i][j] == 1)
	//		{
	//			DrawBox(j * CHIP_SIZE, i * CHIP_SIZE,
	//				j * CHIP_SIZE + CHIP_SIZE, i * CHIP_SIZE + CHIP_SIZE,
	//				GetColor(255, 255, 255), TRUE);
	//		}
	//	}
	//}
}

// �L�����N�^���}�b�v�Ƃ̓����蔻����l�����Ȃ���ړ�����
int CheckMapMove(float * X, float * Y, float * DownSP, float MoveX, float MoveY, float Size, bool * JumpFlag)
{
	float Dummy = 0.0f;
	float hsize;

	// �L�����N�^�̍���A�E��A�����A�E�������ɓ����蔻��̂���
	// �}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă�����␳����
	// �����̃T�C�Y���Z�o
	hsize = Size * 0.5f;

	// �悸�㉺�ړ����������Ń`�F�b�N
	{
		// �����̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
		if (map.MapHitCheck(*X - hsize, *Y + hsize, &Dummy, &MoveY) == 3)
		{
			*DownSP = 0.0F;
		}

		// �E���̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
		if (map.MapHitCheck(*X + hsize, *Y + hsize, &Dummy, &MoveY) == 3)
		{
			*DownSP = 0.0F;
		}

		// ����̃`�F�b�N�A�����u���b�N�̉��ӂɓ������Ă����痎��������
		if (map.MapHitCheck(*X - hsize, *Y - hsize, &Dummy, &MoveY) == 4)
		{
			*DownSP *= -1.0F;
		}

		// �E��̃`�F�b�N�A�����u���b�N�̉��ӂɓ������Ă����痎��������
		if (map.MapHitCheck(*X + hsize, *Y - hsize, &Dummy, &MoveY) == 4)
		{
			*DownSP *= -1.0F;
		}

		// �㉺�ړ����������Z
		*Y += MoveY;
	}

	// ��ɍ��E�ړ����������Ń`�F�b�N
	{
		// �����̃`�F�b�N
		map.MapHitCheck(*X - hsize, *Y + hsize, &MoveX, &Dummy);

		// �E���̃`�F�b�N
		map.MapHitCheck(*X + hsize, *Y + hsize, &MoveX, &Dummy);

		// ����̃`�F�b�N
		map.MapHitCheck(*X - hsize, *Y - hsize, &MoveX, &Dummy);

		// �E��̃`�F�b�N
		map.MapHitCheck(*X + hsize, *Y - hsize, &MoveX, &Dummy);

		// ���E�ړ����������Z
		*X += MoveX;
	}

	// �ڒn����
	{
		// �L�����N�^�̍����ƉE����1�s�N�Z�����Ƀu���b�N�����邩?
		if (map.GetMapChip(*X - hsize, *Y + hsize + 1.0f) == 0 &&
			map.GetMapChip(*X + hsize, *Y + hsize + 1.0f) == 0)
		{
			//����������W�����v���ɂ���
			*JumpFlag = true;
		}
		else
		{
			// ��������false
			*JumpFlag = false;
		}
	}

	// �I��
	return 0;
}

// �}�b�v�Ƃ̓����蔻��( �߂�l 0:������Ȃ�����  1:���ӂɓ�������  2:�E�ӂɓ�������
//                                                3:��ӂɓ�������  4:���ӂɓ�������
int Map::MapHitCheck(float X, float Y, float * MoveX, float * MoveY)
{
	float afX, afY;

	// �ړ��ʂ𑫂�
	afX = X + *MoveX;
	afY = Y + *MoveY;

	//�u���b�N�ɂԂ����Ă�����
	if (map.GetMapChip(afX, afY) == 1 ||
		map.GetMapChip(afX, afY) == 2)
	{
		float blx, bty, brx, bby;

		//�Ԃ��������̍��W����
		blx = (float)((int)afX / CHIP_SIZE) * CHIP_SIZE;        // ���ӂ� X ���W
		brx = (float)((int)afX / CHIP_SIZE + 1) * CHIP_SIZE;    // �E�ӂ� X ���W

		bty = (float)((int)afY / CHIP_SIZE) * CHIP_SIZE;        // ��ӂ� Y ���W
		bby = (float)((int)afY / CHIP_SIZE + 1) * CHIP_SIZE;    // ���ӂ� Y ���W

		// ���ӂɓ������Ă����ꍇ
		if (*MoveX > 0.0f)
		{
			// �ړ��ʂ�␳����
			*MoveX = blx - X - 1.0f;

			// ���ӂɓ��������ƕԂ�
			return 1;
		}

		// �E�ӂɓ������Ă����ꍇ
		if (*MoveX < 0.0f)
		{
			// �ړ��ʂ�␳����
			*MoveX = brx - X + 1.0f;

			// �E�ӂɓ��������ƕԂ�
			return 2;
		}

		// ��ӂɓ������Ă����ꍇ
		if (*MoveY > 0.0f)
		{
			// �ړ��ʂ�␳����
			*MoveY = bty - Y - 1.0f;

			// ��ӂɓ��������ƕԂ�
			return 3;
		}

		// ���ӂɓ������Ă����ꍇ
		if (*MoveY < 0.0f)
		{
			// �ړ��ʂ�␳����
			*MoveY = bby - Y + 1.0f;

			// ���ӂɓ��������ƕԂ�
			return 4;
		}

		//��O�ݒ�
		return 4;
	}

	// �ǂ��ɂ�������Ȃ������ƕԂ�
	return 0;
}

void Enemy::EnemyMove()
{
	float MoveX, MoveY;

	// �ړ��ʂ̏�����
	MoveX = 0.0f;
	MoveY = 0.0f;

	// ��������;
	enemy.EnemyDownSpeed += enemy.Gravity;

	// �������x���ړ��ʂɉ�����
	MoveY = enemy.EnemyDownSpeed;

	// �ړ��ʂɊ�Â��ăL�����N�^�̍��W���ړ�
	CheckMapMove(&enemy.position.x, &enemy.position.y, &enemy.EnemyDownSpeed, MoveX, MoveY, enemy.scale, &enemy.IsJumpFlag);
}

void Enemy::EnemyRenderer()
{
	//int red;
	//if (enemy.IsHitPlayer)
	//{
	//	red = 255;
	//}
	//else
	//{
	//	red = 0;
	//}

	//// �L�����N�^�̕`��
	//DrawBox((int)(enemy.position.x - enemy.scale * 0.5F), (int)(enemy.position.y - enemy.scale * 0.5F),
	//	(int)(enemy.position.x + enemy.scale * 0.5F) + 1, (int)(enemy.position.y + enemy.scale * 0.5F) + 1,
	//	GetColor(red, 0, 255), TRUE);

	Vector2 RectPos(enemy.position.x - enemy.scale * 0.5f, enemy.position.y - enemy.scale * 0.5f);
	renderer.Draw("block.png", RectPos);
}
