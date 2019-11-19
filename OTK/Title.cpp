#include "Title.h"
#include "DxLib.h"

Title::Title(ISceneChanger* changer) : BaseScene(changer)
{

}

//������
void Title::Initialize()
{
	mImageHandle = LoadGraph("images/Scene_Config.png");    //�摜�̃��[�h
}

//�X�V
void Title::Update()
{
	if (CheckHitKey(KEY_INPUT_W) != 0)
	{ //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_GamePlay);//�V�[�������j���[�ɕύX
	}
}

//�`��
void Title::Draw()
{
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	DrawString(0, 0, "�ݒ��ʂł��B", GetColor(255, 255, 255));
	DrawString(0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));
}