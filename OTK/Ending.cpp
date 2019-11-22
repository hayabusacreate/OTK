#include "Ending.h"
#include <DxLib.h>

Ending::Ending(ISceneChanger* changer) : BaseScene(changer)
{
}

void Ending::Initialize()
{
	PlaySoundFile("", DX_PLAYTYPE_LOOP);
	InputMonitor = 0;
}

void Ending::Update()
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

void Ending::Draw()
{
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	DrawString(0, 0, "�G���f�B���O��ʂł��B", GetColor(255, 255, 255));
	DrawString(0, 20, "B�{�^���������ƃ^�C�g���ɐi�݂܂��B", GetColor(255, 255, 255));
	//DrawString(0, 40, "S�L�[�������ƂɃQ�[����ʂɐi�݂܂��B", GetColor(255, 255, 255));
}
