#include "DxLib.h"
#include "Renderer.h"
#include<string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int CmdShow)
{
	//Window���[�h�ŋN������
	ChangeWindowMode(true);

	//��ʃT�C�Y��320�~320�ɐݒ�
	SetGraphMode(1920, 1080, 16);

	if (DxLib_Init() == -1) return -1;

	//�`�����w��
	SetDrawScreen(DX_SCREEN_BACK);

	//��ʔw�i�̐F��ݒ肷��
	SetBackgroundColor(255, 255, 255);

	//������
	Renderer renderer;
	
	int i = 0;
	int x = 0;
	//�����܂�

	//�X�V
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//��ʂ��N���A
		ClearDrawScreen();
		//�����艺��

		//�����聪
		//�o�b�N�o�b�t�@�̓��e����ʂɕ\��
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}