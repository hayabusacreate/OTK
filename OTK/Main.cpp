#include "DxLib.h"
#include "SceneManager.h"
#include "Effect.h"
#include "Screen.h"

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//	Window���[�h�̐ݒ�
	ChangeWindowMode(TRUE);
	//Window�^�C�g����ݒ肷��
	SetMainWindowText("�^�C�g��");
	//��ʃT�C�Y����
	SetGraphMode(Screen::WindowWidth, Screen::WindowHeight, 16);

	// �c�w���C�u�����̏�����
	if (DxLib_Init() == -1) return -1;

	// �`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// ���������M����҂��Ȃ�
	SetWaitVSyncFlag(FALSE);

	// �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ������݂̃J�E���g�l�ɃZ�b�g
	int FrameStartTime = GetNowCount();

	SceneManager scenemanager;
	scenemanager.Initialize();

	

	// ���C�����[�v�J�n�A�d�r�b�L�[�ŊO�ɏo��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ̃N���A
		ClearDrawScreen();

		// �P/�U�O�b���܂ő҂�
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}

		// ���݂̃J�E���g�l��ۑ�
		FrameStartTime = GetNowCount();

		scenemanager.Update();
		scenemanager.Draw();
		
		//���]
		ScreenFlip();
	}

	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �I��
	return 0;
}



