#include "Map.h"
#include "DxLib.h"

Map::Map()
{

}

Map::~Map()
{
	DeleteGraph(img);
}

void Map::Initialize()
{
	//img = LoadDivGraph("0001.png", 1, 1, 1, 64, 64, chip);
}

int Map::GetMapChip(float x, float y)
{
	int X, Y;

	X = x / CHIP_SIZE;
	Y = y / CHIP_SIZE;
	return MapData[Y][X];
}

void Map::Draw()
{
	LoadDivGraph("haikei.png", 2, 2,1, 64, 64, chip);
	//LoadDivGraph("0001.png", 1, 1, 1, 64, 64, chip);
	for (int y = 0; y < 17; y++)
	{
		for (int x = 0; x < 30; x++)
		{
			DrawGraph(x * 64, y * 64, chip[MapData[y][x]], FALSE);
		}
	}
}

// �}�b�v�Ƃ̓����蔻��( �߂�l 0:������Ȃ�����  1:���ӂɓ�������  2:�E�ӂɓ�������
//                                                3:��ӂɓ�������  4:���ӂɓ�������
int Map::MapHitCheck(float x, float y, float * MoveX, float * MoveY)
{
	float afX = 0, afY = 0;

	// �ړ��ʂ𑫂�
	afX = x + *MoveX;
	afY = y + *MoveY;
	//�u���b�N�ɂԂ����Ă�����
	if (GetMapChip(afX, afY) == 1 ||
		GetMapChip(afX, afY) == 2)
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
			*MoveX = blx - x - 1.0f;

			// ���ӂɓ��������ƕԂ�
			return 1;
		}

		// �E�ӂɓ������Ă����ꍇ
		if (*MoveX < 0.0f)
		{
			// �ړ��ʂ�␳����
			*MoveX = brx - x + 1.0f;

			// �E�ӂɓ��������ƕԂ�
			return 2;
		}

		// ��ӂɓ������Ă����ꍇ
		if (*MoveY > 0.0f)
		{
			// �ړ��ʂ�␳����
			*MoveY = bty - y - 1.0f;

			// ��ӂɓ��������ƕԂ�
			return 3;
		}

		// ���ӂɓ������Ă����ꍇ
		if (*MoveY < 0.0f)
		{
			// �ړ��ʂ�␳����
			*MoveY = bby - y + 1.0f;

			// ���ӂɓ��������ƕԂ�
			return 4;
		}

		//��O�ݒ�
		return 4;
	}

	// �ǂ��ɂ�������Ȃ������ƕԂ�
	return 0;
}
