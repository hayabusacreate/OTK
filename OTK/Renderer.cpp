#include "Renderer.h"
#include "DxLib.h"

#define PI    3.1415926535897932384626433832795f

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw(const char* failname, float x, float y)//�摜�`��(����n�_)
{
	//�摜�̓ǂݍ���
	int GHandle = LoadGraph(failname);

	// �ǂ݂��񂾃O���t�B�b�N����ʂɕ`��
	DrawGraph(x, y, GHandle, TRUE);

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	DeleteGraph(GHandle);
}

void Renderer::Draw(const char * failname, float x, float y, float xx, float yy)//�摜�`��(�摜�̃T�C�Y�ύX)
{
	//�摜�̓ǂݍ���
	int GHandle = LoadGraph(failname);

	// �ǂ݂��񂾃O���t�B�b�N����ʂɕ`��
	DrawExtendGraph(x, y, xx, yy, GHandle, TRUE);

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	DeleteGraph(GHandle);
}

//flag true�Ȃ甽�] false�Ȃ炻�̂܂�
void Renderer::Rotate(const char * failname, float x, float y, double angle, int flag)//�摜��]
{
	//�摜�̓ǂݍ���
	int GHandle = LoadGraph(failname);
	double ang = PI / 180 * angle;
	// �ǂ݂��񂾃O���t�B�b�N����]�`��
	DrawRotaGraph(x, y, 1.0f, ang, GHandle, TRUE, flag);

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	DeleteGraph(GHandle);
}

void Renderer::Rotate(const char * failname, float x, float y, float cx, float cy, float angle, int flag)
{
	//�摜�̓ǂݍ���
	int GHandle = LoadGraph(failname);
	double ang = PI / 180 * angle;
	// �ǂ݂��񂾃O���t�B�b�N����]�`��
	DrawRotaGraph2(x, y, cx, cy, 1.0f, ang, GHandle, TRUE, flag);

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	DeleteGraph(GHandle);
}
