#pragma once

//�^�X�N�N���X
class Task
{
public:
	//�f�X
	virtual ~Task()
	{

	}
	//������
	virtual void Initialize()
	{

	}

	//�I������
	virtual void Finalize()
	{

	}
	virtual void Update() = 0;   //�X�V
	virtual void Draw() = 0;   //�`��
};
