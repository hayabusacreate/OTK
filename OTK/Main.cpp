#include "DxLib.h"
#include "GamePlay.h"

#define SCREEN_WIDTH     (640)                          // ��ʉ���
#define SCREEN_HEIGHT    (480)                          // ��ʏc��
#define CHIP_SIZE        (32)                           // ��̃`�b�v�̃T�C�Y
#define MAP_WIDTH        (SCREEN_WIDTH / CHIP_SIZE)     // �}�b�v�̉���
#define MAP_HEIGHT       (SCREEN_HEIGHT / CHIP_SIZE)    // �}�b�v�̏c��




// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	// �c�w���C�u�����̏�����
	if (DxLib_Init() == -1) return -1;

	// �`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// ���������M����҂��Ȃ�
	SetWaitVSyncFlag(FALSE);

	// �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ������݂̃J�E���g�l�ɃZ�b�g
	int FrameStartTime = GetNowCount();

	GamePlay game;
	game.Init();

	// ���C�����[�v�J�n�A�d�r�b�L�[�ŊO�ɏo��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ̃N���A
		ClearDrawScreen();

		// �P/�U�O�b���܂ő҂�
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}

		// ���݂̃J�E���g�l��ۑ�
		FrameStartTime = GetNowCount();

		game.Update();
		game.Draw();
		
		ScreenFlip();
	}

	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �I��
	return 0;
}



