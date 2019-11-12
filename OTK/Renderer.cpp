#include "Renderer.h"
#include "DxLib.h"

#define PI    3.1415926535897932384626433832795f

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw(const char* failname, Vector2 position)//�摜�`��(����n�_)
{
	//�摜�̓ǂݍ���
	int GHandle = LoadGraph(failname);

	// �ǂ݂��񂾃O���t�B�b�N����ʂɕ`��
	DrawGraph(position.x, position.y, GHandle, TRUE);

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	DeleteGraph(GHandle);
}

void Renderer::Draw(const char * failname, Vector2 position, Vector2 scale)//�摜�`��(�摜�̃T�C�Y�ύX)
{
	//�摜�̓ǂݍ���
	int GHandle = LoadGraph(failname);

	// �ǂ݂��񂾃O���t�B�b�N����ʂɕ`��
	DrawExtendGraph(position.x, position.y, scale.x, scale.y, GHandle, TRUE);

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	DeleteGraph(GHandle);
}

//flag true�Ȃ甽�] false�Ȃ炻�̂܂�
void Renderer::Rotate(const char * failname, Vector2 position, double angle, int flag)//�摜��]
{
	//�摜�̓ǂݍ���
	int GHandle = LoadGraph(failname);
	double ang = PI / 180 * angle;
	// �ǂ݂��񂾃O���t�B�b�N����]�`��
	DrawRotaGraph(position.x, position.y, 1.0f, ang, GHandle, TRUE, flag);

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	DeleteGraph(GHandle);
}

void Renderer::Rotate(const char * failname, Vector2 position, Vector2 scale, float angle, int flag)
{
	//�摜�̓ǂݍ���
	int GHandle = LoadGraph(failname);
	double ang = PI / 180 * angle;
	// �ǂ݂��񂾃O���t�B�b�N����]�`��
	DrawRotaGraph2(position.x, position.y, scale.x, scale.y, 1.0f, ang, GHandle, TRUE, flag);

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	DeleteGraph(GHandle);
}
