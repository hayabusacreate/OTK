#pragma once
#include<cmath>

//Vector2Dクラス
class Vector2
{
public:
	//デフォルトコンストラクタ
	Vector2();

	//引数付きコンストラクタ
	Vector2(float x, float y);

	//演算子オーバーロード[+]
	Vector2 operator +(const Vector2& vec);

	//演算子オーバーロード[+=]
	Vector2& operator +=(const Vector2& vec);

	//演算子オーバーロード[-]
	Vector2 operator -(const Vector2& vec);

	//演算子オーバーロード[-=]
	Vector2& operator -=(const Vector2& vec);

	//演算子オーバーロード[*]
	Vector2 operator *(const float& scale);

	//演算子オーバーロード[*=]
	Vector2& operator *=(const float& scale);

	//内積
	float Dot(const Vector2& vec);

	//外積
	float Cross(const Vector2& vec);

	//長さ
	float Magnitude();

	//正規化
	Vector2 Normalize();

public:
	float x, y;
};