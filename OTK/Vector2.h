#pragma once
#include<cmath>

//Vector2D�N���X
class Vector2
{
public:
	//�f�t�H���g�R���X�g���N�^
	Vector2();

	//�����t���R���X�g���N�^
	Vector2(float x, float y);

	//���Z�q�I�[�o�[���[�h[+]
	Vector2 operator +(const Vector2& vec);

	//���Z�q�I�[�o�[���[�h[+=]
	Vector2& operator +=(const Vector2& vec);

	//���Z�q�I�[�o�[���[�h[-]
	Vector2 operator -(const Vector2& vec);

	//���Z�q�I�[�o�[���[�h[-=]
	Vector2& operator -=(const Vector2& vec);

	//���Z�q�I�[�o�[���[�h[*]
	Vector2 operator *(const float& scale);

	//���Z�q�I�[�o�[���[�h[*=]
	Vector2& operator *=(const float& scale);

	//����
	float Dot(const Vector2& vec);

	//�O��
	float Cross(const Vector2& vec);

	//����
	float Magnitude();

	//���K��
	Vector2 Normalize();

public:
	float x, y;
};