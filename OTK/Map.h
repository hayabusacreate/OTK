#ifndef _MAP_H_
#define _MAP_H_

#include "Vector2.h"
#define CHIP_SIZE 64
#define MAP_WIDTH  (Screen::WindowWidth  / CHIP_SIZE);
#define MAP_HEIGHT (Screen::WindowHeight / CHIP_SIZE);

class Map
{
public:
	//コンストラクタ
	Map();

	//デストラクタ
	~Map();

	void Initialize();

	//マップの限界値取得
	int GetMapChip(float x, float y);

	//描画
	void Draw();

	//マップとの当たり判定
	//戻り値 0:当たらなかった  1 : 左辺に当たった  2 : 右辺に当たった
	//                         3 : 上辺に当たった  4 : 下辺に当たった
	int MapHitCheck(float x, float y, float * MoveX, float * MoveY);

	char MapData[17][30] =
	{
        1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,1,0,0,0, 0,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,1,0,0,0, 0,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,1,0,0,0, 0,0,0,0,1,
		1,0,0,0,0, 0,0,0,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,0,0,0, 1,1,1,1,1,
												    		   
		1,0,0,0,0, 0,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,0,0,0, 0,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,0,0,0, 0,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,0,0,0, 0,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,1,1, 1,1,1,1,1,
		1,0,0,0,0, 0,0,0,1,0, 0,0,1,1,1, 1,1,0,0,0, 0,0,1,0,0, 0,0,0,0,1,
												    		   
		1,0,0,0,0, 0,0,0,1,0, 0,0,0,0,0, 1,1,0,0,0, 0,0,1,0,0, 0,0,0,0,1,
		1,0,0,0,0, 0,0,0,1,0, 0,0,0,0,0, 1,1,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,0,0,0, 0,0,0,1,1, 1,1,0,0,0, 1,1,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,1,0,0,0, 0,0,1,1,1, 1,1,1,1,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,1,0,0,0, 0,0,1,1,1, 1,1,1,1,1,
												    		   
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,1,0,0,0, 0,0,1,1,1, 1,1,1,1,1,
		1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
	};


private:
	int chip[3];
	int img;
};


#endif // !_MAP_H_
