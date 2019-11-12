#ifndef _MAP_H_
#define _MAP_H_

class Map
{
public:
	Map();
	~Map();
	int GetMapChip(float x, float y);
	void Draw();
	int MapHitCheck(float x, float y, float MoveX, float MoveY);

private:
	int chip[3];
	char MapData[15][22]=
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

	
};


#endif // !_MAP_H_
