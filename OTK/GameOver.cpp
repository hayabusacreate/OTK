#include "GameOver.h"
#include <DxLib.h>

GameOver::GameOver(ISceneChanger* changer) : BaseScene(changer)
{
}

void GameOver::Initialize()
{
	mImageHandle = LoadGraph("over.png");
	SoundHandle = LoadSoundMem("GameOver.mp3");
	PlaySoundMem(SoundHandle, DX_PLAYTYPE_LOOP);
	InputMonitor = 0;
}

void GameOver::Finalize()
{
	BaseScene::Finalize();
	StopSoundMem(SoundHandle);
}

void GameOver::Update()
{
	pad = GetJoypadInputState(DX_INPUT_PAD1);

	if (pad & PAD_INPUT_B)
	{
		if (InputMonitor == 0)
		{
			mSceneChanger->ChangeScene(eScene_Title);//�V�[�������j���[�ɕύX
		}
		InputMonitor = 1;
	}
	else
	{
		InputMonitor = 0;
	}
}

void GameOver::Draw()
{
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	DrawString(0, 0, "�Q�[���I�[�o�[��ʂł��B", GetColor(255, 255, 255));
	DrawString(0, 20, "B�{�^���������ƃ^�C�g���ɐi�݂܂��B", GetColor(255, 255, 255));
}

