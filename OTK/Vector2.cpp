#include "Vector2.h"

//コンストラクタ
Vector2::Vector2()
	:x(0), y(0)
{

}

//引数付きコンストラクタ
Vector2::Vector2(float x, float y)
	:x(x), y(y)
{

}

//演算子オーバーロード[+]
Vector2 Vector2::operator +(const Vector2& vec)
{
	Vector2 t(this->x + vec.x, this->y + vec.y);

	return t;
}
//演算子オーバーロード[+=]
Vector2& Vector2::operator+=(const Vector2 & vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

//演算子オーバーロード[-]
Vector2 Vector2::operator -(const Vector2& vec)
{
	Vector2 t(this->x - vec.x, this->y - vec.y);

	return t;
}
//演算子オーバーロード[-=]
Vector2& Vector2::operator-=(const Vector2 & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

//演算子オーバーロード[*]
Vector2 Vector2::operator*(const float & scale)
{
	Vector2 t(this->x * scale, this->y * scale);

	return t;
}

Vector2 & Vector2::operator*=(const float & scale)
{
	// TODO: return ステートメントをここに挿入します

	this->x *= scale;
	this->y *= scale;

	return *this;
}

float Vector2::Dot(const Vector2 & vec)
{
	return (this->x*vec.x) + (this->y*vec.y);
}

float Vector2::Cross(const Vector2 & vec)
{
	return (this->x*vec.y - this->y*vec.x);
}

//長さを求める
float Vector2::Magnitude()
{
	return sqrt(x * x + y * y);
}

//正規化
Vector2 Vector2::Normalize()
{
	Vector2 t(x, y);
	t.x = x / Magnitude();
	t.y = y / Magnitude();
	return t;
}
