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

// マップとの当たり判定( 戻り値 0:当たらなかった  1:左辺に当たった  2:右辺に当たった
//                                                3:上辺に当たった  4:下辺に当たった
int Map::MapHitCheck(float x, float y, float * MoveX, float * MoveY)
{
	float afX = 0, afY = 0;

	// 移動量を足す
	afX = x + *MoveX;
	afY = y + *MoveY;
	//ブロックにぶつかっていたら
	if (GetMapChip(afX, afY) == 1 ||
		GetMapChip(afX, afY) == 2)
	{
		float blx, bty, brx, bby;

		//ぶつかった時の座標を代入
		blx = (float)((int)afX / CHIP_SIZE) * CHIP_SIZE;        // 左辺の X 座標
		brx = (float)((int)afX / CHIP_SIZE + 1) * CHIP_SIZE;    // 右辺の X 座標

		bty = (float)((int)afY / CHIP_SIZE) * CHIP_SIZE;        // 上辺の Y 座標
		bby = (float)((int)afY / CHIP_SIZE + 1) * CHIP_SIZE;    // 下辺の Y 座標

		// 左辺に当たっていた場合
		if (*MoveX > 0.0f)
		{
			// 移動量を補正する
			*MoveX = blx - x - 1.0f;

			// 左辺に当たったと返す
			return 1;
		}

		// 右辺に当たっていた場合
		if (*MoveX < 0.0f)
		{
			// 移動量を補正する
			*MoveX = brx - x + 1.0f;

			// 右辺に当たったと返す
			return 2;
		}

		// 上辺に当たっていた場合
		if (*MoveY > 0.0f)
		{
			// 移動量を補正する
			*MoveY = bty - y - 1.0f;

			// 上辺に当たったと返す
			return 3;
		}

		// 下辺に当たっていた場合
		if (*MoveY < 0.0f)
		{
			// 移動量を補正する
			*MoveY = bby - y + 1.0f;

			// 下辺に当たったと返す
			return 4;
		}

		//例外設定
		return 4;
	}

	// どこにも当たらなかったと返す
	return 0;
}
