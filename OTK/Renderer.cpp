#include "Renderer.h"
#include "DxLib.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw(const char* failname, float x, float y)
{
	//�摜�̓ǂݍ���
	int GHandle = LoadGraph(failname);

	// �ǂ݂��񂾃O���t�B�b�N����ʂɕ`��
	DrawGraph(x, y, GHandle, TRUE);

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	DeleteGraph(GHandle);
}
