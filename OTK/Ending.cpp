#include "Ending.h"
#include <DxLib.h>

Ending::Ending(ISceneChanger* changer) : BaseScene(changer)
{
}

void Ending::Initialize()
{
	//mImageHandle = LoadGraph("clear.png");
	//SoundHandle = LoadSoundMem("GameClear.mp3");
	//PlaySoundMem(SoundHandle, DX_PLAYTYPE_LOOP);
	sound.PlayBGM("GameClear.mp3");
	InputMonitor = 0;
}

void Ending::Finalize()
{
	BaseScene::Finalize();
	//StopSoundMem(SoundHandle);
	sound.StopBGM("GameClear.mp3");
}

void Ending::Update()
{
	pad = GetJoypadInputState(DX_INPUT_PAD1);

	if ((pad & PAD_INPUT_B) || (CheckHitKey(KEY_INPUT_W) == 1))
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

void Ending::Draw()
{
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	DrawString(0, 0, "�G���f�B���O��ʂł��B", GetColor(255, 255, 255));
	DrawString(0, 20, "B�{�^���������ƃ^�C�g���ɐi�݂܂��B", GetColor(255, 255, 255));
	/*DrawGraph(0, 0, mImageHandle, TRUE);*/
}
