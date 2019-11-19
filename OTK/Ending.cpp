#include "Ending.h"
#include <DxLib.h>

Ending::Ending(ISceneChanger* changer) : BaseScene(changer) {
}

void Ending::Initialize()
{
}

void Ending::Update()
{
	if (CheckHitKey(KEY_INPUT_W) != 0)//W
	{
		mSceneChanger->ChangeScene(eScene_Title);
	}
	//if (CheckHitKey(KEY_INPUT_5))//S
	//{
	//	mSceneChanger->ChangeScene(eScene_GamePlay);
	//}
}

void Ending::Draw()
{
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	DrawString(0, 0, "�G���f�B���O��ʂł��B", GetColor(255, 255, 255));
	DrawString(0, 20, "W�L�[�������ƃ^�C�g���ɐi�݂܂��B", GetColor(255, 255, 255));
	DrawString(0, 40, "S�L�[�������ƂɃQ�[����ʂɐi�݂܂��B", GetColor(255, 255, 255));
}
