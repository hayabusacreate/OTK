#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player
{
public:
	Player();
	~Player();
	void Move();
	void Draw();
	void Hit(int hit);
	float ReturnPosX();
	float ReturnPosY();
	float ReturnGra();
	//CheckMapMove(&position.x, &position.y, &PlayerDownSpeed, MoveX, MoveY, scale, &IsJumpFlag);
private:
	float Gravity;// �L�����Ɋ|����d�͉����x
	float JumpForce;// �L�����̃W�����v��
	float Speed; // �L�����̈ړ��X�s�[�h
	float scale;// �v���C���[�̃T�C�Y
	//Vector2 position; //�v���C���[�̍��W
	float PlayerDownSpeed;//�v���C���[�̗������x
	bool IsJumpFlag;//�W�����v�������ǂ���?

	int anime[6];//�v���C���[�̉摜�����z��
	int ImgIndex;//�`�悷��摜�̔ԍ�
	int count;//�J�E���g
	float MoveX;
	float MoveY;
};


#endif // !_PLAYER_H_
