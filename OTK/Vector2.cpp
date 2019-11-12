#include "Vector2.h"

//�R���X�g���N�^
Vector2::Vector2()
	:x(0), y(0)
{

}

//�����t���R���X�g���N�^
Vector2::Vector2(float x, float y)
	:x(x), y(y)
{

}

//���Z�q�I�[�o�[���[�h[+]
Vector2 Vector2::operator +(const Vector2& vec)
{
	Vector2 t(this->x + vec.x, this->y + vec.y);

	return t;
}
//���Z�q�I�[�o�[���[�h[+=]
Vector2& Vector2::operator+=(const Vector2 & vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

//���Z�q�I�[�o�[���[�h[-]
Vector2 Vector2::operator -(const Vector2& vec)
{
	Vector2 t(this->x - vec.x, this->y - vec.y);

	return t;
}
//���Z�q�I�[�o�[���[�h[-=]
Vector2& Vector2::operator-=(const Vector2 & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

//���Z�q�I�[�o�[���[�h[*]
Vector2 Vector2::operator*(const float & scale)
{
	Vector2 t(this->x * scale, this->y * scale);

	return t;
}

Vector2 & Vector2::operator*=(const float & scale)
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�

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

//���������߂�
float Vector2::Magnitude()
{
	return sqrt(x * x + y * y);
}

//���K��
Vector2 Vector2::Normalize()
{
	Vector2 t(x, y);
	t.x = x / Magnitude();
	t.y = y / Magnitude();
	return t;
}
